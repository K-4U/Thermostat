/*
 * progressbar.c
 *
 * Created: 2-2-2013 14:29:20
 *  Author: Koen Beckers
 */ 
#include "headers/progressbar.h"
#include "headers/ks0108.h"

progressBar createProgressBar(uint16_t value, uint16_t max, uint8_t x, uint8_t y, uint8_t width, uint8_t height){
	progressBar ret;
	ret.value = value;
	ret.max = max;
	square p;
	p.x = x;
	p.y = y;
	p.width = width;
	p.height = height;
	ret.pos = p;
	
	return ret;
}

void updateBar(progressBar *pb, uint8_t value){
	pb->value = value;
	drawBar(pb);
}

void drawBar(progressBar *pb){
	ks0108FillRect(pb->pos.x,pb->pos.y,pb->pos.width,pb->pos.height,WHITE);
	ks0108DrawRect(pb->pos.x,pb->pos.y,pb->pos.width,pb->pos.height,BLACK);
	
	//Calculate plox
	uint8_t widthToFill = (((pb->pos.width) * pb->value) / pb->max);
	ks0108FillRect(pb->pos.x, pb->pos.y + 1,widthToFill,pb->pos.height-2,BLACK);
}