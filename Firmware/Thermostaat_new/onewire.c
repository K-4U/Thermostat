/*
 * onewire.c
 *
 * Created: 7-2-2013 15:57:02
 *  Author: Koen Beckers
 */ 
#include <util/delay.h>
#include <util/atomic.h>
#include "Headers/config.h"
#include "Headers/onewire.h"


uint8_t ow_input_pin_state(tempSensor* sensor){
	return (*sensor->pin & sensor->loc); //OW_GET_IN();
}

void ow_parasite_enable(tempSensor *sensor){
	*sensor->port |= sensor->loc; //OW_OUT_HIGH();
	 *sensor->ddr |= sensor->loc; //OW_DIR_OUT();
}

void ow_parasite_disable(tempSensor *sensor){
	*sensor->ddr &= ~sensor->loc; //OW_DIR_IN();
#if (!OW_USE_INTERNAL_PULLUP)
	*sensor->port &= ~sensor->loc; //OW_OUT_LOW();
#endif
}


uint8_t ow_reset(tempSensor *sensor){
	uint8_t err;
	
	*sensor->port &= ~sensor->loc; //OW_OUT_LOW();
	*sensor->ddr |= sensor->loc; //OW_DIR_OUT();            // pull OW-Pin low for 480us
	_delay_us(480);

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		// set Pin as input - wait for clients to pull low
		*sensor->ddr &= ~sensor->loc; //OW_DIR_IN(); // input
#if OW_USE_INTERNAL_PULLUP
		*sensor->port |= sensor->loc; //OW_OUT_HIGH();
#endif
	
		_delay_us(64);       // was 66
		err = ow_input_pin_state(sensor);   // no presence detect
		                     // if err!=0: nobody pulled to low, still high
	}
	
	// after a delay the clients should release the line
	// and input-pin gets back to high by pull-up-resistor
	_delay_us(480 - 64);       // was 480-66
	if( ow_input_pin_state(sensor) == 0 ) {
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
static uint8_t ow_bit_io_intern(tempSensor *sensor, uint8_t b, const uint8_t with_parasite_enable )
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
#if OW_USE_INTERNAL_PULLUP
		*sensor->port &= ~sensor->loc; //OW_OUT_LOW();
#endif
		*sensor->ddr |= sensor->loc; //OW_DIR_OUT();    // drive bus low
		_delay_us(2);    // T_INT > 1usec accoding to timing-diagramm
		if ( b ) {
			*sensor->ddr &= ~sensor->loc; //OW_DIR_IN(); // to write "1" release bus, resistor pulls high
#if OW_USE_INTERNAL_PULLUP
			*sensor->port |= sensor->loc; //OW_OUT_HIGH();
#endif
		}

		// "Output data from the DS18B20 is valid for 15usec after the falling
		// edge that initiated the read time slot. Therefore, the master must 
		// release the bus and then sample the bus state within 15ussec from 
		// the start of the slot."
		_delay_us(15-2-OW_CONF_DELAYOFFSET);
		
		if( ow_input_pin_state(sensor) == 0 ) {
			b = 0;  // sample at end of read-timeslot
		}
	
		_delay_us(60-15-2+OW_CONF_DELAYOFFSET);
#if OW_USE_INTERNAL_PULLUP
		*sensor->port |= sensor->loc; //OW_OUT_HIGH();
#endif
		*sensor->ddr &= ~sensor->loc; //OW_DIR_IN();
	
		if ( with_parasite_enable ) {
			ow_parasite_enable(sensor);
		}
	
	} /* ATOMIC_BLOCK */

	_delay_us(OW_RECOVERY_TIME); // may be increased for longer wires

	return b;
}

uint8_t ow_bit_io(tempSensor *sensor, const uint8_t b )
{
	return ow_bit_io_intern(sensor, b & 1, 0 );
}

uint8_t ow_byte_wr(tempSensor *sensor, uint8_t b )
{
	uint8_t i = 8, j;
	
	do {
		j = ow_bit_io(sensor, b & 1 );
		b >>= 1;
		if( j ) {
			b |= 0x80;
		}
	} while( --i );
	
	return b;
}

uint8_t ow_byte_rd( tempSensor *sensor ){
	// read by sending only "1"s, so bus gets released
	// after the init low-pulse in every slot
	return ow_byte_wr(sensor, 0xFF ); 
}

