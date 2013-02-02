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
#include <stdio.h>
#include <stdlib.h>
#define MAIN_C
#include "headers/structs.h"
#include "headers/main.h"

#include "headers/uart.h" //TEMP

#include "headers/ks0108.h"
#include "headers/glcdFunctions.h"
#include "headers/progressbar.h"


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
	for(volatile uint16_t i=0; i<15000; i++);
	//Init direction registers
	// 1 = output
	// 0 = input
	//		 76543210
	//DDRA = 0b00100000;
	DDRB = 0b00000000;
	DDRC = 0x00;
	DDRD = 0xFF;
	
	stdout = stderr = &uart_str; //So that we can use printf() to print to our UART
	
	uart_init();
	
	sei();
	
	printf("Test");
	LED_AAN();
		/*-------------------------------------
	 * ADC Conversion
	 *-------------------------------------
	 */
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0); // Set ADC prescaler to 128 - 125KHz sample rate @ 20MHz

	ADMUX |= (0 << REFS0); // Set ADC reference to AVREF
	ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading

	ADCSRA |= (1 << ADEN);  // Enable ADC
	ADCSRA |= (1 << ADSC);  // Start A2D Conversions
	
	// Initialize the LCD
	ks0108Init(0);
	
	currentTemp = 20.5;
	setTemp = 17.0;
	dtostrf(currentTemp,1,1,currentTempStr);
	dtostrf(setTemp,1,1,setTempStr);
	sprintf(currentTimeStr,"20:09:30");
	
	drawMainScreen();
	
	
	lcdPos stylus;
	lcdPos oldStylus;
	
	uint8_t batteryLevel = read_adc(5);
	uint8_t oldBatteryLevel = batteryLevel;
	progressBar battery = createProgressBar(batteryLevel,256,BATTERY_X,BATTERY_Y,BATTERY_WIDTH,BATTERY_HEIGHT);
	drawBar(&battery);
	
	uint16_t wait;
	double oldSetTemp;
	double oldCurrentTemp;
	for(;;){
		stylus = readPos();
		uint8_t posDiff = 0;
		if((posDiff = isDifferent(&stylus,&oldStylus))){
			if(posDiff & DIFF_P){
				if(stylus.isPressed){
					printf("Pressed\r\n");
					if(isIn(&stylus,&buttonDown)){
						drawMainScreenButtons(2);
						setTemp-=0.5;
					}else if(isIn(&stylus,&buttonUp)){
						drawMainScreenButtons(1);
						setTemp+=0.5;
					}
				}else{
					//That means it went up!
					printf("Released\r\n");
					drawMainScreenButtons(0);
				}
			}				
			oldStylus = stylus;
		}
		if(oldSetTemp != setTemp){
			dtostrf(setTemp,1,1,setTempStr);
			oldSetTemp = setTemp;
			drawValues();
		}
		
		if(wait == MAXWAIT){
			batteryLevel = read_adc(5);
			if( (batteryLevel <= (oldBatteryLevel-2)) || (batteryLevel >= (oldBatteryLevel+2))){
				updateBar(&battery,batteryLevel);
				oldBatteryLevel = batteryLevel;
			}
			wait = 0;			
		}
		wait++;
		
		//currentTemp = read_adc_16(4);
		//printf("%i\r\n",currentTemp);
		
		//dtostrf(currentTemp,1,1,currentTempStr);
		//dtostrf(setTemp,1,1,setTempStr);
		//drawValues();
		//drawMainScreen();
	}
}