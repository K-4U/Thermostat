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

typedef struct{
	uint8_t seconds;
	uint8_t minute;
	uint8_t hours;
	uint8_t day;
	uint8_t date;
	uint8_t month;
	uint8_t year;
} dateTime;


typedef struct {
	uint8_t *image;
	double setTemp;
} preset;

#endif /* STRUCTS_H_ */