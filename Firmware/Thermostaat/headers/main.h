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
PROTO char currentDateStr[8];

#define LED			_BV(PD5)
#define LED_AAN()	PORTD |= LED
#define LED_UIT()	PORTD &= ~LED


#define KS0108_SCREEN_WIDTH		128
#define KS0108_SCREEN_HEIGHT	64
#define TEXTFONT		Ubuntu_9
#define SMALLVALUEFONT	Ubuntu_bold_14
#define LARGEVALUEFONT	ubuntu_bold_26

#define ROUNDNESS	3
#define DEBUG

#define BUTTON_DOWN_X			(KS0108_SCREEN_WIDTH/2)
#define BUTTON_DOWN_Y			SET_Y + UBUNTU_BOLD_14_HEIGHT + 2
#define BUTTON_DOWN_WIDTH		14
#define BUTTON_DOWN_HEIGHT		10

#define BUTTON_UP_X			BUTTON_DOWN_X + BUTTON_DOWN_WIDTH + 4
#define BUTTON_UP_Y			BUTTON_DOWN_Y
#define BUTTON_UP_WIDTH		14
#define BUTTON_UP_HEIGHT	10

#define CURRENT_X		3
#define CURRENT_Y		20
#define SET_X			(KS0108_SCREEN_WIDTH/2 + 2)
#define SET_Y			20

#define TOPBAR_Y		8

#define MAXWAIT			512


#endif /* MAIN_H_ */