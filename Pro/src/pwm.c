#include "pwm.h"
#include "div.h"

uint8_t PWM_Mode = 0;
uint32_t Period;

/**
 * @函数功能: PWM初始化
 * @函数形参: Ratio1 占空比 freq --频率 khz
 * @返回值:
 * @备注:
 */
void pwm_init(uint16_t Ratio1, uint16_t freq)
{
    uint32_t tmpreg;
    uint16_t Value1;
    uint16_t Value2;
    // uint16_t Value3;
    //周期 24M/8/3000 = 1000Hz      1500/3000=50%
    if(PWM_Mode)    //低频
        Period = my_div(3000000,freq);  //1 频率1hz  10 10hz
    else            //高频
        Period = my_div(24000,freq);    //1 频率1Khz  10 10Khz  

    Value1 = my_div(Period*Ratio1,100);
    Value2 = my_div(Period*Ratio1,100);
    // Value3 = my_div(Period*Ratio3,100);
    // Value1 = Ratio1;
    // Value2 = Ratio1;
    // Value3 = Ratio1;

    SYSCON->SYSAHBCLKCTRL |= SYSCON_SYSAHBCLKCTRL_PWMEN;//打开PWM时钟
    SYSCON->SYSAHBCLKCTRL |= SYSCON_SYSAHBCLKCTRL_GPIOAEN;//打开PA组时钟
    SYSCON->SYSAHBCLKCTRL |= SYSCON_SYSAHBCLKCTRL_GPIOBEN;//打开PB组时钟

    /*PA7复用成PWM1功能*/
    //IOCFG->PA7 = IOCFG_PA7_FUNC_PWM_OUT1;
    //GPIOA->DIR |= GPIO_DIR_7;//PA7配置为输出
    /*PB0复用成PWM3功能*/
    IOCFG->PB0 = IOCFG_PB0_FUNC_PWM_OUT3;
    GPIOB->DIR |= GPIO_DIR_0;//PB0配置为输出
    /*PB1复用成PWM5功能*/
    IOCFG->PB1 = IOCFG_PB1_FUNC_PWM_OUT5;
    GPIOB->DIR |= GPIO_DIR_1;//PB1配置为输出
    /*PB15复用成PWM5功能*/
    //IOCFG->PB15 = IOCFG_PB15_FUNC_PWM_OUT5;
    //GPIOB->DIR |= GPIO_DIR_15;//PB15配置为输出
    /*P10复用成PWM4功能*/

    IOCFG->PA10 = IOCFG_PA10_FUNC_PWM_OUT4;
    GPIOA->DIR |= GPIO_DIR_10;//PA10配置为输出

    tmpreg = PWM->CTRL & (~PWM_CTRL_PRSC);

    if(PWM_Mode)
        PWM->CTRL = tmpreg | (uint32_t)(0X60);  //  不分频，0x00,8分频 0x60 
    else
        PWM->CTRL = tmpreg | (uint32_t)(0X00);  //  不分频，无法产生低频信号

    PWM->CNFG |= PWM_CNFG_EDG;//Independent PWMs NDEP23

    PWM->CMOD = Period;//周期 24M/8/3000 = 1kHz      1500/3000=50%
    PWM->CTRL |= PWM_CTRL_LDOK;

    //PWM->VAL1 = Value1;//占空值
    PWM->VAL3 = Value2;//占空值
    PWM->VAL5 = Value1;//占空值
    // PWM->VAL4 = Value3;//占空值

    //PWM->CNFG |=PWM_CNFG_NDEP01;//PWM独立输出
    PWM->CNFG |=PWM_CNFG_NDEP23;//PWM独立输出
    PWM->CNFG |=PWM_CNFG_NDEP45;//PWM独立输出

    /* Enable PWM Output */
    PWM->CTRL |= (0x3F000000 | PWM_CTRL_PWMEN);//PWM使能
    PWM->ICCTRL = PWM_ICCTRL_PAD_EN;

    PWM->OUT |= PWM_OUT_OUT1;//PWM1输出
    PWM->OUT |= PWM_OUT_OUT3;//PWM3输出
    //PWM->OUT |= PWM_OUT_OUT5;//PWM5输出
    PWM->OUT |= PWM_OUT_OUT4;//PWM5输出

    PWM->CNTRINI = 0;

    PWM->CTRL |= PWM_CTRL_LDOK;//将分频值，脉宽调制模数，PWM值加载到缓冲区
    //PWM->CNFG |=PWM_CNFG_WP;//写保护
}

void PWM_SetDuty3(uint16_t duty)
{
    uint16_t Value;
    Value = my_div(Period*duty,100);
    PWM->VAL3 = Value;
}

void PWM_SetDuty5(uint16_t duty)
{
    uint16_t Value;
    Value = my_div(Period*duty,100);
    PWM->VAL5 = Value;
}