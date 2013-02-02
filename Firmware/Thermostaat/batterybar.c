/*
 * progressbar.c
 *
 * Created: 2-2-2013 14:29:20
 *  Author: Koen Beckers
 */ 
#include "headers/batterybar.h"
#include "headers/ks0108.h"
#include "headers/main.h"

batteryBar createBatteryBar(uint16_t value, uint16_t max, uint8_t y){
	batteryBar ret;
	ret.value = value;
	ret.max = max;
	ret.y = y;
	
	return ret;
}

void updateBar(batteryBar *pb, uint8_t value){
	pb->value = value;
	drawBar(pb);
}

void drawBar(batteryBar *pb){
	//Calculate plox
	uint8_t widthToFill = ((KS0108_SCREEN_WIDTH * pb->value) / pb->max);
	ks0108DrawHoriLine(0, pb->y, KS0108_SCREEN_WIDTH ,WHITE);
	ks0108DrawHoriLine(0, pb->y,widthToFill,BLACK);
	
}