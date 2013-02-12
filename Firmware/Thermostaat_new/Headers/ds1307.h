/*
 * ds1307.h
 *
 * Created: 8-2-2013 15:16:01
 *  Author: Koen Beckers
 */ 


#ifndef DS1307_H_
#define DS1307_H_

extern void init_ds1307(void);
extern void Read_DS1307(dateTime *toRead);
extern void Write_DS1307(const dateTime *toWrite);


extern void getDayOfWeek(structDate *toRead);
extern uint8_t maxDays(const structDate *toRead);


#endif /* DS1307_H_ */