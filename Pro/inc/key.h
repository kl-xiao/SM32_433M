#ifndef KEY_H
#define KEY_H

#include "sm32f030.h"
#include "sm32f030_misc.h"
#include "sm32f030_gpio.h"

#define ON 0
#define OFF 1
#define key1 !!( GPIOA->PIN & GPIO_PIN_0 )
#define key2 !!( GPIOA->PIN & GPIO_PIN_1 )
#define key3 !!( GPIOA->PIN & GPIO_PIN_11)
#define key4 !!( GPIOA->PIN & GPIO_PIN_12)

void key_init(void);
uint8_t key_scan(void);

#endif // KEY_H
