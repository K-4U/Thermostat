/*
 * structs.h
 *
 * Created: 2-2-2013 15:11:32
 *  Author: Koen Beckers
 */ 


#ifndef STRUCTS_H_
#define STRUCTS_H_
#define MENU_TEXTLEN 20

typedef struct{
    char acText[MENU_TEXTLEN];
    uint8_t iReturn;
} sMenuItem;

typedef struct{
	uint8_t x;
	uint8_t y;
	uint8_t isPressed;
} lcdPos;

typedef struct{
	uint8_t x;
	uint8_t y;
	uint8_t width;
	uint8_t height;
} square;




#endif /* STRUCTS_H_ */