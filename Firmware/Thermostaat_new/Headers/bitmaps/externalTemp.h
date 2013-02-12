/*******************************************************************************
* image
* filename: E:/repositories/git/12009 - Thermostaat/Firmware/Thermostaat_new/Headers/bitmaps/externalTemp.xml
* name: externalTemp
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


static uint8_t externalTemp[] PROGMEM = {
	8, 8,
    0xfc, 
    0x82, 
    0x81, 
    0x92, 
    0x10, 
    0x54, 
    0x38, 
    0x10
};
