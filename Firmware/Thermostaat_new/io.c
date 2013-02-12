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
	
	DDR_CVP |= CVP_ON | CVP_OFF;
	PORT_CVP &= ~(CVP_ON | CVP_OFF);
	
	DDR_LED |= LED;
	PORT_LED &= ~LED;
	
	//Enable pin change interrupt:
	PCICR |= (1 << PCIE2);
	PCMSK2 |= (1 << PCINT19);
	
}


void checkButtons(void){
	if(CHECKFLAG(FLAG_AWAKE)){
		if((PIN_BUTTONS & BUTTON_ON) == 0){
			//Set preset
			activePreset = &prs_sun;
			setTemp = activePreset->setTemp;
			SETDRAWFLAG(DRAW_PRESET);
			lastAction = 0;
		}
		if((PIN_BUTTONS & BUTTON_OFF) == 0){
			//Set preset
			activePreset = &prs_moon;
			setTemp = activePreset->setTemp;
			SETDRAWFLAG(DRAW_PRESET);
			lastAction = 0;
		}
	}else{
		if((PIN_BUTTONS & BUTTON_WAKE) == 0){
			//Pressed me!
			/*turnLcdOn();
			SETDRAWFLAG(DRAW_ALL);
			if(CHECKFLAG(FLAG_CV_ON)){
				SETDRAWFLAG(DRAW_CV_ON);
			}
			SETFLAG(FLAG_READTIME);
			lastAction = 0;	*/
		}
	}
}

ISR(PCINT2_vect){
	if(!CHECKFLAG(FLAG_AWAKE)){
		//Come out of sleep mode
		SETFLAG(FLAG_WAKE);
	}
	if(PORT_LED & LED){
		LED_UIT();
	}else{
		LED_AAN();
	}
}