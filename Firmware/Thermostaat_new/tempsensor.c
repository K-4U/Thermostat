/*
 * tempsensor.c
 *
 * Created: 7-2-2013 15:54:46
 *  Author: Koen Beckers
 */ 

#include "Headers/config.h"
#include "Headers/tempsensor.h"
#include "Headers/onewire.h"


void init_ds1820(void){
	tempIntern.ddr = &DDR_TEMP_INTERN;
	tempIntern.lastReading = 0.0;
	tempIntern.loc = TEMP_INTERN;
	tempIntern.pin = &PIN_TEMP_INTERN;
	tempIntern.port = &PORT_TEMP_INTERN;
	
	tempExtern.ddr = &DDR_TEMP_EXTERN;
	tempExtern.lastReading = 0.0;
	tempExtern.loc = TEMP_EXTERN;
	tempExtern.pin = &PIN_TEMP_EXTERN;
	tempExtern.port = &PORT_TEMP_EXTERN;
}

void ds1820_read(tempSensor *sensor){
	//ADCSRA &= ~(1<<ADEN)|~(1<<ADSC);
	uint8_t busy=0, temp1, temp2;
    int16_t temp3;
    double result;

    ow_reset(sensor);
	ow_byte_wr(sensor,0xCC); 
	ow_byte_wr(sensor,0x44);
	
	while(busy == 0){
		busy = ow_byte_rd(sensor);
	}
	
	ow_reset(sensor);
	ow_byte_wr(sensor,0xCC);
	ow_byte_wr(sensor,0xBE);
	
	temp1 = ow_byte_rd(sensor);
	temp2 = ow_byte_rd(sensor);
	
	
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
	
	char currentTempStr[30];
	dtostrf(result,1,1,currentTempStr);
	printf("%s\r\n", currentTempStr);
 
    //_delay_ms(200);
    sensor->lastReading = result;
}	