
#ifndef __SM1642_H
#define __SM1642_H

#include "sm32f030.h"
#include "sm32f030_GPIO.h"
#include "sm32f030_misc.h"

//关于1642芯片的一些定义
#define CLK1642_H /*GPIO_SetBits(GPIOA,GPIO_Pin_5)*/GPIOA->SET |= GPIO_Pin_5
#define CLK1642_L /*GPIO_ClearBits(GPIOA,GPIO_Pin_5)*/GPIOA->CLR |= GPIO_Pin_5
#define DATA1642_H /*GPIO_SetBits(GPIOA,GPIO_Pin_7)*/GPIOA->SET |= GPIO_Pin_7
#define DATA1642_L /*GPIO_ClearBits(GPIOA,GPIO_Pin_7)*/GPIOA->CLR |= GPIO_Pin_7

extern const uint8_t BUF_seg[22];

extern uint8_t min_H,min_L,sec_H,sec_L;

void SM1642_Init(void);
void SM1642_PORTout(uint8_t port,uint8_t DAT);
void SM1642_Out(uint8_t data1,uint8_t data2,uint8_t data3,uint8_t data4);

void clock1642(void);
void delay1642_ms(uint32_t ms);
void SM1642_Shownum(int n);

#endif // SM1642_H
