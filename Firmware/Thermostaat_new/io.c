/*
 * io.c
 *
 * Created: 7-2-2013 16:22:34
 *  Author: Koen Beckers
 */ 
#include "Headers/config.h"
#include "Headers/io.h"
#include "Headers/glcdFunctions.h"

void init_io(void){
	//Init direction registers
	// 1 = output
	// 0 = input
	DDR_BUTTONS &= ~(BUTTON_WAKE | BUTTON_ON | BUTTON_OFF);
	PORT_BUTTONS |= BUTTON_WAKE | BUTTON_ON | BUTTON_OFF;
	
	DDR_LCD |= LCD;
	PORT_LCD &= ~LCD;
	
}


void checkButtons(void){
	if(CHECKFLAG(FLAG_AWAKE)){
		if((PIN_BUTTONS & BUTTON_ON) == 0){
			//Set preset
			*activePreset = prs_sun;
			setTemp = activePreset->setTemp;
			SETDRAWFLAG(DRAW_PRESET);
			lastAction = 0;
		}
		if((PIN_BUTTONS & BUTTON_OFF) == 0){
			//Set preset
			*activePreset = prs_moon;
			setTemp = activePreset->setTemp;
			SETDRAWFLAG(DRAW_PRESET);
			lastAction = 0;
		}
	}else{
		if((PIN_BUTTONS & BUTTON_WAKE) == 0){
			//Pressed me!
			turnLcdOn();
			SETDRAWFLAG(DRAW_ALL);
			lastAction = 0;	
		}
	}
}