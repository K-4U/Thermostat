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
	init_pwm();
	PWM_BACKLIGHT = 255;
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
	SETFLAG(FLAG_AWAKE);
	/*
	dateTime toWrite;
	toWrite.date.date = 12;
	toWrite.date.month = 02;
	toWrite.date.year = 13;
	toWrite.time.seconds = 00;
	toWrite.time.minute = 35;
	toWrite.time.hours = 13;
	
	Write_DS1307(&toWrite);
	*/
	Read_DS1307(&currentDateTime);
	ds1820_read(&tempIntern);
	ds1820_read(&tempExtern);
	
	drawMainScreen();
	CV_OFF();
	
	timeOfReturn.date.date = 11;
	timeOfReturn.date.month = 02;
	timeOfReturn.date.year = 13;
	timeOfReturn.time.hours = 19;
	timeOfReturn.time.minute = 20;
	
	getDayOfWeek(&timeOfReturn.date);
	//SETFLAG(FLAG_AWAYSCREEN);
	//SETDRAWFLAG(DRAW_AWAYSCREEN);
	
	drawMainScreen();
	power_timer0_disable();
	power_spi_disable();
	set_sleep_mode(SLEEP_MODE_STANDBY);
    while(1){
		if(CHECKFLAG(FLAG_AWAKE)){
			checkButtons();
			readAndHandleScreen();
			drawMainScreen();
			if(CHECKFLAG(FLAG_READTIME)){
				Read_DS1307(&currentDateTime);
				RESETFLAG(FLAG_READTIME);
			}
		}else{
			if(CHECKFLAG(FLAG_WAKE)){
				turnLcdOn();
				SETDRAWFLAG(DRAW_ALL);
				if(CHECKFLAG(FLAG_CV_ON)){
					SETDRAWFLAG(DRAW_CV_ON);
				}
				SETFLAG(FLAG_READTIME);
				lastAction = 0;	
				SETFLAG(FLAG_AWAKE);
				RESETFLAG(FLAG_WAKE);
				
				power_twi_enable();
				power_timer2_enable();
				power_adc_enable();
			}
		}
		
		timer();
		
		if(tempIntern.lastReading <= setTemp-0.5 && !CHECKFLAG(FLAG_CV_ON) && !CHECKFLAG(FLAG_BATTERYTOOLOW)){
			SETFLAG(FLAG_CV_ON);
			CV_ON();			
		}else if(tempIntern.lastReading >= setTemp && CHECKFLAG(FLAG_CV_ON)){
			RESETFLAG(FLAG_CV_ON);
			CV_OFF();				
		}
    }
	return 0;
}