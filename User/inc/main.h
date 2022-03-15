#ifndef __MAIN_H__ 
#define __MAIN_H__ 

#include "sm32f030.h"
#include "uart.h"
// #include "iic.h"
#include "433m.h"
#include "zero.h"
#include "sm1642.h"

#define PRINT   1

#define ALL_ON  0x06
#define ALL_OFF 0x0c

#define LIGHT   0x16
#define DARK    0x03
#define WARM    0x1a
#define COLD    0x12

#define SW1_ON  0x26
#define SW1_OFF 0x2c
#define SW2_ON  0x46
#define SW2_OFF 0x4c
#define SW3_ON  0x66
#define SW3_OFF 0x6c
#define SW4_ON  0x86
#define SW4_OFF 0x8c

#endif	// __MAIN_H__