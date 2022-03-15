#include "SM1642.h"
#include "div.h"

//数码管字模
const uint8_t BUF_seg[22] = {0b00111111,0b00000110,0b01011011,0b01001111,\
                             0b01100110,0b01101101,0b01111101,0b00000111,\
                             0b01111111,0b01101111,0b01110111,0b01111100,\
                             0b00111001,0b01011110,0b01111001,0b01110001,\
                             0b00000000,0b01010100,0b01011000,0b00011100,\
                             0b00111000,0b00110001};//灭，m，c，u，L，r*/

/***************数码管驱动（1642芯片）初始化函数***************

函数名称：SM1642_Init
函数形参：无
函数功能：初始化1642芯片需要的CLK,DATA引脚
函数返回：无
编写者：深圳市明微电子股份有限公司————zglin19015

***************数码管驱动（1642芯片）初始化函数***************/
void SM1642_Init(void)
{
    GPIO_Init(PA5,GPIO_Mode_OUT, IOCFG_DEFAULT);   //配置PA5输出，即1642芯片CLK端口
    GPIO_Init(PA7,GPIO_Mode_OUT, IOCFG_DEFAULT);   //配置PA7输出，即1642芯片DATA端口
    CLK1642_L;
    DATA1642_H;
//    delay_us(1);
}
/***********************************************
 * @file    : SM1642_PORTout
 * @brief   : SM1642端口驱动
 * @param   : port--位选   DAT--显示数据
 * @return  : 无
 * @date    : 2021/12/01 15:54:32
 * @author  : xkl
************************************************/
void SM1642_PORTout(uint8_t port,uint8_t DAT)
{
    uint32_t data = ((~(1<<port)&0x0f) | (BUF_seg[DAT]<<10)) & 0x3FC0F;

    DATA1642_H;
    for(uint32_t mask = 0x0001; mask != 0x40000; mask <<= 1)
    {
        CLK1642_L;
        if(mask & data)
        {
            DATA1642_H;
        }
        else
        {
            DATA1642_L;
        }
        CLK1642_H;
    }
    DATA1642_L;
    DATA1642_H;
    DATA1642_L;
    CLK1642_L;
    DATA1642_H;
}
/**************数码管驱动（1642芯片）片选输出函数**************

函数名称：SM1642_PORTout
函数形参：port —— 片选端口，DAT —— 显示数据
函数功能：初始化1642芯片需要的CLK,DATA引脚
函数返回：无
编写者：深圳市明微电子股份有限公司————zglin19015

**************数码管驱动（1642芯片）片选输出函数**************/
// void SM1642_PORTout(uint8_t port,uint8_t DAT)
// {
//     uint8_t i = 0;
//     uint8_t data = BUF_seg[DAT];
//     DATA1642_H;
//     CLK1642_L;
//     //delay_us(1);
//     //delay(1);
//     for(i = 0;i < 18;i++)
//     {
//        if(i < 4)
//        {
//             if(i == port)DATA1642_L;
//             else DATA1642_H;
//        }
//        else if(i > 9)
//        {
//             if((data>>(i-10))&0x01)DATA1642_H;
//             else DATA1642_L;
//        }
//         CLK1642_H;
//         if(i<17)
//         {
//             CLK1642_L;
//         }
//         else
//         {
//             DATA1642_L;
//             //delay_us(1);
//             //delay(1);
//             DATA1642_H;
//             //delay_us(1);
//             //delay(1);
//             DATA1642_L;
//             //delay_us(1);
//             //delay(1);
//             CLK1642_L;
//             //delay_us(1);
//             //delay(1);
//             DATA1642_H;
//             delay_us(1);
//             //delay(1);
//         }
//     }
// }
/**************数码管驱动（1642芯片）动态输出函数**************

函数名称：SM1642_out
函数形参：data1，data2，data3，data4 —— 各个数码管显示数据
函数功能：初始化1642芯片需要的CLK,DATA引脚
函数返回：无
编写者：深圳市明微电子股份有限公司————zglin19015

**************数码管驱动（1642芯片）动态输出函数**************/
void SM1642_Out(uint8_t data1,uint8_t data2,uint8_t data3,uint8_t data4)
{
    SM1642_PORTout(0,data1);
    SM1642_PORTout(1,data2);
    SM1642_PORTout(2,data3);
    SM1642_PORTout(3,data4);

    SM1642_PORTout(0,16);
    SM1642_PORTout(1,16);
    SM1642_PORTout(2,16);
    SM1642_PORTout(3,16);//消影
}

/************************数码管简易时钟************************

函数名称：clock1642
函数形参：无
函数功能：使用1642驱动数码管显示一个简易的时钟
函数返回：无
编写者：深圳市明微电子股份有限公司————zglin19015

************************数码管简易时钟************************/
uint8_t min_H = 0,min_L = 0,sec_H = 0,sec_L = 0;
void clock1642(void)
{
    static uint16_t a = 0;
    //SM1642_out(min_H,min_L,sec_H,sec_L);
    delay1642_ms(1);
    a++;
    if(a > 504)//实测数据，不是很准
    {
        a = 0;
        sec_L++;
        if(sec_L > 9)
        {
            sec_L = 0;
            sec_H++;
            if(sec_H > 5)
            {
                sec_H = 0;
                min_L++;
                if(min_L > 9)
                {
                    min_L = 0;
                    min_H++;
                    if(min_H > 5)
                    {
                        min_H = 0;
                    }
                }
            }
        }

    }

}
void delay1642_ms(uint32_t ms)
{
    while(ms--)
    {
        SM1642_Out(min_H,min_L,sec_H,sec_L);
    }

}

//显示数字
void SM1642_Shownum(int num)
{
    uint32_t now_num = 0;
    int unitPlace = 0;
    int tenPlace = 0;
    int hundredPlace = 0;
    int thousandPlace = 0;

    if( now_num != num )
    {
        thousandPlace = my_div_f(num,1000);
        hundredPlace = my_div_f((num-my_div_f(num,1000)*1000),100);
        tenPlace = my_div_f((num-my_div_f(num,100)*100),10);
        unitPlace = my_div_f((num-my_div_f(num,10)*10),1);
    }
    now_num = num;

    SM1642_PORTout(0,thousandPlace);
    SM1642_PORTout(1,hundredPlace);
    SM1642_PORTout(2,tenPlace);
    SM1642_PORTout(3,unitPlace);
    SM1642_PORTout(0,16);
    SM1642_PORTout(1,16);
    SM1642_PORTout(2,16);
    SM1642_PORTout(3,16);   //消隐
}
