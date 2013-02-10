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

PROTO double oldCurrentTemp;
PROTO double currentTemp;
PROTO double setTemp;
PROTO double oldSetTemp;
PROTO uint8_t lastAction;
PROTO preset *activePreset;
PROTO dateTime currentDateTime;

PROTO uint16_t flags;
PROTO uint16_t drawFlags;

PROTO dateTime currentDateTime;


PROTO square buttonUp;
PROTO square buttonDown;
PROTO square buttonPreset;
PROTO square buttonAway;
PROTO square preset_sun;
PROTO square preset_moon;

PROTO uint8_t batteryLevel;
PROTO uint8_t oldBatteryLevel;

PROTO progressBar batteryBar;
PROTO progressBar ttlBar;

PROTO uint8_t button_pressed;

PROTO tempSensor tempIntern;
PROTO tempSensor tempExtern;


#endif /* VARS_H_ */