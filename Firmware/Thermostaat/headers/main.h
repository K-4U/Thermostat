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

PROTO double currentTemp;
PROTO double setTemp;
PROTO char currentTempStr[5];
PROTO char setTempStr[5];
PROTO uint8_t prevY;

PROTO char currentTimeStr[8];

#define LED			_BV(PD5)
#define LED_AAN()	PORTD |= LED
#define LED_UIT()	PORTD &= ~LED


#define KS0108_SCREEN_WIDTH		128
#define KS0108_SCREEN_HEIGHT	64
#define TEXTFONT	Ubuntu_9
#define VALUEFONT	Ubuntu_bold_14

#define ROUNDNESS	3
#define DEBUG

#define BUTTON_UP_X		(KS0108_SCREEN_WIDTH/2)+37
#define BUTTON_UP_Y		23
#define BUTTON_UP_WIDTH	15
#define BUTTON_UP_HEIGHT 10

#define BUTTON_DOWN_X	(KS0108_SCREEN_WIDTH/2)+37
#define BUTTON_DOWN_Y	33
#define BUTTON_DOWN_WIDTH	15
#define BUTTON_DOWN_HEIGHT 10

#define BATTERY_X		1
#define BATTERY_Y		(KS0108_SCREEN_HEIGHT - 3)
#define BATTERY_WIDTH	(KS0108_SCREEN_WIDTH -2)
#define BATTERY_HEIGHT	2

#define MAXWAIT			512


#endif /* MAIN_H_ */