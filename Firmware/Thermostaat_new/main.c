/*
 * main.c
 *
 * Created: 7-2-2013 15:11:32
 *  Author: Koen Beckers
 */ 
#define MAIN_C
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

#include "Headers/config.h"
#include "Headers/adc.h"
#include "Headers/io.h"
#include "Headers/glcdFunctions.h"
#include "Headers/uart.h"
#include "Headers/tempsensor.h"
#include "Headers/ds1307.h"
#include "Headers/timer.h"



int main(void){
	activePreset = &prs_sun;
	init_adc();
	init_io();
	init_display();
	init_uart();
	init_ds1820();
	init_ds1307();
	init_timer1();
	sei();
	
	printf("Init complete!\r\n");
	SETDRAWFLAG(DRAW_ALL);
	
	Read_DS1307(&currentDateTime);
	
	drawMainScreen();
	
    while(1){
		if(CHECKFLAG(FLAG_AWAKE)){
			readAndHandleScreen();
			drawMainScreen();
		}
		
		
		if(CHECKFLAG(FLAG_READTIME)){
			//Read_DS1307(&currentDateTime);
			RESETFLAG(FLAG_READTIME);
		}
		timer();
    }
	return 0;
}