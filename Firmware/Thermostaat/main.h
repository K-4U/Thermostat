/*
 * main.h
 *
 * Created: 31-1-2013 21:24:05
 *  Author: Koen Beckers
 */ 


#ifndef MAIN_H_
#define MAIN_H_


#define LED			_BV(PA5)
#define LED_AAN()	PORTA |= LED
#define LED_UIT()	PORTA &= ~LED




#endif /* MAIN_H_ */