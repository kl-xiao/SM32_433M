#include "timer.h"
#include "main.h"

uint16_t Timer_Cnt = 0;

/*
 * @ 50us中断一次
 */
void timer_init(void)
{
    SYSCON_AHBPeriphClockCmd(SYSCON_SYSAHBCLKCTRL_TIM0EN, ENABLE);

    TIM_DeInit(TIM0);

    TIM_SetPrescaler(TIM0, 11);		// 系统时钟分频 11+1 1m
	TIM_Match0Config(TIM0, 60, TIM_Match_Interrupt | TIM_Match_CounterReset);     // 计数完中断清零

    // 配置 TIM0 中断通道
	NVIC_SetPriority(TIM0_IRQn, 0);     // 优先级设置
	NVIC_EnableIRQ(TIM0_IRQn);          // 使能

	TIM_Cmd(TIM0, ENABLE);		        //使能 TIM0
}

void TIM0_IRQHandler(void)
{
    // if(TIM0->IR & TIM_IR_MR0INT)
    if(TIM_GetITStatus(TIM0, TIM_IT_MAT0))
    {
        TIM_ClearITPendingBit(TIM0, TIM_IT_MAT0);
        // TIM0->IR = TIM_IT_MAT0;
        Timer_Cnt++;
    }
}