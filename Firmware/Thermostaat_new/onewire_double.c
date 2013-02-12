#include <avr/io.h>
#include <util/delay.h>
#include <util/atomic.h>
#include "Headers/config.h"
#include "Headers/onewire.h"

#define OW_EX_GET_IN()   ( PIN_TEMP_EXTERN	&	TEMP_EXTERN)
#define OW_EX_OUT_LOW()  ( PORT_TEMP_EXTERN &=	~TEMP_EXTERN)
#define OW_EX_OUT_HIGH() ( PORT_TEMP_EXTERN |=	TEMP_EXTERN)
#define OW_EX_DIR_IN()   ( DDR_TEMP_EXTERN	&=	~TEMP_EXTERN)
#define OW_EX_DIR_OUT()  ( DDR_TEMP_EXTERN	|=	TEMP_EXTERN)


#define OW_IN_GET_IN()   ( PIN_TEMP_INTERN	&	TEMP_INTERN)
#define OW_IN_OUT_LOW()  ( PORT_TEMP_INTERN &=	~TEMP_INTERN)
#define OW_IN_OUT_HIGH() ( PORT_TEMP_INTERN |=	TEMP_INTERN)
#define OW_IN_DIR_IN()   ( DDR_TEMP_INTERN	&=	~TEMP_INTERN)
#define OW_IN_DIR_OUT()  ( DDR_TEMP_INTERN	|=	TEMP_INTERN)


uint8_t ow_in_input_pin_state(){
	return OW_IN_GET_IN();
}
uint8_t ow_ex_input_pin_state(){
	return OW_EX_GET_IN();
}


void ow_in_parasite_enable(void){
	OW_IN_OUT_HIGH();
	OW_IN_DIR_OUT();
}
void ow_ex_parasite_enable(void){
	OW_EX_OUT_HIGH();
	OW_EX_DIR_OUT();
}


void ow_in_parasite_disable(void){
	OW_IN_DIR_IN();
#if (!OW_USE_INTERNAL_PULLUP)
	OW_IN_OUT_LOW();
#endif
}
void ow_ex_parasite_disable(void){
	OW_EX_DIR_IN();
#if (!OW_USE_INTERNAL_PULLUP)
	OW_EX_OUT_LOW();
#endif
}


uint8_t ow_in_reset(void){
	uint8_t err;
	
	OW_IN_OUT_LOW();
	OW_IN_DIR_OUT();            // pull OW-Pin low for 480us
	_delay_us(480);

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		// set Pin as input - wait for clients to pull low
		OW_IN_DIR_IN(); // input
#if OW_USE_INTERNAL_PULLUP
		OW_IN_OUT_HIGH();
#endif
	
		_delay_us(64);       // was 66
		err = OW_IN_GET_IN();   // no presence detect
		                     // if err!=0: nobody pulled to low, still high
	}
	
	// after a delay the clients should release the line
	// and input-pin gets back to high by pull-up-resistor
	_delay_us(480 - 64);       // was 480-66
	if( OW_IN_GET_IN() == 0 ) {
		err = 1;             // short circuit, expected low but got high
	}
	
	return err;
}

uint8_t ow_ex_reset(void){
	uint8_t err;
	
	OW_EX_OUT_LOW();
	OW_EX_DIR_OUT();            // pull OW-Pin low for 480us
	_delay_us(480);

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		// set Pin as input - wait for clients to pull low
		OW_EX_DIR_IN(); // input
#if OW_USE_INTERNAL_PULLUP
		OW_EX_OUT_HIGH();
#endif
	
		_delay_us(64);       // was 66
		err = OW_EX_GET_IN();   // no presence detect
		                     // if err!=0: nobody pulled to low, still high
	}
	
	// after a delay the clients should release the line
	// and input-pin gets back to high by pull-up-resistor
	_delay_us(480 - 64);       // was 480-66
	if( OW_EX_GET_IN() == 0 ) {
		err = 1;             // short circuit, expected low but got high
	}
	
	return err;
}


/* Timing issue when using runtime-bus-selection (!OW_ONE_BUS):
   The master should sample at the end of the 15-slot after initiating
   the read-time-slot. The variable bus-settings need more
   cycles than the constant ones so the delays had to be shortened 
   to achive a 15uS overall delay 
   Setting/clearing a bit in I/O Register needs 1 cyle in OW_ONE_BUS
   but around 14 cyles in configureable bus (us-Delay is 4 cyles per uS) */
static uint8_t ow_in_bit_io_intern( uint8_t b, uint8_t with_parasite_enable )
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
#if OW_USE_INTERNAL_PULLUP
		OW_IN_OUT_LOW();
#endif
		OW_IN_DIR_OUT();    // drive bus low
		_delay_us(2);    // T_INT > 1usec accoding to timing-diagramm
		if ( b ) {
			OW_IN_DIR_IN(); // to write "1" release bus, resistor pulls high
#if OW_USE_INTERNAL_PULLUP
			OW_IN_OUT_HIGH();
#endif
		}

		// "Output data from the DS18B20 is valid for 15usec after the falling
		// edge that initiated the read time slot. Therefore, the master must 
		// release the bus and then sample the bus state within 15ussec from 
		// the start of the slot."
		_delay_us(15-2-OW_CONF_DELAYOFFSET);
		
		if( OW_IN_GET_IN() == 0 ) {
			b = 0;  // sample at end of read-timeslot
		}
	
		_delay_us(60-15-2+OW_CONF_DELAYOFFSET);
#if OW_USE_INTERNAL_PULLUP
		OW_IN_OUT_HIGH();
#endif
		OW_IN_DIR_IN();
	
		if ( with_parasite_enable ) {
			ow_in_parasite_enable();
		}
	
	} /* ATOMIC_BLOCK */

	_delay_us(OW_RECOVERY_TIME); // may be increased for longer wires

	return b;
}
static uint8_t ow_ex_bit_io_intern( uint8_t b, uint8_t with_parasite_enable )
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
#if OW_USE_INTERNAL_PULLUP
		OW_EX_OUT_LOW();
#endif
		OW_EX_DIR_OUT();    // drive bus low
		_delay_us(2);    // T_INT > 1usec accoding to timing-diagramm
		if ( b ) {
			OW_EX_DIR_IN(); // to write "1" release bus, resistor pulls high
#if OW_USE_INTERNAL_PULLUP
			OW_EX_OUT_HIGH();
#endif
		}

		// "Output data from the DS18B20 is valid for 15usec after the falling
		// edge that initiated the read time slot. Therefore, the master must 
		// release the bus and then sample the bus state within 15ussec from 
		// the start of the slot."
		_delay_us(15-2-OW_CONF_DELAYOFFSET);
		
		if( OW_EX_GET_IN() == 0 ) {
			b = 0;  // sample at end of read-timeslot
		}
	
		_delay_us(60-15-2+OW_CONF_DELAYOFFSET);
#if OW_USE_INTERNAL_PULLUP
		OW_EX_OUT_HIGH();
#endif
		OW_EX_DIR_IN();
	
		if ( with_parasite_enable ) {
			ow_ex_parasite_enable();
		}
	
	} /* ATOMIC_BLOCK */

	_delay_us(OW_RECOVERY_TIME); // may be increased for longer wires

	return b;
}


uint8_t ow_in_bit_io( uint8_t b ){
	return ow_in_bit_io_intern( b & 1, 0 );
}
uint8_t ow_ex_bit_io( uint8_t b ){
	return ow_ex_bit_io_intern( b & 1, 0 );
}

uint8_t ow_in_byte_wr( uint8_t b ){
	uint8_t i = 8, j;
	
	do {
		j = ow_in_bit_io( b & 1 );
		b >>= 1;
		if( j ) {
			b |= 0x80;
		}
	} while( --i );
	
	return b;
}
uint8_t ow_ex_byte_wr( uint8_t b ){
	uint8_t i = 8, j;
	
	do {
		j = ow_ex_bit_io( b & 1 );
		b >>= 1;
		if( j ) {
			b |= 0x80;
		}
	} while( --i );
	
	return b;
}

uint8_t ow_in_byte_wr_with_parasite_enable( uint8_t b ){
	uint8_t i = 8, j;
	
	do {
		if ( i != 1 ) {
			j = ow_in_bit_io_intern( b & 1, 0 );
		} else {
			j = ow_in_bit_io_intern( b & 1, 1 );
		}
		b >>= 1;
		if( j ) {
			b |= 0x80;
		}
	} while( --i );
	
	return b;
}
uint8_t ow_ex_byte_wr_with_parasite_enable( uint8_t b ){
	uint8_t i = 8, j;
	
	do {
		if ( i != 1 ) {
			j = ow_ex_bit_io_intern( b & 1, 0 );
		} else {
			j = ow_ex_bit_io_intern( b & 1, 1 );
		}
		b >>= 1;
		if( j ) {
			b |= 0x80;
		}
	} while( --i );
	
	return b;
}



uint8_t ow_in_byte_rd( void ){
	// read by sending only "1"s, so bus gets released
	// after the init low-pulse in every slot
	return ow_in_byte_wr( 0xFF ); 
}

uint8_t ow_ex_byte_rd( void ){
	// read by sending only "1"s, so bus gets released
	// after the init low-pulse in every slot
	return ow_ex_byte_wr( 0xFF ); 
}

