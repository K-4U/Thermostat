/*
 * main.h
 *
 * Created: 31-1-2013 21:24:05
 *  Author: Koen Beckers
 */ 


#ifndef MAIN_H_
#define MAIN_H_
#include "../lang/nl.h"

#ifdef MAIN_C
#define PROTO
#else
#define PROTO extern
#endif

extern const preset prs_sun;
extern const preset prs_moon;

PROTO double currentTemp;
PROTO double setTemp;
PROTO char currentTempStr[5];
PROTO char setTempStr[5];
//PROTO uint8_t prevY;
PROTO uint8_t flags;
PROTO uint8_t lastAction;
PROTO preset *activePreset;

#define MAXLASTACTION 20

PROTO dateTime currentDateTime;
PROTO char currentTimeStr[8];
PROTO char currentDateStr[8];

#define MINIMAL_BATTERY_LEVEL 20


//							  76543210
#define FLAG_CV_ON			0b00000001
#define FLAG_AWAKE			0b00000010
#define FLAG_HALFSEC		0b00000100
#define FLAG_100MS			0b00001000
#define FLAG_SEC			0b00010000
#define FLAG_DRAWER			0b00100000
#define FLAG_BATTERYTOOLOW	0b01000000
#define CHECKFLAG(flag) (flags & flag)
#define SETFLAG(flag)	(flags |= flag)
#define RESETFLAG(flag)	(flags &= ~flag)



#define LCD			_BV(PC2)
#define LCD_AAN()	PORTC |= LCD
#define LCD_UIT()	PORTC &= ~LCD


#define CVP_ON		_BV(PC7)
#define CVP_OFF		_BV(PC6)
#define CV_ON()		{PORTC |= CVP_ON; _delay_ms(5); PORTC &= ~CVP_ON;}
#define CV_OFF()	{PORTC |= CVP_OFF; _delay_ms(5); PORTC &= ~CVP_OFF;}

#define BUTTON_WAKE	_BV(PC3)
#define BUTTON_ON	_BV(PC4)
#define BUTTON_OFF	_BV(PC5)
#define BUTTON_PIN	PINC


#define KS0108_SCREEN_WIDTH		128
#define KS0108_SCREEN_HEIGHT	64
#define TEXTFONT		Ubuntu_9
#define SMALLVALUEFONT	Ubuntu_bold_14
#define LARGEVALUEFONT	ubuntu_bold_26

#define ROUNDNESS	3
#define DEBUG

#define BUTTON_DOWN_X			(KS0108_SCREEN_WIDTH/2)
#define BUTTON_DOWN_Y			SET_Y + UBUNTU_BOLD_14_HEIGHT + 2
#define BUTTON_DOWN_WIDTH		12
#define BUTTON_DOWN_HEIGHT		8

#define BUTTON_UP_X				BUTTON_DOWN_X + BUTTON_DOWN_WIDTH + 4
#define BUTTON_UP_Y				BUTTON_DOWN_Y
#define BUTTON_UP_WIDTH			12
#define BUTTON_UP_HEIGHT		8

#define BUTTON_PRES_X			BUTTON_UP_X + BUTTON_UP_WIDTH + 4
#define BUTTON_PRES_Y			BUTTON_UP_Y
#define BUTTON_PRES_WIDTH		12
#define BUTTON_PRES_HEIGHT		8

#define PRESET_X				BUTTON_PRES_X + 2
#define PRESET_Y				BUTTON_PRES_Y - 15

#define CURRENT_X		3
#define CURRENT_Y		20
#define SET_X			(KS0108_SCREEN_WIDTH/2 + 2)
#define SET_Y			20

#define FLAME_X			KS0108_SCREEN_WIDTH - 8
#define FLAME_Y			KS0108_SCREEN_HEIGHT - 11

#define BATTERY_X		0
#define BATTERY_Y		KS0108_SCREEN_HEIGHT - 11

#define TOPBAR_Y		8

#define MAXWAIT			512


#endif /* MAIN_H_ */