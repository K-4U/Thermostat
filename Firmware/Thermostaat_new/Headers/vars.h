/*
 * vars.h
 *
 * Created: 7-2-2013 15:12:03
 *  Author: Koen Beckers
 */ 


#ifndef VARS_H_
#define VARS_H_

//Global vars
PROTO const preset prs_sun PRESET_SUN;
PROTO const preset prs_moon PRESET_MOON;
PROTO char *dayNames[7] DAYNAMES;

PROTO double oldCurrentTemp;
PROTO double setTemp;
PROTO double oldSetTemp;
PROTO uint8_t lastAction;
PROTO preset *activePreset;

PROTO uint16_t flags;
PROTO uint16_t drawFlags;

PROTO dateTime currentDateTime;


PROTO square buttonUp;
PROTO square buttonDown;
PROTO square buttonPreset;
PROTO square buttonAway;
PROTO square preset_sun;
PROTO square preset_moon;

PROTO square awayscreenButtonCancel;
PROTO square awayscreenButtonOk;
PROTO square awayscreenButtonDayUp;
PROTO square awayscreenButtonMonthUp;
PROTO square awayscreenButtonHourUp;
PROTO square awayscreenButtonMinuteUp;
PROTO square awayscreenButtonDayDown;
PROTO square awayscreenButtonMonthDown;
PROTO square awayscreenButtonHourDown;
PROTO square awayscreenButtonMinuteDown;


PROTO uint8_t batteryLevel;
PROTO uint8_t oldBatteryLevel;

PROTO progressBar batteryBar;
PROTO progressBar ttlBar;

PROTO uint8_t button_pressed;

PROTO tempSensor tempIntern;
PROTO tempSensor tempExtern;

PROTO dateTime timeOfReturn;


#endif /* VARS_H_ */