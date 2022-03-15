#include "uart.h"
#include "sm32f030_misc.h"
#include "div.h"

char rx_buf[50] = "0";
char rx_flag = 0;

/***********************************************
 * @file    : 串口重定向
 * @brief   : 
 * @param   : 
 * @return  : 
 * @date    : 2021/06/29 09:14:03
 * @author  : xkl
************************************************/
int _write (int fd, char *pBuffer, int size)
{
	for (int i = 0; i < size; i++)
	{
		while(UART0->SR & UART_SR_TXNE);//等待上一次串口数据发送完成  
        UART0->DR = (uint8_t) pBuffer[i];       //写DR,串口1将发送数据
	}
	return size;
}

/**
 * @函数功能:  uart初始化
 * @函数形参:  Baud -- 波特率
 * @返回值:
 * @备注:      PA9--TX PA10--RX
 */
void uart_init(unsigned int Baud)
{
    SYSCON->SYSAHBCLKCTRL |= SYSCON_SYSAHBCLKCTRL_UART0EN; //打开UART0时钟
    SYSCON->UART0CLKDIV = 1;//UART0时钟分频为1，UARTn_PCLK除1

    GPIO_Init(PA9, GPIO_Mode_OUT, IOCFG_PA9_FUNC_TXD0);
	GPIO_Init(PA10, GPIO_Mode_IN, IOCFG_PA10_FUNC_RXD0);

    UART_DeInit(UART0);
	UART_Init(UART0, Baud, UART_Parity_No, UART_Mode_Rx | UART_Mode_Tx);
  	
    UART_ITConfig(UART0, UART_IT_RXNE, ENABLE);		//使能接收中断
	
	NVIC_SetPriority(UART0_IRQn, 1);		//设置串口0中断通道的优先级
	NVIC_EnableIRQ(UART0_IRQn);			    //使能串口0中断通道
}

/**
 * @函数功能:  uart发送一个字节
 * @函数形参:  ch -- 字节数据
 * @返回值:
 * @备注:
 */
void uart0_send_char(char ch)
{
    UART0->DR = ch;
    while(UART0->SR & UART_SR_TXNE);   //等待数据发送完成
}

/**
 * @函数功能:  uart发送字符串
 * @函数形参:  buf -- 字符串地址
 * @返回值:
 * @备注:
 */
void uart0_send_Str(char *buf)
{
    uint8_t i = 0;
    while( buf[i] != '\0' )
    {
        while(UART0->SR & UART_SR_TXF);//发送 FIOF 非满
        UART0->DR = buf[i];
        i++;
         while(UART0->SR & UART_SR_TXNE);   //等待数据发送完成
    }

}

/**
 * @函数功能:  uart阻塞接收一个字节数据
 * @函数形参:
 * @返回值:    rec -- 接收到的数据
 * @备注:
 */
uint8_t uart0_rec_char_while(void)
{
    uint8_t rec;
    while(1)
    {
        if( UART0->SR & 0X02)//接收到数据
        {
            rec = UART0->DR;
            return rec;
        }
    }
    return '\0';
}
/**
 * @函数功能:  uart非阻塞接收一个字节数据
 * @函数形参:
 * @返回值:    rec -- 接收到的数据
 * @备注:
 */
uint8_t uart0_rec_char(void)
{
    uint8_t rec;
    if( UART0->SR & 0X02)//接收到数据
    {
        rec = UART0->DR;
        return rec;
    }
    return '\0';
}
/**
 * @函数功能:  uart阻塞接收字符串
 * @函数形参:
 * @返回值:
 * @备注:      rx_buf -- 全局变量
 */
void uart0_rec_Str_while(void)
{
    uint8_t rec = 0,flag = 0;
    uint8_t i = 0;
    while(!flag)
    {
         if( UART0->SR & 0X02 )//接收到数据
        {
            rec = UART0->DR;
            rx_buf[i] = rec;
            i++;
            if( rx_buf[i-1] == '#')
            {
               rx_buf[i-1] = '\0';
               i = 0;
               //uart0_send_Str(rx_buf);
                flag = 1;
            }

        }

    }
}

/**
 * @函数功能:  uart非阻塞接收字符串
 * @函数形参:
 * @返回值:
 * @备注:      rx_buf -- 全局变量
 */
void uart0_rec_Str(void)
{
    uint8_t rec = 0;
    static uint8_t i = 0;
    if( UART0->SR & 0X02 )//接收到数据
    {
        rec = UART0->DR;
        rx_buf[i] = rec;
        i++;
        if( rx_buf[i-1] == '#')
        {
           rx_buf[i-1] = '\0';
           i = 0;
           rx_flag = 1;
        }

    }
}
int uart0_rec_int(void)
{
    uint8_t rec = 0;
    int rec_data = 0,rec_reg = 0;
    uint8_t i = 0;
    rx_flag = 0;
    while(!rx_flag)
    {
         if( UART0->SR & 0X02 )//接收到数据
        {
            rec = UART0->DR;
            rx_buf[i] = rec;
            i++;
            if( i > 3)
            {
                for(i = 0;i<4;i++)
                {
                    rec_reg = rx_buf[i];
                    rec_data +=rec_reg << (8*i);
                }
                rx_flag = 1;
            }
        }

    }
    return rec_data;

}

//串口接收中断服务函数写在start.c文件里面
void UART0_IRQHandler()
{
    static uint8_t num = 0;
    if(UART_GetITStatus(UART0, UART_IT_RXNE))
    {
        UART_ClearITPendingBit(UART0, UART_IT_RXNE);

        rx_buf[num++] = UART0->DR;

        if(num == 2)
        {
            if(rx_buf[1] != 0xaa || rx_buf[0] != 0x64)
            {
                num = 0;
            }
        }

        if((rx_buf[num-1] == 0x0d) && (rx_buf[num-2] == 0x0a))
        {
            GPIOA->NOT = GPIO_Pin_3;
            rx_buf[num] = '\0';
            num = 0;
            rx_flag = 1;
        }        
    }
}
