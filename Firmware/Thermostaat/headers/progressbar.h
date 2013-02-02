
/*
 * progressbar.h
 *
 * Created: 2-2-2013 14:29:33
 *  Author: Koen Beckers
 */ 
#include <stdint.h>
#include "structs.h"


#ifndef PROGRESSBAR_H_
#define PROGRESSBAR_H_


typedef struct{
	uint16_t value;
	uint16_t max;
	square pos;
} progressBar;

extern progressBar createProgressBar(uint16_t value, uint16_t max, uint8_t x, uint8_t y, uint8_t width, uint8_t height);
extern void updateBar(progressBar *pb, uint8_t value);
extern void drawBar(progressBar *pb);


#endif /* PROGRESSBAR_H_ */