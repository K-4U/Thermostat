/*
 * Thermostaat.c
 *
 * Created: 31-1-2013 19:40:12
 *  Author: Koen Beckers
 */ 

//#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#define MAIN_C
#include "headers/structs.h"
#include "headers/main.h"

#include "headers/uart.h" //TEMP

#include "headers/ks0108.h"
#include "headers/glcdFunctions.h"
#include "headers/batterybar.h"
#include "headers/bitmap.h"
//#include "headers/ds1307.h"

const preset prs_sun = {sun, 18};
const preset prs_moon = {Moon, 13};

FILE  uart_str= FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);


uint8_t read_adc(uint8_t adc_input)
{
	//Set ADC off
	ADCSRA &= ~(1<<ADEN)|~(1<<ADSC);

	ADMUX = (0 << REFS0); // Set ADC reference to AVREF
	ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading
	ADMUX |= adc_input;

	ADCSRA |= (1<<ADEN)|(1<<ADSC);
	while ((ADCSRA & 0x10)==0);
	ADCSRA|=0x10;
	
	//uint16_t z2 = ADCL; //Read the high
	//z2 = z2 + (ADCH<<8); //Read the low

	return ADCH;
}


uint16_t read_adc_16(uint8_t adc_input)
{
	//Set ADC off
	ADCSRA &= ~(1<<ADEN)|~(1<<ADSC);

	ADMUX = (0 << REFS0); // Set ADC reference to AVREF
	ADMUX &= ~(1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading
	ADMUX |= adc_input;

	ADCSRA |= (1<<ADEN)|(1<<ADSC);
	while ((ADCSRA & 0x10)==0);
	ADCSRA|=0x10;

	return ADC;
}


int main(void){
	
	//Init direction registers
	// 1 = output
	// 0 = input
	//		 76543210
	//DDRA = 0b00100000;
	DDRB = 0b00000000;
	DDRC = 0b00000000;
	PORTC = 0x00 | BUTTON_WAKE | BUTTON_ON;
	DDRD = 0xFF;
	
	stdout = stderr = &uart_str; //So that we can use printf() to print to our UART
	
	uart_init();
	
	sei();
	
	printf("Start!\r\n");

	LCD_AAN();
	SETFLAG(FLAG_AWAKE);
	for(volatile uint16_t i=0; i<15000; i++);
	ks0108Init(0);
		/*-------------------------------------
	 * ADC Conversion
	 *-------------------------------------
	 */
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0); // Set ADC prescaler to 128 - 125KHz sample rate @ 20MHz

	ADMUX |= (0 << REFS0); // Set ADC reference to AVREF
	ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading

	ADCSRA |= (1 << ADEN);  // Enable ADC
	ADCSRA |= (1 << ADSC);  // Start A2D Conversions
	
	//Initialize Interrupt for timer0
	TCNT0 = 0x83;
	TCCR0B = (0<<WGM01) | (0<<CS02)|(1<<CS01)|(1<<CS00);
	TIMSK0 |= _BV(TOIE0);
	
	currentTemp = 15;
	setTemp = 17.0;
	//Read_DS1307();
	
	currentDateTime.seconds = 0;
	currentDateTime.minute = 37;
	currentDateTime.hours = 13;
	currentDateTime.date = 3;
	currentDateTime.month = 2;
	currentDateTime.year = 13;
	
	dtostrf(currentTemp,1,1,currentTempStr);
	dtostrf(setTemp,1,1,setTempStr);
	
	
	//Load boot screen plox
	loadImageInverted(0,0,logo);
	_delay_ms(200);
	loadImage(0,0,logo);
	
	_delay_ms(1000);
	
	ks0108ClearScreen();
	
	drawMainScreen();
	
	lcdPos stylus;
	lcdPos oldStylus;
	
	uint8_t batteryLevel = read_adc(5);
	uint8_t oldBatteryLevel = batteryLevel;
	batteryBar battery = createBatteryBar(batteryLevel,256,TOPBAR_Y+1);
	batteryBar ttl	   = createBatteryBar(MAXLASTACTION - lastAction,MAXLASTACTION,KS0108_SCREEN_HEIGHT-1);
	drawBar(&battery);
	drawBar(&ttl);
	
	SETFLAG(FLAG_AWAKE);
	uint16_t wait;
	double oldSetTemp;
	double oldCurrentTemp;
	for(;;){
		if(!CHECKFLAG(FLAG_AWAKE)){
			if((BUTTON_PIN & BUTTON_WAKE) == 0){
				//Pressed me!
				turnLcdOn();
				drawBar(&battery);
				drawBar(&ttl);
				lastAction = 0;
				if(CHECKFLAG(FLAG_CV_ON)){
					loadImage(FLAME_X,FLAME_Y, flame);
				}	
			}
		}
		
		
		if(CHECKFLAG(FLAG_AWAKE)){
			stylus = readPos();
			uint8_t posDiff = 0;
			if((posDiff = isDifferent(&stylus,&oldStylus))){
				if(posDiff & DIFF_P){
					if(stylus.isPressed){
						if(isIn(&stylus,&buttonDown)){
							drawMainScreenButtons(2);
							setTemp-=0.5;
						}else if(isIn(&stylus,&buttonUp)){
							drawMainScreenButtons(1);
							setTemp+=0.5;
						}else if(isIn(&stylus, &buttonPreset)){
							drawMainScreenButtons(3);
							if(CHECKFLAG(FLAG_DRAWER)){
								closePresetDrawer();
							}else{
								drawPresetDrawer();
							}								
						}
						if(CHECKFLAG(FLAG_DRAWER)){
							if(isIn(&stylus,&preset_sun)){
								activePreset = &prs_sun;
								setTemp = activePreset->setTemp;
								closePresetDrawer();
								drawPresetActive();
							}else if(isIn(&stylus, &preset_moon)){
								activePreset = &prs_moon;
								setTemp = activePreset->setTemp;
								closePresetDrawer();
								drawPresetActive();
							}
						}
					}else{
						//That means it went up!
						drawMainScreenButtons(0);
					}
					lastAction = 0;
				}				
				oldStylus = stylus;
				
			}
			if(oldSetTemp != setTemp){
				dtostrf(setTemp,1,1,setTempStr);
				oldSetTemp = setTemp;
				drawValues();
			}
		}		
		
		if(CHECKFLAG(FLAG_HALFSEC)){
			RESETFLAG(FLAG_HALFSEC);
			if(CHECKFLAG(FLAG_AWAKE)){
				//lastAction++;
				//updateBar(&ttl,MAXLASTACTION-lastAction);
				if(lastAction == MAXLASTACTION){
					turnLcdOff();
				}
			}
			if(CHECKFLAG(FLAG_SEC)){
				RESETFLAG(FLAG_SEC);
				currentDateTime.seconds++;
				if(currentDateTime.seconds == 60){
					currentDateTime.seconds = 0;
					currentDateTime.minute++;
					if(currentDateTime.minute == 60){
						currentDateTime.minute = 0;
						currentDateTime.hours++;
					}
				}
				drawTime();
			}else{
				SETFLAG(FLAG_SEC);
			}
		}
		
		if(CHECKFLAG(FLAG_100MS)){
			RESETFLAG(FLAG_100MS);
			//batteryLevel = read_adc(5);
			batteryLevel = 200;
			if( (batteryLevel <= (oldBatteryLevel-2)) || (batteryLevel >= (oldBatteryLevel+2))){
				if(CHECKFLAG(FLAG_AWAKE)){
					updateBar(&battery,batteryLevel);
				}				
				oldBatteryLevel = batteryLevel;
			}
			double tempff;
			uint8_t tempC;
		
			//tempC = read_adc(4);
			if(oldCurrentTemp != currentTemp){
				oldCurrentTemp = currentTemp;
			}
			if(currentTemp <= setTemp-0.5 && !CHECKFLAG(FLAG_CV_ON)){
				SETFLAG(FLAG_CV_ON);
				//Do that
				CV_ON();
				//Draw
				if(CHECKFLAG(FLAG_AWAKE)){
					loadImage(FLAME_X,FLAME_Y, flame);
				}				
			}else if(currentTemp >= setTemp && CHECKFLAG(FLAG_CV_ON)){
				RESETFLAG(FLAG_CV_ON);
				//Turn it off!!
				CV_OFF();
				//Reset that spot plox
				if(CHECKFLAG(FLAG_AWAKE)){
					ks0108FillRect(FLAME_X,FLAME_Y,KS0108_SCREEN_WIDTH-FLAME_X-1,KS0108_SCREEN_HEIGHT-FLAME_Y-1,WHITE);
				}					
			}	
		}
	}
}


uint16_t t;
ISR(TIMER0_OVF_vect){
	//This gets called every mSec!
	TCNT0 = 0x83;
	t++;
	if(t == 100){
		SETFLAG(FLAG_100MS);
	}
	if(t == 500){
		SETFLAG(FLAG_HALFSEC);
		t=0;
	}	
	
}	