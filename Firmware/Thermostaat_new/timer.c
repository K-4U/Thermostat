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


/*
 * Initializes the PWM Hardware
 */
void init_pwm(){
	//Timer 2 setup
	TCCR2A |= (1 << COM2A1) | (0 << COM2A0);
	TCCR2A |= (0 << WGM21) | (1 << WGM20);	// Phase Correct PWM.
	TCCR2B |= (1 << CS20); //Timer 2 start
	OCR2A = 0;
	
	DDR_BACKLIGHT |= BACKLIGHT;
}

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
		
		currentDateTime.time.seconds++;
		if(CHECKFLAG(FLAG_AWAKE)){
			SETDRAWFLAG(DRAW_TIME);
		}				
		if((currentDateTime.time.seconds % 10) == 0){
			SETFLAG(FLAG_READTIME);
		}
		if((currentDateTime.time.seconds % 20) == 0){
			ds1820_read(&tempIntern);
			if(tempIntern.prevReading != tempIntern.lastReading){
				if(!CHECKFLAG(FLAG_AWAYSCREEN)){
					SETDRAWFLAG(DRAW_INTERN);
				}					
				tempIntern.prevReading = tempIntern.lastReading;
			}
		
				
			ds1820_read(&tempExtern);
			if(tempExtern.prevReading != tempExtern.lastReading){
				if(!CHECKFLAG(FLAG_AWAYSCREEN)){
					SETDRAWFLAG(DRAW_EXTERN);
				}					
				tempExtern.prevReading = tempExtern.lastReading;
			}
		}	
		
		batteryLevel = read_adc(ADC_BATTERY);
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
		}
	}
	
	if(CHECKFLAG(FLAG_100MS)){
		RESETFLAG(FLAG_100MS);
	}
	
	if(CHECKFLAG(FLAG_HALFSEC)){
		RESETFLAG(FLAG_HALFSEC);

		if(CHECKFLAG(FLAG_AWAKE)){
			lastAction++;
			PWM_BACKLIGHT = (MAX_LAST_ACTION - lastAction) * (255 / MAX_LAST_ACTION);
			SETDRAWFLAG(DRAW_TTL_BAR);
			if(lastAction == MAX_LAST_ACTION){
				turnLcdOff();
				power_twi_disable();
				power_timer2_disable();
				power_adc_disable();
				sleep_enable();
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
