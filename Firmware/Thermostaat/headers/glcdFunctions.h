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

extern void drawMenuHeader(void);
extern void drawTime(void);
extern void drawDate(void);
extern void drawMainScreenButtons(uint8_t active);
extern void drawMenu(char *title, const sMenuItem *pcmuItems, uint8_t iMaxItems);
extern void drawValues();

extern uint8_t isIn(lcdPos *pos,square *obj);
extern uint8_t isDifferent(lcdPos *p1, lcdPos *p2);
//				  76543210
#define DIFF_X	0b00000001
#define DIFF_Y	0b00000010
#define DIFF_P	0b00000100

extern sMenuItem makeMenuItem(const char *paccText, int iRet);

extern void drawMainScreen();


extern lcdPos readPos(void);

#endif /* GLCDFUNCTIONS_H_ */