#include "ir.h"

uint8_t IR_flag = 0;
uint32_t IRdata = 0;

/***********************************************
 * @file    : IR_Init
 * @brief   : 外部中断初始化 红外接收端口初始化
 * @param   : 
 * @return  : 
 * @date    : 2021/12/06 16:03:57
 * @author  : xkl
************************************************/
void IR_Init(void)
{
    SYSCON_AHBPeriphClockCmd(SYSCON_SYSAHBCLKCTRL_TIM1EN | SYSCON_SYSAHBCLKCTRL_GPIOAEN, ENABLE);

    // 计数器
    TIM_DeInit(TIM1);

    TIM_SetPrescaler(TIM1, 24);		// 系统时钟分频 24 1m
    TIM_Cmd(TIM1, DISABLE);

    // 输入
    GPIO_Init(PA4, GPIO_Mode_IN, IOCFG_PA4_FUNC_PA4);

    GPIO_ITConfig(GPIOA, GPIO_Pin_4, GPIO_Interrupt_Falling);		//配置PA3 双沿触发中断
	
	NVIC_SetPriority(GPIOA_IRQn, 0);	// 设置 GPIOA 中断通道的优先级
	NVIC_EnableIRQ(GPIOA_IRQn);		    // 使能 GPIOA 中断通道
	
	GPIO_ITCmd(GPIOA, GPIO_Pin_4, ENABLE);		// 打开 PA3 中断
}

//  蝶式交换
uint8_t HighLowShift(uint8_t dat)
{
    dat = ((dat>>4) & 0x0f) | ((dat<<4) & 0xf0);
    dat = ((dat>>2) & 0x33) | ((dat<<2) & 0xcc);
    dat = ((dat>>1) & 0x55) | ((dat<<1) & 0xaa);

    return dat;
}

uint16_t Get_LowTime()
{
    TIM_CounterReset(TIM1);
    TIM_Cmd(TIM1, ENABLE);
    while (!(GPIOA->PIN & GPIO_PIN_4))     //输入为低
    {
        if(TIM1->TC >= 16000)    // 大于18ms
            break;
    }
    TIM_Cmd(TIM1, DISABLE);
    
    return TIM1->TC;
}

uint16_t Get_HighTime()
{
    TIM_CounterReset(TIM1);
    TIM_Cmd(TIM1, ENABLE);
    while (GPIOA->PIN & GPIO_PIN_4)     //输入为高
    {
        if(TIM1->TC >= 16000)    // 大于18ms
            break;
    }
    TIM_Cmd(TIM1, DISABLE);
    
    return TIM1->TC;
}

// GPIOA 中断服务函数
/*
 * @ 8.5ms--8190   9ms--8675  8ms--
 */
void GPIOA_IRQHandler(void)
{
    uint16_t time = 0;
    if(GPIO_GetITStatus(GPIOA, GPIO_PIN_4) != RESET)    //中断标志位
    {
        time = Get_LowTime();
        if(time < 8190 || time > 9160)
        {
            GPIO_ClearITPendingBit(GPIOA, GPIO_PIN_4);
            return;
        }

        time = Get_HighTime();
        if(time < 3854 || time > 4818)
        {
            GPIO_ClearITPendingBit(GPIOA, GPIO_PIN_4);
            return;
        }

        for(uint8_t i=0; i<32; i++)
        {
            time = Get_LowTime();
            if ((time<313) || (time>718)) //时间判定范围为 340～780us，
            {
                GPIO_ClearITPendingBit(GPIOA, GPIO_PIN_4);
                return;
            }
            //接收每 bit 高电平时间，判定该 bit 的值
            time = Get_HighTime();
            if ((time>313) && (time<745)) //时间判定范围为 340～780us，
            {
                IRdata <<= 1; //因低位在先，所以数据右移，高位为 0
                IRdata |= 0;
            }
            else if ((time>1395) && (time<1829)) //时间判定范围为 1460～1900us，
            {
                IRdata <<= 1; //因低位在先，所以数据右移，
                IRdata |= 1; //高位置 1
            }
            else //不在上述范围内则说明为误码，直接退出
            {
                GPIO_ClearITPendingBit(GPIOA, GPIO_PIN_4);
                return;
            }
        }
        IR_flag = 1;
        GPIO_ClearITPendingBit(GPIOA, GPIO_PIN_4);
    }
}