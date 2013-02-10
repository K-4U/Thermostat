/*
 * glcdFunctions.h
 *
 * Created: 7-2-2013 16:13:55
 *  Author: Koen Beckers
 */ 


#ifndef GLCDFUNCTIONS_H_
#define GLCDFUNCTIONS_H_

extern void init_display(void);
extern void drawMainScreen();
extern void drawTopHeader(void);
extern void drawTime(void);
extern void drawDate(void);


extern void drawMainScreenButtons(const uint8_t active);
extern void drawValues(void);
extern void drawAwayScreen(void);
extern void drawPresetActive(void);
extern void closePresetDrawer(void);
extern void drawPresetDrawer(void);

extern uint8_t isIn(const lcdPos *pos, const square *obj);
extern uint8_t isDifferent(const lcdPos *p1, const lcdPos *p2);

extern void loadImage(const uint8_t x, const uint8_t y, const uint8_t *bitmap);
extern void loadImageInverted(const uint8_t x, const uint8_t y, const uint8_t *bitmap);

extern void turnLcdOn(void);
extern void turnLcdOff(void);

extern lcdPos readPos(void);
extern void readAndHandleScreen(void);

extern void drawBatteryBar(void);
extern void drawTtlBar(void);

#endif /* GLCDFUNCTIONS_H_ */