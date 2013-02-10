/*
 * tempsensor.h
 *
 * Created: 7-2-2013 15:51:55
 *  Author: Koen Beckers
 */ 


#ifndef TEMPSENSOR_H_
#define TEMPSENSOR_H_

extern void init_ds1820(void);
extern void ds1820_read(tempSensor *sensor);



#endif /* TEMPSENSOR_H_ */