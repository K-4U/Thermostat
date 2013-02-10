#ifndef ONE_WIRE_C
#define ONE_WIRE_C

#include <avr/io.h>
#include <util/atomic.h>
#include "headers/onewire.h"

/*
 * Reads temp from the DS18B20
 */
double ds1820_read(void)
{
	ADCSRA &= ~(1<<ADEN)|~(1<<ADSC);
	uint8_t busy=0, temp1, temp2;
    int16_t temp3;
    double result;

    ow_reset();
	ow_byte_wr(0xCC); 
	ow_byte_wr(0x44);
	
	while(busy == 0){
		busy = ow_byte_rd();
	}
	
	ow_reset();
	ow_byte_wr(0xCC);
	ow_byte_wr(0xBE);
	
	temp1 = ow_byte_rd();
	temp2 = ow_byte_rd();
	
	
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
    return(result);
}	

#endif /*ONE_WIRE_C*/