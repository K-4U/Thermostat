#include <avr/pgmspace.h>
#include "structs.h"
#define LCD_WIDTH 128
#ifndef BITMAP_H
#define BITMAP_H
#include "bitmaps/bootscreen.h"
#include "bitmaps/flame.h"
#include "bitmaps/sun.h"
#include "bitmaps/moon.h"
//First width, then height
/*static uint8_t flame[] PROGMEM = {
	0x07, 0x09,
//    76543210
	0b01110000,
	0b11111000,
	0b10001100,
	0b00000111,
	0b10011110,
	0b11111000,
	0b01100000,
	0b00000000,
	0b00000000,
	0b00000001,
	0b00000001,
	0b00000001,
	0b00000000,
	0b00000000
};*/

extern void loadImage(const uint8_t x, const uint8_t y, const uint8_t *img);
extern void loadImageInverted(const uint8_t x, const uint8_t y, const uint8_t *img);
#endif