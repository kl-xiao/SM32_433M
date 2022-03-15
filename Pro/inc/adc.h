#ifndef __ADC_H__ 
#define __ADC_H__ 

#include "sm32f030.h"

void adc_init(uint8_t adc_ch);
uint16_t adc_getvalue(uint8_t ch);

#endif	// __ADC_H__