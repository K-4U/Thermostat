#include <avr/pgmspace.h>
#include "structs.h"
#define LCD_WIDTH 128
#ifndef BITMAP_H
#define BITMAP_H
#include "bitmaps/bootscreen.h"
#include "bitmaps/flame.h"
#include "bitmaps/sun.h"
#include "bitmaps/moon.h"
#include "bitmaps/batteryIndicator.h"

extern void loadImage(const uint8_t x, const uint8_t y, const uint8_t *img);
extern void loadImageInverted(const uint8_t x, const uint8_t y, const uint8_t *img);
#endif