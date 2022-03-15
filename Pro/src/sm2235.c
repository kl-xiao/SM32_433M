#include "SM2235.h"

uint8_t d_us;

void SM2235_Init(void)
{
    SYSCON->SYSAHBCLKCTRL |= SYSCON_SYSAHBCLKCTRL_GPIOBEN;//打开PB组时钟
    GPIO_Init(PB0,GPIO_Mode_OUT,IOCFG_PB0_FUNC_PB0 | IOCFG_PUE);    //
    GPIO_Init(PB1,GPIO_Mode_OUT,IOCFG_PB1_FUNC_PB1 | IOCFG_PUE);    //
}

void SM2235_Start(void)
{
    CLK_H;
    DAT_H;
    delay_ns(4);
    DAT_L;
    delay_ns(4);
    CLK_L;
}

void SM2235_Stop(void)
{
    CLK_L;
    DAT_L;
    delay_ns(4);
    CLK_H;
    delay_ns(4);
    DAT_H;
}

void SM2235_Ack(void)
{
    DAT_L;
    delay_ns(d_us);    //
    CLK_H;
    delay_ns(d_us);
    CLK_L;
}

void SM2235_SendByte(uint8_t dat)
{
    //CLK_L;
    for(uint8_t mask = 0x80; mask != 0; mask >>= 1)
    {
        if(mask & dat)
            DAT_H;
        else
            DAT_L;

        delay_ns(d_us);    //delay_ns(2);
        CLK_H;
        delay_ns(d_us);
        CLK_L;
    }
    SM2235_Ack();
}

void SM2235_SendByte4(uint8_t dat)
{
    for(uint8_t mask = 0x08; mask != 0; mask >>= 1)
    {
        if(mask & dat)
            DAT_H;
        else
            DAT_L;

        delay_ns(d_us);    //
        CLK_H;
        delay_ns(d_us);
        CLK_L;
    }
    SM2235_Ack();
}

void SM2235_SendGray(uint16_t Gray)
{
    SM2235_SendByte(Gray >> 8);
    SM2235_SendByte(Gray);
}

void SM2235_SendData(uint8_t Current, uint16_t R_Gray,uint16_t G_Gray,uint16_t B_Gray,uint16_t W_Gray,uint16_t Y_Gray)
{
    SM2235_Start();
    SM2235_SendByte(0xD8);
    SM2235_SendByte(Current);
    SM2235_SendGray(R_Gray);
    SM2235_SendGray(G_Gray);
    SM2235_SendGray(B_Gray);
    SM2235_SendGray(W_Gray);
    SM2235_SendGray(Y_Gray);
    SM2235_Stop();
}

void SM2235_SendData12(uint8_t Cur1, uint8_t Cur2, uint16_t R_Gray,uint16_t G_Gray,uint16_t B_Gray,uint16_t W_Gray,uint16_t Y_Gray)
{
    SM2235_Start();
    SM2235_SendByte(0xD8);
    SM2235_SendByte(Cur1);
    SM2235_SendByte(Cur2);
    SM2235_SendGray(R_Gray);
    SM2235_SendGray(G_Gray);
    SM2235_SendGray(B_Gray);
    SM2235_SendGray(W_Gray);
    SM2235_SendGray(Y_Gray);
    SM2235_Stop();
}
