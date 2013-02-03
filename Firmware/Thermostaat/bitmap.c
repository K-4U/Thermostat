//************************************************************************
// Bitmap.C
//************************************************************************
#include <avr/pgmspace.h>
#include "headers/bitmap.h"
#include "headers/ks0108.h"
#include "headers/structs.h"
//##########################################################
void loadImage(const uint8_t x, const uint8_t y, const uint8_t *bitmap){
	uint8_t x_, y_ ,by;
	uint8_t maxWidth = pgm_read_byte(bitmap++);
	uint8_t maxHeight = pgm_read_byte(bitmap++);
	for(y_=0; y_ < maxHeight; y_+=8)

	for(x_=0; x_ < maxWidth; x_++){
		by=pgm_read_byte(bitmap++);
		ks0108GotoXY(x_+x, y_+y);
		ks0108WriteData(by);
	}
}
void loadImageInverted(const uint8_t x, const uint8_t y, const uint8_t *bitmap){
	uint8_t x_, y_ ,by;
	uint8_t maxWidth = pgm_read_byte(bitmap++);
	uint8_t maxHeight = pgm_read_byte(bitmap++);
	for(y_=0; y_ < maxHeight; y_+=8)

	for(x_=0; x_ < maxWidth; x_++){
		by=pgm_read_byte(bitmap++);
		ks0108GotoXY(x_+x, y_+y);
		ks0108WriteData(~by);
	}
}