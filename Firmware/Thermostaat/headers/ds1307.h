/*
 * ds1307.h
 *
 * Created: 24-10-2011 15:02:49
 *  Author: Koen Beckers
 */ 


#ifndef DS1307_H_
#define DS1307_H_

extern dateTime currentDateTime;
extern void Read_DS1307(void);
extern void Write_DS1307(dateTime *toWrite);


#endif /* DS1307_H_ */