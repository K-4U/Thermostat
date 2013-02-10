/*
 * timer.c
 *
 * Created: 7-2-2013 16:56:36
 *  Author: Koen Beckers
 */ 
#include "Headers/config.h"
#include "Headers/adc.h"
#include "Headers/timer.h"
#include "Headers/tempsensor.h"
#include "Headers/glcdFunctions.h"

void init_timer1(void){
	//Initialize Interrupt for timer1
	TCNT1L = 0x3c;
	TCNT1H = 0xf6;
	TCCR1B = (0<<WGM12) | (0<<CS12)|(1<<CS11)|(0<<CS10); 
	TIMSK1 |= _BV(TOIE1);
	printf("Timer 1 initialized\r\n");
}


void timer(void){
	if(CHECKFLAG(FLAG_SEC)){
		RESETFLAG(FLAG_SEC);
		
		if(CHECKFLAG(FLAG_AWAKE)){
			currentDateTime.time.seconds++;
			if(currentDateTime.time.seconds == 60){
				SETFLAG(FLAG_READTIME);
			}
		}		
		
		ds1820_read(&tempIntern);
		if(oldCurrentTemp != tempIntern.lastReading){
			SETDRAWFLAG(DRAW_CURRENT);
			oldCurrentTemp = tempIntern.lastReading;
		}	
		
		/*batteryLevel = read_adc(4);
		if( (batteryLevel <= (oldBatteryLevel-2)) || (batteryLevel >= (oldBatteryLevel+2))){
			SETDRAWFLAG(DRAW_BATTERY_BAR);
			
			oldBatteryLevel = batteryLevel;
			if(batteryLevel < MINIMAL_BATTERY_LEVEL && !CHECKFLAG(FLAG_BATTERYTOOLOW)){
				//BATTERY TOO LOW!
				SETFLAG(FLAG_BATTERYTOOLOW);
				CV_OFF();
				//Draw the warning
				SETDRAWFLAG(DRAW_BATTERY_LOW);
			}
		}*/
	}
	
	if(CHECKFLAG(FLAG_100MS)){
		RESETFLAG(FLAG_100MS);
	}
	
	if(CHECKFLAG(FLAG_HALFSEC)){
		RESETFLAG(FLAG_HALFSEC);

		if(CHECKFLAG(FLAG_AWAKE)){
			lastAction++;
			SETDRAWFLAG(DRAW_TTL_BAR);
			if(lastAction == MAX_LAST_ACTION){
				turnLcdOff();
			}
		}
		
	}
	
	
}

volatile uint16_t t;
ISR(TIMER1_OVF_vect){
	//This gets called every mSec!
	TCNT1L = 0x3c;
	TCNT1H = 0xf6;

	t++;
	if((t % 100) == 0){
		SETFLAG(FLAG_100MS);
	}
	if((t % 500) == 0){
		SETFLAG(FLAG_HALFSEC);
	}
	if((t % 1000) == 0){
		SETFLAG(FLAG_SEC);
		t = 0;
	}
}
