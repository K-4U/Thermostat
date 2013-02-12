/*
 * config.h
 *
 * Created: 7-2-2013 15:13:10
 *  Author: Koen Beckers
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/power.h>
#include <avr/sleep.h>

#ifdef MAIN_C
#define PROTO
#define PRESET_SUN	= {sun, 18, {00,00,17}}
#define PRESET_MOON	= {Moon, 13, {00,00,23}}
#define DAYNAMES = {"Ma", "Di", "Wo", "Do", "Vr", "Za", "Zo"}
#else
#define PROTO extern
#define PRESET_SUN
#define PRESET_MOON
#define DAYNAMES
#endif

#include "bitmaps.h"
#include "fonts.h"
#include "structs.h"
#include "vars.h"
#include "draw.h"
#include "flags.h"
#include "pindefines.h"
#include "io.h"



//As J. Onokiewicz would call them: Magic numbers!
#define MINIMAL_BATTERY_LEVEL	20
#define MAX_LAST_ACTION			20
#define MIN_TEMP_AWAY			10

//Font
#define TEXTFONT		Ubuntu_9
#define SMALLVALUEFONT	Ubuntu_bold_14
#define LARGEVALUEFONT	ubuntu_bold_26


//UART
#define UART_BAUD  			19200




#endif /* CONFIG_H_ */