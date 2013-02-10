/*
 * adc.c
 *
 * Created: 7-2-2013 16:18:54
 *  Author: Koen Beckers
 */ 
#include <avr/io.h>


void init_adc(){
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0);

	ADMUX |= (0 << REFS0); 
	ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading

	ADCSRA |= (1 << ADEN);  // Enable ADC
	ADCSRA |= (1 << ADSC);  // Start A2D Conversions
}

uint8_t read_adc(const uint8_t adc_input){
	//Set ADC off
	ADCSRA &= ~(1<<ADEN)|~(1<<ADSC);

	ADMUX = (0 << REFS0); // Set ADC reference to AVREF
	ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading
	ADMUX |= adc_input;

	ADCSRA |= (1<<ADEN)|(1<<ADSC);
	while ((ADCSRA & 0x10)==0);
	ADCSRA|=0x10;

	return ADCH;
}


uint16_t read_adc_16(const uint8_t adc_input){
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