/*
 * pindefines.h
 *
 * Created: 7-2-2013 15:26:12
 *  Author: Koen Beckers
 */ 


#ifndef PINDEFINES_H_
#define PINDEFINES_H_

#define DDR_LCD				DDRC
#define PORT_LCD			PORTC
#define LCD					_BV(PC2)

#define DDR_LED				DDRA
#define PORT_LED			PORTA
#define LED					_BV(PA4)

#define PORT_LCD_CMD		PORTD
#define DDR_LCD_CMD			DDRD
#define LCD_CMD_DI			PD4
#define LCD_CMD_RW			PD5
#define LCD_CMD_EN			PD6
#define LCD_CMD_CS1			PD3
#define LCD_CMD_CS2			PD2

#define PORT_BACKLIGHT		PORTD
#define DDR_BACKLIGHT		DDRD
#define BACKLIGHT			_BV(PD7)
#define PWM_BACKLIGHT		OCR2A

#define PIN_LCD_DATA		PINB
#define PORT_LCD_DATA		PORTB
#define DDR_LCD_DATA		DDRB

#define PORT_TOUCH			PORTA
#define PIN_TOUCH			PINA
#define DDR_TOUCH			DDRA
#define TOUCH_1				PA0
#define TOUCH_2				PA1
#define TOUCH_3				PA2
#define TOUCH_4				PA3

#define ADC_BATTERY			PA5


#define DDR_CVP				DDRC
#define PORT_CVP			PORTC
#define CVP_ON				_BV(PC7)
#define CVP_OFF				_BV(PC6)

#define DDR_BUTTONS			DDRC
#define PORT_BUTTONS		PORTC
#define PIN_BUTTONS			PINC
#define BUTTON_WAKE			_BV(PC3)
#define BUTTON_ON			_BV(PC4)
#define BUTTON_OFF			_BV(PC5)

#define TEMP_INTERN			_BV(PA6)
#define PIN_TEMP_INTERN		PINA
#define PORT_TEMP_INTERN	PORTA
#define DDR_TEMP_INTERN		DDRA

#define TEMP_EXTERN			_BV(PA7)
#define PIN_TEMP_EXTERN		PINA
#define PORT_TEMP_EXTERN	PORTA
#define DDR_TEMP_EXTERN		DDRA





#endif /* PINDEFINES_H_ */