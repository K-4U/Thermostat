
/*
 * progressbar.h
 *
 * Created: 2-2-2013 14:29:33
 *  Author: Koen Beckers
 */ 
#include <stdint.h>
#include "structs.h"


#ifndef BATTERYBAR_H_
#define BATTERYBAR_H_


typedef struct{
	uint16_t value;
	uint16_t max;
	uint8_t y;
} batteryBar;

extern batteryBar createBatteryBar(uint16_t value, uint16_t max, uint8_t y);
extern void updateBar(batteryBar *pb, uint8_t value);
extern void drawBar(batteryBar *pb);


#endif /* BATTERYBAR_H_ */