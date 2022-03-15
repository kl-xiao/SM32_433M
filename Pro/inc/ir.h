#ifndef __IR_H__ 
#define __IR_H__ 

#include "sm32f030.h"
#include "main.h"

typedef enum
{
    R,
    G,
    B,
    W,
    Y
}ColorType;

typedef enum
{
    ADD,
    DEC,
    OFF,
    ON,
    RED,
    GREEN,
    BLUE,
    WHITE,
    KEY31,
    KEY32,
    KEY33,
    FLASH,
    KEY41,
    KEY42,
    KEY43,
    STROBE,
    KEY51,
    KEY52,
    KEY53,
    FADE,
    KEY61,
    KEY62,
    KEY63,
    SMOOTH,
    SLEEP,
    IDEL
}IRType;


extern uint8_t IR_flag;
extern uint32_t IRdata;

void IR_Init(void);
uint8_t HighLowShift(uint8_t dat);

#endif	// __EXTI_H__