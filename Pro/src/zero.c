#include "zero.h"
#include "sm15155.h"

void ZERO_Init(void)
{
    GPIO_Init(PB6, GPIO_Mode_OUT, IOCFG_PB6_FUNC_PB6);
    ZR_L;
}

void ZERO_SendByte(uint8_t dat)
{
    for(uint8_t mask = 0x80; mask != 0; mask >>= 1)
    {
        if(mask & dat)
        {
            ZR_H;
            NOP(20);
            // NOP(12);
            ZR_L;
            // NOP(6);
        }            
        else 
        {
            ZR_H;
            NOP(6);
            // NOP(6);
            ZR_L;
            NOP(15);
        }   
    }
}

void ZERO_SendData(uint16_t dat)
{
    for(uint16_t mask = 0x8000; mask != 0; mask >>= 1)
    {
        if(mask & dat)
        {
            ZR_H;
            NOP(20);
            // NOP(12);
            ZR_L;
            // NOP(6);
        }            
        else 
        {
            ZR_H;
            NOP(6);
            // NOP(6);
            ZR_L;
            NOP(15);
        }   
    }
}

void ZERO_Rst(void)
{
    ZR_L;
    delay_us(300);
}
