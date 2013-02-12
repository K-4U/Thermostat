/*
 * tempsensor.h
 *
 * Created: 11-2-2013 13:43:51
 *  Author: Koen Beckers
 */ 


#ifndef TEMPSENSOR_H_
#define TEMPSENSOR_H_

void init_ds1820(void);
void ds1820_read(tempSensor *sensor);



#endif /* TEMPSENSOR_H_ */