/*
 * adc.h
 *
 * Created: 7-2-2013 16:19:56
 *  Author: Koen Beckers
 */ 


#ifndef ADC_H_
#define ADC_H_

extern void init_adc(void);
extern uint8_t read_adc(const uint8_t adc_input);
extern uint16_t read_adc_16(const uint8_t adc_input);



#endif /* ADC_H_ */