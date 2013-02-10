/*******************************************************************************
* image
* filename: E:/repositories/git/12009 - Thermostaat/Firmware/Thermostaat/headers/bitmaps/batteryIndicator.xml
* name: battery_indicator
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


static uint8_t batteryIndicator[] PROGMEM = {
	24, 10,
    0xff, 0x01, 
    0xfd, 0x95, 
    0x95, 0x69, 
    0x01, 0xc1, 
    0x79, 0x45, 
    0x79, 0xc1, 
    0x01, 0x05, 
    0xfd, 0x04, 
    0x01, 0x05, 
    0xfd, 0x05, 
    0x01, 0xbd, 
    0x01, 0xff, 
    0x03, 0x02, 
    0x02, 0x02, 
    0x02, 0x02, 
    0x02, 0x02, 
    0x02, 0x02, 
    0x02, 0x02, 
    0x02, 0x02, 
    0x02, 0x02, 
    0x02, 0x02, 
    0x02, 0x02, 
    0x02, 0x02, 
    0x02, 0x03
};
