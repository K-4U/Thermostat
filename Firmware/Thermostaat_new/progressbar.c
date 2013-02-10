/*
 * progressbar.c
 *
 * Created: 7-2-2013 17:09:14
 *  Author: Koen Beckers
 */ 
#include "Headers/config.h"
#include "Headers/progressBar.h"
#include "Headers/display.h"


progressBar createProgressBar(const uint16_t value, const uint16_t max, const uint8_t y){
	progressBar ret;
	ret.value = value;
	ret.max = max;
	ret.y = y;
	
	return ret;
}

void updateBar(progressBar *pb, const uint8_t value){
	pb->value = value;
}

void drawBar(const progressBar *pb){
	//Calculate plox
	uint8_t widthToFill = ((DISPLAY_SCREEN_WIDTH * pb->value) / pb->max);
	displayDrawHoriLine(0, pb->y, DISPLAY_SCREEN_WIDTH ,WHITE);
	displayDrawHoriLine(0, pb->y,widthToFill,BLACK);
	
}