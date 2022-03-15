#ifndef UART_H
#define UART_H

#include "sm32f030.h"
#include "div.h"
#include "stdio.h"

void uart_init(unsigned int Baud);
void uart0_send_Str(char *buf);
void uart0_send_char(char ch);
uint8_t uart0_rec_char(void);
uint8_t uart0_rec_char_while(void);
void uart0_rec_Str(void);
void uart0_rec_Str_while(void);
int uart0_rec_int(void);
extern char rx_buf[50];
extern char rx_flag;

#endif // UART_H
