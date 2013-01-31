/*
 * Thermostaat.c
 *
 * Created: 31-1-2013 19:40:12
 *  Author: Koen Beckers
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>


#include "main.h"

#include "ks0108.h"
#include "arial_bold_14.h"

#include "ds1820.h"


uint16_t read_adc(uint8_t adc_input)
{
	//Set ADC off
	ADCSRA &= ~(1<<ADEN)|~(1<<ADSC);

	ADMUX = (0 << REFS0); // Set ADC reference to AVREF
	//ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading
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
	DDRA = 0b00100000;
	DDRB = 0b00000000;
	DDRC = 0xFF;
	DDRD = 0xFF;
	
	LED_AAN();
		/*-------------------------------------
	 * ADC Conversion
	 *-------------------------------------
	 */
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0); 
	ADMUX |= (0 << REFS0); 
	//ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading

	ADCSRA |= (1 << ADEN);  // Enable ADC
	ADCSRA |= (1 << ADSC);  // Start A2D Conversions
	
	// Wait a little while the display starts up
	
	
	// Initialize the LCD
	ks0108Init(0);
	
	// Select a font
	
	ks0108SelectFont(Arial_Bold_14, ks0108ReadFontData, BLACK);
	// Set a position
	ks0108GotoXY(15,10);
	// Print some text
	ks0108Puts_P(PSTR("Hallo wereld!"));
	// a nice little round rect
	ks0108DrawRoundRect(5, 5, 117, 20, 8, BLACK);
	


	// Once again :)
	// Select a font
	//ks0108SelectFont(SC, ks0108ReadFontData, BLACK);
	// Set a position
	//ks0108GotoXY(5,30);
	// Print some text
	//ks0108Puts("test");
   // ks0108DrawLine(0, 0, 100, 50, BLACK);
	//ks0108DrawCircle(50, 40, 20, BLACK);
	//ks0108ClearScreen();
	//LoadBitmap(IMAGE);

	for(;;){
		ks0108ClearScreen();
		char lm35TempString[10];
		
		double tempff;
		uint16_t tempC;
		
		tempC = read_adc(3);
		tempff = (float)tempC;
		tempff = (5.0 * tempC * 100.0)/1023.0;
		
		dtostrf(tempff,1,1,&lm35TempString);
		
		ks0108GotoXY(15,10);
		// Print some text
		ks0108Puts_P(PSTR("Hallo wereld!"));
		// a nice little round rect
		ks0108DrawRoundRect(5, 5, 117, 20, 8, BLACK);
		ks0108GotoXY(15,30);
		// Print some text
		ks0108Puts(lm35TempString);
		//ks0108Puts_P(PSTR(ds1820TempString));
		// a nice little round rect
		ks0108DrawRoundRect(5, 5, 117, 40, 8, BLACK);
		_delay_ms(500);
	}
}