/*
 * glcdFunctions.c
 *
 * Created: 7-2-2013 16:14:25
 *  Author: Koen Beckers
 */ 
#include <util/delay.h>
#include "Headers/config.h"
#include "Headers/display.h"
#include "Headers/glcdFunctions.h"
#include "Headers/adc.h"
#include "Headers/progressBar.h"

lcdPos stylus;
lcdPos oldStylus;

void turnLcdOn(void){
	LCD_AAN();
	SETFLAG(FLAG_AWAKE);
	for(volatile uint16_t i=0; i<15000; i++);
	displayInit(0);
	drawMainScreen();
}

void turnLcdOff(void){
	LCD_UIT();
	RESETFLAG(FLAG_AWAKE);
}

void init_display(void){
	displayInit(0);
	SETFLAG(FLAG_AWAKE);
	for(volatile uint16_t i=0; i<15000; i++);
	
	loadImageInverted(0,0,logo);
	_delay_ms(200);
	loadImage(0,0,logo);
	
	_delay_ms(1000);
	
	displayClearScreen();
	
	batteryBar	= createProgressBar(batteryLevel, 256, TOPBAR_Y+1);
	ttlBar		= createProgressBar(MAX_LAST_ACTION - lastAction, MAX_LAST_ACTION, DISPLAY_SCREEN_HEIGHT-1);
	drawBar(&batteryBar);
	drawBar(&ttlBar);
}

void drawTopHeader(){
	drawTime();
	drawDate();
	
	displayDrawHoriLine(0, TOPBAR_Y,DISPLAY_SCREEN_WIDTH, BLACK);
	drawBatteryBar();
}

void drawBatteryBar(){
	if(CHECKDRAWFLAG(DRAW_BATTERY_BAR)){
		updateBar(&batteryBar, batteryLevel);
		RESETDRAWFLAG(DRAW_BATTERY_BAR);
	}
	if(CHECKDRAWFLAG(DRAW_BATTERY_LOW)){
		RESETDRAWFLAG(DRAW_BATTERY_LOW);
		loadImage(BATTERY_X,BATTERY_Y,batteryIndicator);
	}
}

void drawTtlBar(){
	if(CHECKDRAWFLAG(DRAW_TTL_BAR)){
		updateBar(&ttlBar, MAX_LAST_ACTION - lastAction);
		RESETDRAWFLAG(DRAW_TTL_BAR);
	}		
}

void loadImage(const uint8_t x, const uint8_t y, const uint8_t *bitmap){
	uint8_t x_, y_ ,by;
	uint8_t maxWidth = pgm_read_byte(bitmap++);
	uint8_t maxHeight = pgm_read_byte(bitmap++);
	for(y_=0; y_ < maxHeight; y_+=8)

	for(x_=0; x_ < maxWidth; x_++){
		by=pgm_read_byte(bitmap++);
		displayGotoXY(x_+x, y_+y);
		displayWriteData(by);
	}
}
void loadImageInverted(const uint8_t x, const uint8_t y, const uint8_t *bitmap){
	uint8_t x_, y_ ,by;
	uint8_t maxWidth = pgm_read_byte(bitmap++);
	uint8_t maxHeight = pgm_read_byte(bitmap++);
	for(y_=0; y_ < maxHeight; y_+=8)

	for(x_=0; x_ < maxWidth; x_++){
		by=pgm_read_byte(bitmap++);
		displayGotoXY(x_+x, y_+y);
		displayWriteData(~by);
	}
}


void drawTime(){
	if(CHECKDRAWFLAG(DRAW_TIME)){
		RESETDRAWFLAG(DRAW_TIME);
		displaySelectFont(TEXTFONT, displayReadFontData, BLACK);
		displayFillRect(TIME_X, TIME_Y, 30+5, 7, WHITE);
		displayGotoXY(TIME_X, TIME_Y);
		displayPutChar((currentDateTime.time.hours / 10)+48);
		displayPutChar((currentDateTime.time.hours % 10)+48);
		displayPutChar(':');
		displayPutChar((currentDateTime.time.minute / 10)+48);
		displayPutChar((currentDateTime.time.minute % 10)+48);
		displayPutChar(':');
		displayPutChar((currentDateTime.time.seconds / 10)+48);
		displayPutChar((currentDateTime.time.seconds % 10)+48);
	}	
}

void drawDate(){
	if(CHECKDRAWFLAG(DRAW_DATE)){
		RESETDRAWFLAG(DRAW_DATE);
		displaySelectFont(TEXTFONT, displayReadFontData, BLACK);
		displayFillRect(DATE_X, DATE_Y, 40, 7, WHITE);
		displayGotoXY(DATE_X, DATE_Y);
	
		displayPutChar((currentDateTime.date.date / 10) + 48);
		displayPutChar((currentDateTime.date.date % 10) + 48);
		displayPutChar('-');
		displayPutChar((currentDateTime.date.month / 10) + 48);
		displayPutChar((currentDateTime.date.month % 10) + 48);
		displayPutChar('-');
		displayPutChar((currentDateTime.date.year / 10) + 48);
		displayPutChar((currentDateTime.date.year % 10) + 48);
	}	
}


void drawMainScreen(){
	displaySelectFont(TEXTFONT, displayReadFontData,BLACK);
	drawTopHeader();
	drawValues();
	drawPresetActive();
	drawTtlBar();
	
	if(CHECKFLAG(FLAG_CV_ON)){
		loadImage(FLAME_X,FLAME_Y, flame);
	}
	
	//And.. the buttons!
	drawMainScreenButtons(button_pressed);
	
	
	drawAwayScreen();
	
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
	
	buttonAway.x = BUTTON_AWAY_X;
	buttonAway.y = BUTTON_AWAY_Y;
	buttonAway.width = BUTTON_AWAY_WIDTH;
	buttonAway.height = BUTTON_AWAY_HEIGHT;
}


void drawAwayScreen(){
	if(CHECKFLAG(DRAW_AWAYSCREEN)){
		RESETDRAWFLAG(DRAW_AWAYSCREEN);
		//First, clear the field.
		displayFillRect(AWAYSCREEN_X - 1, AWAYSCREEN_Y - 1, AWAYSCREEN_WIDTH + 2, AWAYSCREEN_WIDTH + 2, WHITE);
		displayDrawRect(AWAYSCREEN_X, AWAYSCREEN_Y, AWAYSCREEN_WIDTH, AWAYSCREEN_HEIGHT, BLACK);
		
		//Then, draw the 3 fields.
		displayDrawRect(AWAYSCREEN_X + 2, AWAYSCREEN_FIELDS_Y, 20, UBUNTU_BOLD_14_HEIGHT + 2, BLACK);
		displayDrawRect(AWAYSCREEN_X + 2 + (20 * 1) + 2, AWAYSCREEN_FIELDS_Y, 20, UBUNTU_BOLD_14_HEIGHT + 2, BLACK);
		displayDrawRect(AWAYSCREEN_X + 2 + (20 * 2) + 2, AWAYSCREEN_FIELDS_Y, 20, UBUNTU_BOLD_14_HEIGHT + 2, BLACK);
	}		
}

//Active. 0 = none, 1 = UP, 2 = DOWN, 2 = PRESET
void drawMainScreenButtons(const uint8_t active){
	if(CHECKDRAWFLAG(DRAW_BUTTONS)){
		RESETDRAWFLAG(DRAW_BUTTONS);
		displayFillRect(BUTTON_UP_X, BUTTON_UP_Y, BUTTON_UP_WIDTH, BUTTON_UP_HEIGHT, WHITE);
		displayFillRect(BUTTON_DOWN_X, BUTTON_DOWN_Y, BUTTON_DOWN_WIDTH, BUTTON_DOWN_HEIGHT, WHITE);
		displayFillRect(BUTTON_PRES_X, BUTTON_PRES_Y, BUTTON_PRES_WIDTH, BUTTON_PRES_HEIGHT, WHITE);
		displayFillRect(BUTTON_AWAY_X, BUTTON_AWAY_Y, BUTTON_AWAY_WIDTH, BUTTON_AWAY_HEIGHT, WHITE);
	
		displayDrawRect(BUTTON_UP_X, BUTTON_UP_Y, BUTTON_UP_WIDTH, BUTTON_UP_HEIGHT, BLACK);
		displayDrawRect(BUTTON_DOWN_X, BUTTON_DOWN_Y, BUTTON_DOWN_WIDTH, BUTTON_DOWN_HEIGHT, BLACK);
		displayDrawRect(BUTTON_PRES_X, BUTTON_PRES_Y, BUTTON_PRES_WIDTH, BUTTON_PRES_HEIGHT, BLACK);
		displayDrawRect(BUTTON_AWAY_X, BUTTON_AWAY_Y, BUTTON_AWAY_WIDTH, BUTTON_AWAY_HEIGHT, WHITE);
		
	
		//Draw the minus
		uint8_t x1 = BUTTON_DOWN_X+4;
		uint8_t x2 = x1 + 4;
		uint8_t y = BUTTON_DOWN_Y+4;
		displayDrawLine(x1,y,x2,y,BLACK);
	
		//Draw the plus
		x1 = BUTTON_UP_X+4;
		x2 = x1 + 4;
		uint8_t y1 = BUTTON_UP_Y+4;
	
		displayDrawLine(x1,y1,x2,y1,BLACK);
	
		x1 = BUTTON_UP_X+6;
		y1 = BUTTON_UP_Y+2;
		uint8_t y2 = y1 + 4;
	
		displayDrawLine(x1,y1,x1,y2,BLACK);
	
	
		//And the arrow
		if(CHECKFLAG(FLAG_DRAWER)){
			displayFillRect(BUTTON_PRES_X+1, BUTTON_PRES_Y + BUTTON_PRES_HEIGHT-1,BUTTON_PRES_WIDTH-2, 2,WHITE);
			x1 = BUTTON_PRES_X + 4;
			x2 = BUTTON_PRES_X + 6;
			y1 = BUTTON_PRES_Y + 5;
			y2 = BUTTON_PRES_Y + 3;
			displayDrawLine(x1,y1,x2,y2,BLACK);
	
			x1 = BUTTON_PRES_X + 8;
			displayDrawLine(x1,y1,x2,y2,BLACK);
		}else{
			x1 = BUTTON_PRES_X + 4;
			x2 = BUTTON_PRES_X + 6;
			y1 = BUTTON_PRES_Y + 3;
			y2 = BUTTON_PRES_Y + 5;
			displayDrawLine(x1,y1,x2,y2,BLACK);
	
			x1 = BUTTON_PRES_X + 8;
			displayDrawLine(x1,y1,x2,y2,BLACK);
		}	
	
		//displayGotoXY(BUTTON_DOWN_X+((BUTTON_DOWN_WIDTH-8)/2)+1,BUTTON_DOWN_Y+((BUTTON_DOWN_HEIGHT-10)/2));
		//displayPutChar('-');
	
		if(active == 1){
			displayInvertRect(BUTTON_UP_X, BUTTON_UP_Y, BUTTON_UP_WIDTH, BUTTON_UP_HEIGHT);
		}else if(active == 2){
			displayInvertRect(BUTTON_DOWN_X, BUTTON_DOWN_Y, BUTTON_DOWN_WIDTH, BUTTON_DOWN_HEIGHT);
		}else if(active == 3){
			displayInvertRect(BUTTON_PRES_X, BUTTON_PRES_Y, BUTTON_PRES_WIDTH, BUTTON_PRES_HEIGHT);
		}else if(active == 4){
			displayInvertRect(BUTTON_AWAY_X, BUTTON_AWAY_Y, BUTTON_AWAY_WIDTH, BUTTON_AWAY_HEIGHT);
		}
	}		
}

void drawValues(){
	if(CHECKDRAWFLAG(DRAW_CURRENT)){
		RESETDRAWFLAG(DRAW_CURRENT);
		displayFillRect(CURRENT_X,CURRENT_Y,60,20,WHITE);
		displayGotoXY(CURRENT_X, CURRENT_Y);
		displaySelectFont(LARGEVALUEFONT,displayReadFontData,BLACK);
	
		displayPutChar((currentTemp / 10) + 48);
		displayPutChar(((uint8_t)currentTemp % 10) + 48);
		displayPutChar('.');
		displayPutChar(((uint8_t)(currentTemp * 10) % 10) + 48);
	
		//Draw degree
		displayDrawCircle(CURRENT_X+47,20, 3, BLACK)
		displayDrawCircle(CURRENT_X+47,20, 2, BLACK)
	}
	
	if(CHECKDRAWFLAG(DRAW_SET)){
		RESETDRAWFLAG(DRAW_SET);
		//And the set temperature
		displaySelectFont(SMALLVALUEFONT,displayReadFontData,BLACK);
		//uint8_t fWidth = displayStringWidth(setTempStr);
		displayFillRect(SET_X,SET_Y,20,UBUNTU_BOLD_14_HEIGHT, WHITE);
	
		displayGotoXY(SET_X, SET_Y);
		displayPutChar((setTemp / 10) + 48);
		displayPutChar(((uint8_t)setTemp % 10) + 48);
		displayPutChar('.');
		displayPutChar(((uint8_t)(setTemp * 10) % 10) + 48);
	
		//Draw degree
		displayDrawCircle(SET_X+26,SET_Y, 2, BLACK)
		//displayDrawRoundRect(DISPLAY_SCREEN_WIDTH/2,23,35,20,ROUNDNESS,BLACK);
	}	
}

/*
 * PRESET DRAWER
 */
void drawPresetDrawer(void){
	if(CHECKDRAWFLAG(DRAW_DRAWER)){
		RESETDRAWFLAG(DRAW_DRAWER);
		displayFillRect(BUTTON_PRES_X - 32, BUTTON_PRES_Y + BUTTON_PRES_HEIGHT + 1,BUTTON_PRES_WIDTH + 32, 12,WHITE);
		displayDrawRect(BUTTON_PRES_X - 32, BUTTON_PRES_Y + BUTTON_PRES_HEIGHT + 1,BUTTON_PRES_WIDTH + 32, 12,BLACK);
		displayFillRect(BUTTON_PRES_X+1, BUTTON_PRES_Y + BUTTON_PRES_HEIGHT-1,BUTTON_PRES_WIDTH-2, 2,WHITE);
	
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
}

void closePresetDrawer(void){
	displayFillRect(BUTTON_PRES_X - 32, BUTTON_PRES_Y + BUTTON_PRES_HEIGHT + 1,BUTTON_PRES_WIDTH + 32, 12,WHITE);
}

void drawPresetActive(void){
	if(CHECKDRAWFLAG(DRAW_PRESET)){
		RESETDRAWFLAG(DRAW_PRESET);
		displayFillRect(PRESET_X, PRESET_Y, 9, 9, WHITE);
		loadImage(PRESET_X, PRESET_Y, activePreset->image);
	}	
}


uint8_t isIn(const lcdPos *pos, const square *obj){
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

uint8_t isDifferent(const lcdPos *p1, const lcdPos *p2){
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

/*
 * TOUCHSCREEN
 */

lcdPos readPos(void){
	lcdPos retPos;
	//read X
	//1 = output
    //0 = input
	//        76543210
	DDR_TOUCH &= ~(_BV(TOUCH_1) | _BV(TOUCH_2) | _BV(TOUCH_3) | _BV(TOUCH_4)); //DDRA &= 0b11110000;
	DDR_TOUCH |= _BV(TOUCH_1) | _BV(TOUCH_3); //DDRA |= 0b00000101;
	PORT_TOUCH &= ~(_BV(TOUCH_1) | _BV(TOUCH_2) | _BV(TOUCH_3) | _BV(TOUCH_4));// PORTA &=0b11110000;
	PORT_TOUCH |= _BV(TOUCH_3);//PORTA |=0b00000100;
	
	//_delay_ms(20);

    uint8_t resX = read_adc(TOUCH_2);
	uint8_t rawX = resX;
	uint8_t a3 = read_adc(TOUCH_4);
	
	//printf("rawX: %i   A3: %i   dif: %i\r\n",rawX,a3,a3-rawX);
	
	resX = resX - 22;
	retPos.x = resX / 1.5625;
	
	//Read Y
	//1 = output
    //0 = input
	//        76543210
	DDR_TOUCH &= ~(_BV(TOUCH_1) | _BV(TOUCH_2) | _BV(TOUCH_3) | _BV(TOUCH_4)); //DDRA &= 0b11110000;
	DDR_TOUCH |= _BV(TOUCH_2) | _BV(TOUCH_4); //DDRA |= 0b00001010;
	PORT_TOUCH &= ~(_BV(TOUCH_1) | _BV(TOUCH_2) | _BV(TOUCH_3) | _BV(TOUCH_4));// PORTA &=0b11110000;
	PORT_TOUCH |= _BV(TOUCH_4); //PORTA |=0b00001000;
	
	//_delay_ms(20);

    uint8_t resY = 255 - read_adc(TOUCH_1);
	uint8_t rawY = resY;
	uint8_t a2 = 255 - read_adc(TOUCH_3);
	resY = resY - 40;
	retPos.y = resY / 2.765625;
	
	
	
	if(((a3 - rawX) == 0) && ((a2 - rawY) == 0)){
		retPos.isPressed = 1;
	}else{
		retPos.isPressed = 0;
	}
	
	return retPos;
}


void readAndHandleScreen(void){
	if(CHECKFLAG(FLAG_AWAKE)){
		stylus = readPos();
		uint8_t posDiff = 0;
		if((posDiff = isDifferent(&stylus, &oldStylus))){
			if(posDiff & DIFF_P){
				if(stylus.isPressed){
					if(isIn(&stylus,&buttonDown)){
						button_pressed = 2;
						SETDRAWFLAG(DRAW_BUTTONS);
						setTemp-=0.5;
					}else if(isIn(&stylus,&buttonUp)){
						button_pressed = 1;
						SETDRAWFLAG(DRAW_BUTTONS);
						setTemp+=0.5;
					}else if(isIn(&stylus, &buttonPreset)){
						button_pressed = 3;
						SETDRAWFLAG(DRAW_BUTTONS);
						SETDRAWFLAG(DRAW_DRAWER);
						if(CHECKFLAG(FLAG_DRAWER)){
							closePresetDrawer();
							RESETFLAG(FLAG_DRAWER);
						}else{
							SETDRAWFLAG(DRAW_DRAWER);	
							SETFLAG(FLAG_DRAWER);
						}							
					}
					if(CHECKFLAG(FLAG_DRAWER)){
						if(isIn(&stylus,&preset_sun)){
							*activePreset = prs_sun;
							setTemp = activePreset->setTemp;
							closePresetDrawer();
							RESETFLAG(FLAG_DRAWER);
							SETDRAWFLAG(DRAW_PRESET);
						}else if(isIn(&stylus, &preset_moon)){
							*activePreset = prs_moon;
							setTemp = activePreset->setTemp;
							RESETFLAG(FLAG_DRAWER);
							closePresetDrawer();
							SETDRAWFLAG(DRAW_PRESET);
						}
					}
				}else{
					//That means it went up!
					SETDRAWFLAG(DRAW_BUTTONS);
					button_pressed = 0;
				}
				lastAction = 0;
			}				
			oldStylus = stylus;
				
		}
		if(oldSetTemp != setTemp){
			oldSetTemp = setTemp;
			SETDRAWFLAG(DRAW_SET);
		}
	}
}