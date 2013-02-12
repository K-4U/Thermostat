#include <avr/io.h>
#include <util/atomic.h>
#include "Headers/config.h"
#include "Headers/onewire.h"

void init_ds1820(void){
	tempIntern.lastReading = 0.0;
	tempIntern.prevReading = 0.0;
	
	tempExtern.lastReading = 0.0;
	tempExtern.prevReading = 0.0;
}


/*
 * Reads temp from the DS18B20
 */
void ds1820_extern_read(void){
	ADCSRA &= ~(1<<ADEN)|~(1<<ADSC);
	uint8_t busy=0, temp1, temp2;
    int16_t temp3;
    double result;

    ow_ex_reset();
	ow_ex_byte_wr(0xCC); 
	ow_ex_byte_wr(0x44);
	
	while(busy == 0){
		busy = ow_ex_byte_rd();
	}
	
	ow_ex_reset();
	ow_ex_byte_wr(0xCC);
	ow_ex_byte_wr(0xBE);
	
	temp1 = ow_ex_byte_rd();
	temp2 = ow_ex_byte_rd();
	
	
    /*onewire_write(0xCC);            //Skip ROM, address all devices
    onewire_write(0x44);            //Start temperature conversion

    while(busy == 0)                //Wait while busy (bus is low)
        busy = onewire_read();

    onewire_reset();
    onewire_write(0xCC);            //Skip ROM, address all devices
    onewire_write(0xBE);            //Read scratchpad
    temp1 = onewire_read();
    temp2 = onewire_read();*/
    
    temp3 = temp2;
    temp3 = temp3 << 8;
    temp3 = temp3 | temp1;
 
    //result = (float) temp3 / 2.0;   //Calculation for DS18S20 with 0.5 deg C resolution
    result = (double) temp3 / 16.0;    //Calculation for DS18B20
 
    //_delay_ms(200);
    //return(result);
	tempExtern.lastReading = result;
}	
/*
 * Reads temp from the DS18B20
 */
void ds1820_intern_read(void){
	ADCSRA &= ~(1<<ADEN)|~(1<<ADSC);
	uint8_t busy=0, temp1, temp2;
    int16_t temp3;
    double result;

    ow_in_reset();
	ow_in_byte_wr(0xCC); 
	ow_in_byte_wr(0x44);
	
	while(busy == 0){
		busy = ow_in_byte_rd();
	}
	
	ow_in_reset();
	ow_in_byte_wr(0xCC);
	ow_in_byte_wr(0xBE);
	
	temp1 = ow_in_byte_rd();
	temp2 = ow_in_byte_rd();
	
	
    /*onewire_write(0xCC);            //Skip ROM, address all devices
    onewire_write(0x44);            //Start temperature conversion

    while(busy == 0)                //Wait while busy (bus is low)
        busy = onewire_read();

    onewire_reset();
    onewire_write(0xCC);            //Skip ROM, address all devices
    onewire_write(0xBE);            //Read scratchpad
    temp1 = onewire_read();
    temp2 = onewire_read();*/
    
    temp3 = temp2;
    temp3 = temp3 << 8;
    temp3 = temp3 | temp1;
 
    //result = (float) temp3 / 2.0;   //Calculation for DS18S20 with 0.5 deg C resolution
    result = (double) temp3 / 16.0;    //Calculation for DS18B20
 
    //_delay_ms(200);
    //return(result);
	tempIntern.lastReading = result;
}	