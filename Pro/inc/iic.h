#ifndef IIC_H_INCLUDED
#define IIC_H_INCLUDED

#include "sm32f030.h"

// #define SERIES
// #define PARALLEL

#define  CLK_H   (GPIOA->SET = GPIO_PIN_3)
#define  CLK_L   (GPIOA->CLR = GPIO_PIN_3)

#define  DAT_H   (GPIOA->SET = GPIO_PIN_4)
#define  DAT_L   (GPIOA->CLR = GPIO_PIN_4)

extern uint8_t d_us;

void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
void IIC_SendByte(uint8_t dat);

void SM2235_SendData(uint8_t cmd, uint8_t cur, uint16_t R, uint16_t G, uint16_t B, uint16_t W, uint16_t Y);

void MW21518_SetCMD(uint8_t cmd1, uint8_t cmd2, uint8_t cmd3, uint8_t cmd4);
void MW21518_SetCur(uint8_t cur_r, uint8_t cur_g, uint8_t cur_b, uint8_t cur_w, uint8_t cur_y);
void MW21518_SetGray(uint16_t R, uint16_t G, uint16_t B, uint16_t W, uint16_t Y, uint8_t end_flag);

#endif // SM2235_H_INCLUDED
