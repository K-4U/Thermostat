/*
 * Author: Koen Beckers
 * Project: RoomControl
 * Module: Remote
 * File: glcdFunctions.h
 * Description:
 * Header file for the .c
 */


#ifndef GLCDFUNCTIONS_H_
#define GLCDFUNCTIONS_H_

#ifdef GLCDFUNCTIONS_C
#define PROTO_F
#else
#define PROTO_F extern
#endif

PROTO_F square buttonUp;
PROTO_F square buttonDown;
PROTO_F square buttonPreset;
PROTO_F square preset_sun;
PROTO_F square preset_moon;

extern void drawMainScreen();
extern void drawMenuHeader(void);
extern void drawTime(void);
extern void drawDate(void);
extern void drawMainScreenButtons(uint8_t active);
extern void drawValues(void);
extern void drawPresetActive(void);
extern void closePresetDrawer(void);
extern void drawPresetDrawer(void);

extern uint8_t isIn(lcdPos *pos,square *obj);
extern uint8_t isDifferent(lcdPos *p1, lcdPos *p2);
//				  76543210
#define DIFF_X	0b00000001
#define DIFF_Y	0b00000010
#define DIFF_P	0b00000100


extern void turnLcdOn(void);
extern void turnLcdOff(void);

extern lcdPos readPos(void);

#endif /* GLCDFUNCTIONS_H_ */