#include "iic.h"

uint8_t d_us = 1;

void IIC_Init(void)
{
    SYSCON->SYSAHBCLKCTRL |= SYSCON_SYSAHBCLKCTRL_GPIOAEN;//打开PA组时钟
    GPIO_Init(PA3,GPIO_Mode_OUT,IOCFG_PA3_FUNC_PA3 | IOCFG_PUE);    //
    GPIO_Init(PA4,GPIO_Mode_OUT,IOCFG_PA4_FUNC_PA4 | IOCFG_PUE);    //
}

void IIC_Start(void)
{
    CLK_H;
    DAT_H;
    delay_ns(4);
    DAT_L;
    delay_ns(4);
    CLK_L;
}

void IIC_Stop(void)
{
    CLK_L;
    DAT_L;
    delay_ns(4);
    CLK_H;
    delay_ns(4);
    DAT_H;
}

void IIC_Ack(void)
{
    DAT_L;
    delay_ns(d_us);    //
    CLK_H;
    delay_ns(d_us);
    CLK_L;
}

void IIC_SendByte(uint8_t dat)
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
    IIC_Ack();
}

void IIC_SendByte4(uint8_t dat)
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
    //IIC_Ack();
}

void IIC_SendBit(uint8_t dat)
{
    if(dat & 0x01)
        DAT_H;
    else
        DAT_L;
    delay_ns(d_us);    //
    CLK_H;
    delay_ns(d_us);
    CLK_L;   
}

void IIC_SendGray(uint16_t dat)
{
    IIC_SendByte(dat>>8);
    IIC_SendByte(dat);
}
/***********************************************
 * @file    : SM2235_SendData
 * @brief   : 发送SM2235控制数据
 * @param   : 
 * @return  : 
 * @date    : 2021/08/17 09:59:20
 * @author  : xkl
************************************************/
void SM2235_SendData(uint8_t cmd, uint8_t cur, uint16_t R, uint16_t G, uint16_t B, uint16_t W, uint16_t Y)
{
    IIC_Start();
    IIC_SendByte(cmd);
    IIC_SendByte(cur);
    IIC_SendGray(R);
    IIC_SendGray(G);
    IIC_SendGray(B);
    IIC_SendGray(W);
    IIC_SendGray(Y); 
    IIC_Stop();
}
/***********************************************
 * @file    : MW21518_SendData
 * @brief   : 发送MW21518控制数据
 * @param   : cmd1---识别、待机、地址   cmd2---模式、频率、最大电流
 * @param   : cmd3---通道使能          cmd4---恒功率
 * @return  : 
 * @date    : 2021/08/17 09:31:29
 * @author  : xkl
************************************************/
void MW21518_SetCMD(uint8_t cmd1, uint8_t cmd2, uint8_t cmd3, uint8_t cmd4)
{
    IIC_Start();
    IIC_SendByte(cmd1);     //
    IIC_SendByte(cmd2);
    IIC_SendByte(cmd3);
    IIC_SendByte(cmd4);
}

void MW21518_SetCur(uint8_t cur_r, uint8_t cur_g, uint8_t cur_b, uint8_t cur_w, uint8_t cur_y)
{
    IIC_SendByte(cur_r);
    IIC_SendByte(cur_g);
    IIC_SendByte(cur_b);
    IIC_SendByte(cur_w);
    IIC_SendByte(cur_y);
}

void MW21518_SetGray(uint16_t R, uint16_t G, uint16_t B, uint16_t W, uint16_t Y, uint8_t end_flag)
{
    IIC_SendGray(R);
    IIC_SendGray(G);
    IIC_SendGray(B);
    IIC_SendGray(W);
    IIC_SendGray(Y);

#ifdef SERIES
    IIC_SendByte(0xC3);
#else
    IIC_SendByte(end_flag);
#endif     
    IIC_Stop();
}

