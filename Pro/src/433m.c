#include "433m.h"

#define RF_REC	(GPIOB->PIN & GPIO_Pin_2)

uint8_t decode_ok = 0;			//解码成功
uint16_t hcnt = 0, lcnt = 0;	//高,低电平宽度
uint8_t rec_num = 0;			//接收到第几位编码了
 	
uint32_t rec_tmp = 0;		// 用于接收过程存放遥控编码
uint32_t rec_data1 = 0; 	// 用于接收完成后存放遥控编码，第一次
uint32_t rec_data2 = 0;		// 用于接收完成后存放遥控编码，第二次

uint8_t rf_ok1, rf_ok2, rf_ok; 	//解码过程中的临时接收成功标志,接收到一个完整的遥控命令后置1,通知解码程序可以解码了
uint8_t pre_state;			   	//保存上一次查询到的电平状态
uint8_t start_ok = 0;		   	//接收到同步的马时置1
uint16_t over_time;			   	//超时时间
extern uint8_t rf_data[4];

/*
 * @ 50us进一次中断
 */
void RF433M_Init(void)
{
    SYSCON_AHBPeriphClockCmd(SYSCON_SYSAHBCLKCTRL_TIM1EN | SYSCON_SYSAHBCLKCTRL_GPIOBEN, ENABLE);

    // 计数器
    TIM_DeInit(TIM1);

    TIM_SetPrescaler(TIM1, 23);		// 系统时钟分频 23+1 1m
    TIM_Match0Config(TIM1, 80, TIM_Match_Interrupt | TIM_Match_CounterReset);

    // 配置 TIM0 中断通道
	NVIC_SetPriority(TIM1_IRQn, 0);     // 优先级设置
	NVIC_EnableIRQ(TIM1_IRQn);          // 使能

	TIM_Cmd(TIM1, ENABLE);		        //使能 TIM0

    // 输入
    GPIO_Init(PB2, GPIO_Mode_IN, IOCFG_PB2_FUNC_PB2);
}

void TIM1_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM1, TIM_IT_MAT0))
    {
        TIM_ClearITPendingBit(TIM1, TIM_IT_MAT0);

		if (RF_REC == 0)
		{
			lcnt++; // 检测到低电平 低电平时间加1,记录本 // 次电平状态old_rc5			
			pre_state = 0;
		}
		else // 检测到高电平
		{
			hcnt++;
			if (!pre_state) // 检测到从低到高的跳变,已检测					// 到一个完整(高-低)电平周期
			{
				if (((hcnt >= 2) && (hcnt <= 6)) && ((lcnt >= 50) && (lcnt <= 60))) //判同步码    2/5 100/130
				{
					start_ok = 1;
					rec_num = 0;
					rec_tmp = 0;
				}
				else if ((start_ok) && ((lcnt >= 9) && (lcnt <= 14))) //8/13
				{
					rec_num++; //已经接收到同步码,判0

					if (rec_num >= 24)
					{
						if (rf_ok1 == 0) //rf_ok1临时接收成功
						{				 
							rec_data1 = rec_tmp;	//将接收到的编码复制到解码寄存器中

							rf_ok1 = 1;				// 通知解码子程序可以解码了
							start_ok = 0;
							over_time = 1000;
						}
						else
						{ 
							rec_data2 = rec_tmp;	// 将接收到的编码复制到解码寄存器中										
							rf_ok2 = 1;				// 通知解码子程序可以解码了
							start_ok = 0;
						}
					}
				}
				else if ((start_ok) && ((lcnt >= 2) && (lcnt <= 6))) // 2/7
				{
					rec_num++;

					if(rec_num < 25)
					{
						rec_tmp = rec_tmp | (0x800000 >> (rec_num - 1));	//计数值不是从0开始，所以需要减1
					}
					
					if(rec_num == 24)
					{
						if (!rf_ok1)
						{
							rec_data1 = rec_tmp;	// 将接收到的编码复制到解码寄存器中
							rf_ok1 = 1; 			// 通知解码子程序可以解码了
							start_ok = 0;
							over_time = 1000;		// 超时时间设定
						}
						else
						{
							rec_data2 = rec_tmp; 	// 将再次接收到的编码复制到解码寄存器中，
							rf_ok2 = 1;	 			// 通知解码子程序可以解码了
							start_ok = 0;
						}
					}
				}
				else
				{	
					rec_num = 0;
					start_ok = 0;
					rec_tmp = 0;

					hcnt = 1;
					lcnt = 0;
				} //接收到不符合的高-低电平序列
				lcnt = 0;
				hcnt = 1;
			}
			pre_state = 1; // 记录本次电平状态
		}

		if (rf_ok1) //规定时间内接受到2帧相同的编码数据才有效
		{
			over_time--;
			if (!over_time)
				rf_ok1 = 0;
			if (rf_ok2)
			{
				if(rec_data2 == rec_data1)
				{
					rf_ok = 1;
					rf_ok1 = 0;
					rf_ok2 = 0;
				}
				else
				{
					rf_ok = 0;
					rf_ok1 = 0;
					rf_ok2 = 0;
				}
			}
		}

		if ((rf_ok) && (lcnt >= 1250) && (lcnt <= 2000)) //判断是否接收成功
		{
			NVIC_DisableIRQ(TIM1_IRQn);
			rf_ok = 0;
			rf_data[0] = rec_data1 >> 16;
			rf_data[1] = rec_data1 >> 8;
			rf_data[2] = rec_data1;

			decode_ok = 1;
			
			NVIC_EnableIRQ(TIM1_IRQn);
		}
    }
}