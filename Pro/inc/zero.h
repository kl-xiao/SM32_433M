#ifndef __ZERO_H__
#define __ZERO_H__

#include "sm32f030.h"

#define ZR_H   (GPIOB->SET = GPIO_PIN_6)
#define ZR_L   (GPIOB->CLR = GPIO_PIN_6)

void ZERO_Init(void);
void ZERO_SendByte(uint8_t dat);
void ZERO_SendData(uint16_t dat);
void ZERO_Rst(void);

#endif