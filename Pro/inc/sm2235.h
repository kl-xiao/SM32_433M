#ifndef SM2235_H_INCLUDED
#define SM2235_H_INCLUDED

#include "sm32f030.h"
#include "sm32f030_gpio.h"
#include "sm32f030_misc.h"



#define  CLK_H   GPIO_SetBits(GPIOB,GPIO_PIN_0)
#define  CLK_L   GPIO_ClearBits(GPIOB,GPIO_PIN_0)

#define  DAT_H   GPIO_SetBits(GPIOB,GPIO_PIN_1)
#define  DAT_L   GPIO_ClearBits(GPIOB,GPIO_PIN_1)

extern uint8_t d_us;

void SM2235_Start(void);
void SM2235_Stop(void);
void SM2235_SendByte(uint8_t dat);
void SM2235_SendByte4(uint8_t dat);
void SM2235_SendGray(uint16_t Gray);

void SM2235_Init(void);
void SM2235_SendData(uint8_t Current, uint16_t R_Gray,uint16_t G_Gray,uint16_t B_Gray,uint16_t W_Gray,uint16_t Y_Gray);
void SM2235_SendData12(uint8_t Cur1, uint8_t Cur2, uint16_t R_Gray,uint16_t G_Gray,uint16_t B_Gray,uint16_t W_Gray,uint16_t Y_Gray);


#endif // SM2235_H_INCLUDED
