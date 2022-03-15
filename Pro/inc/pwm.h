#ifndef PWM_H
#define PWM_H

#include "sm32f030.h"

extern uint8_t PWM_Mode;

void pwm_init(uint16_t Ratio1, uint16_t freq);

#endif // PWM_H
