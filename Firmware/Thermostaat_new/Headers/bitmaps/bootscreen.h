/*******************************************************************************
* image
* filename: E:/repositories/git/12009 - Thermostaat/Firmware/Thermostaat/headers/bitmaps/bootscreen.xml
* name: logo
*
* preset name: K-4U_LCD
* data block size: 8 bit(s), uint8_t
* RLE compression enabled: no
* conversion type: Monochrome, Ordered Dither 0
* bits per pixel: 1
*
* preprocess:
*  main scan direction: left to right
*  line scan direction: backward
*  inverse: yes
*******************************************************************************/

/*
 typedef struct {
     const uint8_t *data;
     uint16_t width;
     uint16_t height;
     } tImage;
*/
#include <stdint.h>


static uint8_t logo[] PROGMEM = {
	128, 64,
    0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x81, 
    0x81, 0x81, 0x81, 0x81, 0x01, 0x01, 0x01, 0x01, 
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xf9, 0xf9, 
    0xf9, 0xf9, 0x39, 0x39, 0x39, 0x39, 0x01, 0x01, 
    0x01, 0x81, 0x81, 0x81, 0x81, 0x01, 0x01, 0x01, 
    0x01, 0x01, 0x01, 0x01, 0x81, 0x81, 0x81, 0x81, 
    0x81, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x81, 0x81, 
    0x81, 0x81, 0x81, 0x01, 0x01, 0x01, 0x01, 0x01, 
    0x01, 0x81, 0x81, 0x81, 0x81, 0x01, 0x01, 0x01, 
    0x01, 0x01, 0x01, 0x01, 0x01, 0x81, 0x81, 0x81, 
    0x81, 0x01, 0x01, 0x01, 0x39, 0x39, 0x39, 0x39, 
    0xf9, 0xf9, 0xf9, 0xf9, 0x01, 0x01, 0x01, 0xff, 
    0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
    0x00, 0x00, 0x24, 0xff, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
    0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0xff, 0xff, 0xff, 0xff, 0x80, 0xc0, 0xe0, 
    0xf0, 0xf8, 0x3e, 0x1f, 0x1f, 0x0f, 0x07, 0x03, 
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x80, 0xc0, 0xf0, 0xf8, 0xfc, 0x7e, 0x1f, 0xff, 
    0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 
    0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 
    0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1f, 
    0x08, 0x08, 0x09, 0x1f, 0xe0, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
    0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x1f, 0x3f, 
    0x7f, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 
    0x00, 0x00, 0x00, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 
    0x1c, 0x1c, 0x1c, 0x00, 0x00, 0xf0, 0xfc, 0xfe, 
    0xff, 0xff, 0xe7, 0xe1, 0xe0, 0xe0, 0xe0, 0xff, 
    0xff, 0xff, 0xff, 0xe0, 0xe0, 0x00, 0x00, 0x00, 
    0x00, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xff, 0xff, 
    0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 
    0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 
    0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
    0x02, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x80, 
    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
    0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 
    0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x01, 0x03, 0x0f, 0x1f, 0x1f, 0x1f, 
    0x1c, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 
    0x1f, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x03, 0x07, 0x0f, 0x1f, 0x1f, 0x1e, 
    0x1e, 0x1e, 0x1e, 0x1f, 0x1f, 0x0f, 0x07, 0x03, 
    0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 
    0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 
    0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
    0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x06, 0x06, 
    0xfe, 0xfe, 0x06, 0x06, 0x06, 0x06, 0x00, 0xff, 
    0xff, 0x30, 0x30, 0x30, 0x30, 0x70, 0xe0, 0xc0, 
    0x00, 0x00, 0x80, 0xe0, 0x60, 0x30, 0x31, 0x31, 
    0x71, 0xe1, 0xc1, 0x01, 0x01, 0xf1, 0xf0, 0x30, 
    0x30, 0x30, 0x30, 0x00, 0xf0, 0xf0, 0x30, 0x30, 
    0x30, 0x70, 0xe0, 0xe0, 0x30, 0x30, 0x30, 0x70, 
    0xe0, 0xc0, 0x00, 0x00, 0x80, 0xe0, 0x70, 0x30, 
    0x30, 0x30, 0x70, 0xe0, 0x80, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 
    0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0xff, 
    0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
    0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x3f, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 
    0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 
    0x00, 0x00, 0x0f, 0x1f, 0x3b, 0x33, 0x33, 0x33, 
    0x33, 0x33, 0x03, 0x00, 0x00, 0x3f, 0x3f, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x00, 0x00, 
    0x00, 0x00, 0x3f, 0x3f, 0x00, 0x00, 0x00, 0x00, 
    0x3f, 0x3f, 0x00, 0x00, 0x07, 0x1f, 0x38, 0x30, 
    0x30, 0x30, 0x38, 0x1f, 0x07, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 
    0x0c, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
    0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 
    0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0xff, 0xff, 0x03, 0x03, 0x03, 0x07, 0xfe, 
    0xfe, 0x03, 0x03, 0x03, 0x07, 0xfe, 0xfc, 0x00, 
    0x00, 0xf8, 0xfe, 0xb6, 0x33, 0x33, 0x33, 0x37, 
    0x3e, 0x3c, 0x00, 0x00, 0xe0, 0xf3, 0x1b, 0x1b, 
    0x1b, 0x1b, 0xfe, 0xfc, 0x00, 0x00, 0x1e, 0x1f, 
    0x33, 0x33, 0xe3, 0xe0, 0x00, 0x00, 0xff, 0xff, 
    0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0xff, 0xff, 
    0x03, 0x03, 0x03, 0x03, 0x00, 0x78, 0xfe, 0x87, 
    0x03, 0x03, 0x03, 0x87, 0xfe, 0x78, 0x00, 0x00, 
    0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
    0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
    0x80, 0x83, 0x83, 0x80, 0x80, 0x80, 0x80, 0x83, 
    0x83, 0x80, 0x80, 0x80, 0x80, 0x83, 0x83, 0x80, 
    0x80, 0x80, 0x81, 0x83, 0x83, 0x83, 0x83, 0x83, 
    0x83, 0x80, 0x80, 0x80, 0x80, 0x81, 0x83, 0x83, 
    0x83, 0x83, 0x83, 0x83, 0x80, 0x80, 0x83, 0x83, 
    0x83, 0x83, 0x83, 0x81, 0x80, 0x80, 0x81, 0x83, 
    0x83, 0x83, 0x83, 0x83, 0x80, 0x80, 0x83, 0x83, 
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0x83, 
    0x83, 0x83, 0x83, 0x83, 0x81, 0x80, 0x80, 0x98, 
    0x98, 0x9f, 0x9f, 0x80, 0x80, 0x80, 0x80, 0x80, 
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff
};