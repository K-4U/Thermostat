/*
 * Author: Koen Beckers
 * Project: RoomControl
 * Module: Remote
 * File: glcdFunctions.c
 * Description:
 * Has functions for drawing basic stuff and the location grabbers
 */
#define GLCDFUNCTIONS_C

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include "headers/structs.h"
#include "headers/main.h"
#include "headers/glcdFunctions.h"
#include "headers/ks0108.h"
#include "headers/bitmap.h"

#include "fonts/ubuntu_8.h"
#include "fonts/ubuntu_bold_14.h"
#include "fonts/ubuntu_bold_26.h"


extern uint8_t read_adc(uint8_t adc_input);

void drawMenuHeader(){
	drawTime();
	drawDate();
	
	ks0108DrawHoriLine(0,TOPBAR_Y,KS0108_SCREEN_WIDTH,BLACK);
}

void drawTime(){
	ks0108SelectFont(TEXTFONT,ks0108ReadFontData,BLACK);
	ks0108FillRect(KS0108_SCREEN_WIDTH - 30-5,0,30+5,7,WHITE);
	ks0108GotoXY(KS0108_SCREEN_WIDTH - 30 - 3,0);
	ks0108PutChar((currentDateTime.hours / 10)+48);
	ks0108PutChar((currentDateTime.hours % 10)+48);
	ks0108PutChar(':');
	ks0108PutChar((currentDateTime.minute / 10)+48);
	ks0108PutChar((currentDateTime.minute % 10)+48);
	ks0108PutChar(':');
	ks0108PutChar((currentDateTime.seconds / 10)+48);
	ks0108PutChar((currentDateTime.seconds % 10)+48);
}

void drawDate(){
	sprintf(currentDateStr,"%02i-%02i-%02i",currentDateTime.date, currentDateTime.month, currentDateTime.year);
	
	ks0108SelectFont(TEXTFONT,ks0108ReadFontData,BLACK);
	uint8_t stringWidth = ks0108StringWidth(currentDateStr);
	ks0108FillRect(3,0,stringWidth,7,WHITE);
	ks0108GotoXY(3,0);
	ks0108Puts(currentDateStr);
}

void drawPresetDrawer(void){
	SETFLAG(FLAG_DRAWER);
	ks0108FillRect(BUTTON_PRES_X - 32, BUTTON_PRES_Y + BUTTON_PRES_HEIGHT + 1,BUTTON_PRES_WIDTH + 32, 12,WHITE);
	ks0108DrawRect(BUTTON_PRES_X - 32, BUTTON_PRES_Y + BUTTON_PRES_HEIGHT + 1,BUTTON_PRES_WIDTH + 32, 12,BLACK);
	ks0108FillRect(BUTTON_PRES_X+1, BUTTON_PRES_Y + BUTTON_PRES_HEIGHT-1,BUTTON_PRES_WIDTH-2, 2,WHITE);
	
	loadImage(BUTTON_PRES_X - 32 + 3,BUTTON_PRES_Y + BUTTON_PRES_HEIGHT + 3,sun);
	loadImage(BUTTON_PRES_X - 32 + 15,BUTTON_PRES_Y + BUTTON_PRES_HEIGHT + 3,Moon);
	
	preset_sun.x = BUTTON_PRES_X - 32 + 3;
	preset_sun.y = BUTTON_PRES_Y + BUTTON_PRES_HEIGHT + 3;
	preset_sun.width = 9;
	preset_sun.height = 9;
	
	preset_moon.x = BUTTON_PRES_X - 32 + 15;
	preset_moon.y = BUTTON_PRES_Y + BUTTON_PRES_HEIGHT + 3;
	preset_moon.width = 9;
	preset_moon.height = 9;
}

void closePresetDrawer(void){
	RESETFLAG(FLAG_DRAWER);
	ks0108FillRect(BUTTON_PRES_X - 32, BUTTON_PRES_Y + BUTTON_PRES_HEIGHT + 1,BUTTON_PRES_WIDTH + 32, 12,WHITE);
}

void drawPresetActive(void){
	ks0108FillRect(PRESET_X, PRESET_Y, 9, 9, WHITE);
	if(activePreset == &prs_sun){
		loadImage(PRESET_X, PRESET_Y, sun);
	}else{
		loadImage(PRESET_X, PRESET_Y, Moon);
	}
}

void drawMainScreen(){
	ks0108SelectFont(TEXTFONT, ks0108ReadFontData,BLACK);
	drawMenuHeader();

	
	drawValues();
	
	drawPresetActive();
	
	//And.. the buttons!
	drawMainScreenButtons(0);
	//Put it in the squares
	buttonDown.x = BUTTON_DOWN_X;
	buttonDown.y = BUTTON_DOWN_Y;
	buttonDown.width = BUTTON_DOWN_WIDTH;
	buttonDown.height = BUTTON_DOWN_HEIGHT;
	
	buttonUp.x = BUTTON_UP_X;
	buttonUp.y = BUTTON_UP_Y;
	buttonUp.width = BUTTON_UP_WIDTH;
	buttonUp.height = BUTTON_UP_HEIGHT;
	
	buttonPreset.x = BUTTON_PRES_X;
	buttonPreset.y = BUTTON_PRES_Y;
	buttonPreset.width = BUTTON_PRES_WIDTH;
	buttonPreset.height = BUTTON_PRES_HEIGHT;
}

uint8_t isIn(lcdPos *pos,square *obj){
	if((pos->x >= obj->x) && (pos->x <= (obj->width + obj->x))){
		//X is correct!
		if((pos->y >= obj->y) && (pos->y <= (obj->height + obj->y))){
			//And so is Y!
			return 1;
		}else{
			return 0;
		}
	}else{
		return 0;
	}
}

uint8_t isDifferent(lcdPos *p1, lcdPos *p2){
	uint8_t diff = 0;
	if((p1->x <= (p2->x-2)) || (p1->x >= (p2->x+2))){
		diff |= DIFF_X;
	}
	if((p1->y <= (p2->y-2)) || (p1->y >= (p2->y+2))){
		diff |= DIFF_Y;
	}	
	if(p1->isPressed != p2->isPressed){
		diff |= DIFF_P;
	}
	return diff;
}

void drawValues(){
	ks0108FillRect(CURRENT_X,CURRENT_Y,35,20,WHITE);
	ks0108GotoXY(CURRENT_X, CURRENT_Y);
	ks0108SelectFont(LARGEVALUEFONT,ks0108ReadFontData,BLACK);
	
	uint8_t fWidth = ks0108StringWidth(currentTempStr);
	ks0108Puts(currentTempStr);
	//Draw degree
	ks0108DrawCircle(fWidth+CURRENT_X+5,20, 3, BLACK)
	ks0108DrawCircle(fWidth+CURRENT_X+5,20, 2, BLACK)

	//And the set temperature
	ks0108SelectFont(SMALLVALUEFONT,ks0108ReadFontData,BLACK);
	fWidth = ks0108StringWidth(setTempStr);
	ks0108FillRect(SET_X,SET_Y,fWidth + 4,UBUNTU_BOLD_14_HEIGHT, WHITE);
	
	ks0108GotoXY(SET_X, SET_Y);
	
	ks0108Puts(setTempStr);
	//Draw degree
	ks0108DrawCircle(fWidth+SET_X+4,SET_Y, 2, BLACK)
	//ks0108DrawRoundRect(KS0108_SCREEN_WIDTH/2,23,35,20,ROUNDNESS,BLACK);
}


//Active. 0 = none, 1 = UP, 2 = DOWN, 2 = PRESET
void drawMainScreenButtons(uint8_t active){
	ks0108FillRect(BUTTON_UP_X,BUTTON_UP_Y,BUTTON_UP_WIDTH,BUTTON_UP_HEIGHT,WHITE);
	ks0108FillRect(BUTTON_DOWN_X,BUTTON_DOWN_Y,BUTTON_DOWN_WIDTH,BUTTON_DOWN_HEIGHT,WHITE);
	ks0108FillRect(BUTTON_PRES_X,BUTTON_PRES_Y,BUTTON_PRES_WIDTH,BUTTON_PRES_HEIGHT,WHITE);
	
	ks0108DrawRect(BUTTON_UP_X,BUTTON_UP_Y,BUTTON_UP_WIDTH,BUTTON_UP_HEIGHT,BLACK);
	ks0108DrawRect(BUTTON_DOWN_X,BUTTON_DOWN_Y,BUTTON_DOWN_WIDTH,BUTTON_DOWN_HEIGHT,BLACK);
	ks0108DrawRect(BUTTON_PRES_X,BUTTON_PRES_Y,BUTTON_PRES_WIDTH,BUTTON_PRES_HEIGHT,BLACK);
	
	//Draw the minus
	uint8_t x1 = BUTTON_DOWN_X+4;
	uint8_t x2 = x1 + 4;
	uint8_t y = BUTTON_DOWN_Y+4;
	ks0108DrawLine(x1,y,x2,y,BLACK);
	
	//Draw the plus
	x1 = BUTTON_UP_X+4;
	x2 = x1 + 4;
	uint8_t y1 = BUTTON_UP_Y+4;
	
	ks0108DrawLine(x1,y1,x2,y1,BLACK);
	
	x1 = BUTTON_UP_X+6;
	y1 = BUTTON_UP_Y+2;
	uint8_t y2 = y1 + 4;
	
	ks0108DrawLine(x1,y1,x1,y2,BLACK);
	
	
	//And the arrow
	if(CHECKFLAG(FLAG_DRAWER)){
		ks0108FillRect(BUTTON_PRES_X+1, BUTTON_PRES_Y + BUTTON_PRES_HEIGHT-1,BUTTON_PRES_WIDTH-2, 2,WHITE);
		x1 = BUTTON_PRES_X + 4;
		x2 = BUTTON_PRES_X + 6;
		y1 = BUTTON_PRES_Y + 5;
		y2 = BUTTON_PRES_Y + 3;
		ks0108DrawLine(x1,y1,x2,y2,BLACK);
	
		x1 = BUTTON_PRES_X + 8;
		ks0108DrawLine(x1,y1,x2,y2,BLACK);
	}else{
		x1 = BUTTON_PRES_X + 4;
		x2 = BUTTON_PRES_X + 6;
		y1 = BUTTON_PRES_Y + 3;
		y2 = BUTTON_PRES_Y + 5;
		ks0108DrawLine(x1,y1,x2,y2,BLACK);
	
		x1 = BUTTON_PRES_X + 8;
		ks0108DrawLine(x1,y1,x2,y2,BLACK);
	}	
	
	//ks0108GotoXY(BUTTON_DOWN_X+((BUTTON_DOWN_WIDTH-8)/2)+1,BUTTON_DOWN_Y+((BUTTON_DOWN_HEIGHT-10)/2));
	//ks0108PutChar('-');
	
	if(active == 1){
		ks0108InvertRect(BUTTON_UP_X,BUTTON_UP_Y,BUTTON_UP_WIDTH,BUTTON_UP_HEIGHT);
	}else if(active == 2){
		ks0108InvertRect(BUTTON_DOWN_X,BUTTON_DOWN_Y,BUTTON_DOWN_WIDTH,BUTTON_DOWN_HEIGHT);
	}else if(active == 3){
		ks0108InvertRect(BUTTON_PRES_X,BUTTON_PRES_Y,BUTTON_PRES_WIDTH,BUTTON_PRES_HEIGHT);
	}
	
	
}


void turnLcdOn(void){
	LCD_AAN();
	SETFLAG(FLAG_AWAKE);
	for(volatile uint16_t i=0; i<15000; i++);
	ks0108Init(0);
	drawMainScreen();
}

void turnLcdOff(void){
	LCD_UIT();
	RESETFLAG(FLAG_AWAKE);
}

lcdPos readPos(void){
	lcdPos retPos;
	//read X
	//1 = output
    //0 = input
	//        76543210
	DDRC &= 0b11110000;
	DDRC |= 0b00000101;
	PORTC &=0b11110000;
	PORTC |=0b00000100;
	
	//_delay_ms(20);

    uint8_t resX = read_adc(1);
	uint8_t rawX = resX;
	uint8_t a3 = read_adc(3);
	
	
	resX = resX - 22;
	retPos.x = resX / 1.5625;
	
	//Read Y
	//1 = output
    //0 = input
	//        76543210
	DDRC &= 0b11110000;
	DDRC |= 0b00001010;
	PORTC &=0b11110000;
	PORTC |=0b00001000;
	
	//_delay_ms(20);

    uint8_t resY = 255 - read_adc(0);
	uint8_t rawY = resY;
	uint8_t a2 = 255 - read_adc(2);
	resY = resY - 40;
	retPos.y = resY / 2.765625;
	
	
	
	if(((a3 - rawX) < 4) && ((a2 - rawY) < 4)){
		retPos.isPressed = 1;
	}else{
		retPos.isPressed = 0;
	}
	
	return retPos;
}