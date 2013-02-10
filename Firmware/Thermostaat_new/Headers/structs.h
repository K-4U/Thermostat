/*
 * structs.h
 *
 * Created: 7-2-2013 15:14:00
 *  Author: Koen Beckers
 */ 


#ifndef STRUCTS_H_
#define STRUCTS_H_

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
} structTime;

typedef struct{
	uint8_t day;
	uint8_t date;
	uint8_t month;
	uint8_t year;
} structDate;

typedef struct{
	structTime time;
	structDate date;
} dateTime;


typedef struct {
	uint8_t *image;
	double setTemp;
	structTime onTime;
} preset;

typedef struct {
	uint8_t x;
	uint8_t y;
	uint8_t page;
} lcdCoord;

typedef struct {
	float lastReading;
	volatile uint8_t *port;
	volatile uint8_t *pin;
	volatile uint8_t *ddr;
	uint8_t loc;
} tempSensor;


typedef struct{
	uint16_t value;
	uint16_t max;
	uint8_t y;
} progressBar;

#endif /* STRUCTS_H_ */