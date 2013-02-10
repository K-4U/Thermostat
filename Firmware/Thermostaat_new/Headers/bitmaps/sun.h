/*******************************************************************************
* image
* filename: E:/repositories/git/12009 - Thermostaat/Firmware/Thermostaat/headers/bitmaps/sun.xml
* name: sun
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


static uint8_t sun[] PROGMEM = {
	9, 9,
    0x10, 0x92, 
    0x7c, 0x7c, 
    0xff, 0x7c, 
    0x7c, 0x92, 
    0x10, 0x00, 
    0x00, 0x00, 
    0x00, 0x01, 
    0x00, 0x00, 
    0x00, 0x00
};
