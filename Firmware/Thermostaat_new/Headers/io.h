/*
 * macro.h
 *
 * Created: 7-2-2013 15:37:15
 *  Author: Koen Beckers
 */ 


#ifndef MACRO_H_
#define MACRO_H_

#define LED_AAN()	PORT_LED |= LED
#define LED_UIT()	PORT_LED &= ~LED

#define LCD_AAN()	PORT_LCD |= LCD
#define LCD_UIT()	PORT_LCD &= ~LCD

#define CV_ON()		{PORT_CVP |= CVP_ON; _delay_ms(5); PORT_CVP &= ~CVP_ON;SETDRAWFLAG(DRAW_CV_ON);}
#define CV_OFF()	{PORT_CVP |= CVP_OFF; _delay_ms(5); PORT_CVP &= ~CVP_OFF;SETDRAWFLAG(DRAW_CV_OFF);}

extern void init_io(void);
extern void checkButtons(void);


#endif /* MACRO_H_ */