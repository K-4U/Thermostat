/*
 * progressBar.h
 *
 * Created: 7-2-2013 17:08:29
 *  Author: Koen Beckers
 */ 


#ifndef PROGRESSBAR_H_
#define PROGRESSBAR_H_

extern progressBar createProgressBar(const uint16_t value, const uint16_t max, const uint8_t y);
extern void updateBar(progressBar *pb, const uint8_t value);
extern void drawBar(const progressBar *pb);



#endif /* PROGRESSBAR_H_ */