#include "pwm.h"
#include "div.h"

uint8_t PWM_Mode = 0;
uint32_t Period;

/**
 * @��������: PWM��ʼ��
 * @�����β�: Ratio1 ռ�ձ� freq --Ƶ�� khz
 * @����ֵ:
 * @��ע:
 */
void pwm_init(uint16_t Ratio1, uint16_t freq)
{
    uint32_t tmpreg;
    uint16_t Value1;
    uint16_t Value2;
    // uint16_t Value3;
    //���� 24M/8/3000 = 1000Hz      1500/3000=50%
    if(PWM_Mode)    //��Ƶ
        Period = my_div(3000000,freq);  //1 Ƶ��1hz  10 10hz
    else            //��Ƶ
        Period = my_div(24000,freq);    //1 Ƶ��1Khz  10 10Khz  

    Value1 = my_div(Period*Ratio1,100);
    Value2 = my_div(Period*Ratio1,100);
    // Value3 = my_div(Period*Ratio3,100);
    // Value1 = Ratio1;
    // Value2 = Ratio1;
    // Value3 = Ratio1;

    SYSCON->SYSAHBCLKCTRL |= SYSCON_SYSAHBCLKCTRL_PWMEN;//��PWMʱ��
    SYSCON->SYSAHBCLKCTRL |= SYSCON_SYSAHBCLKCTRL_GPIOAEN;//��PA��ʱ��
    SYSCON->SYSAHBCLKCTRL |= SYSCON_SYSAHBCLKCTRL_GPIOBEN;//��PB��ʱ��

    /*PA7���ó�PWM1����*/
    //IOCFG->PA7 = IOCFG_PA7_FUNC_PWM_OUT1;
    //GPIOA->DIR |= GPIO_DIR_7;//PA7����Ϊ���
    /*PB0���ó�PWM3����*/
    IOCFG->PB0 = IOCFG_PB0_FUNC_PWM_OUT3;
    GPIOB->DIR |= GPIO_DIR_0;//PB0����Ϊ���
    /*PB1���ó�PWM5����*/
    IOCFG->PB1 = IOCFG_PB1_FUNC_PWM_OUT5;
    GPIOB->DIR |= GPIO_DIR_1;//PB1����Ϊ���
    /*PB15���ó�PWM5����*/
    //IOCFG->PB15 = IOCFG_PB15_FUNC_PWM_OUT5;
    //GPIOB->DIR |= GPIO_DIR_15;//PB15����Ϊ���
    /*P10���ó�PWM4����*/

    IOCFG->PA10 = IOCFG_PA10_FUNC_PWM_OUT4;
    GPIOA->DIR |= GPIO_DIR_10;//PA10����Ϊ���

    tmpreg = PWM->CTRL & (~PWM_CTRL_PRSC);

    if(PWM_Mode)
        PWM->CTRL = tmpreg | (uint32_t)(0X60);  //  ����Ƶ��0x00,8��Ƶ 0x60 
    else
        PWM->CTRL = tmpreg | (uint32_t)(0X00);  //  ����Ƶ���޷�������Ƶ�ź�

    PWM->CNFG |= PWM_CNFG_EDG;//Independent PWMs NDEP23

    PWM->CMOD = Period;//���� 24M/8/3000 = 1kHz      1500/3000=50%
    PWM->CTRL |= PWM_CTRL_LDOK;

    //PWM->VAL1 = Value1;//ռ��ֵ
    PWM->VAL3 = Value2;//ռ��ֵ
    PWM->VAL5 = Value1;//ռ��ֵ
    // PWM->VAL4 = Value3;//ռ��ֵ

    //PWM->CNFG |=PWM_CNFG_NDEP01;//PWM�������
    PWM->CNFG |=PWM_CNFG_NDEP23;//PWM�������
    PWM->CNFG |=PWM_CNFG_NDEP45;//PWM�������

    /* Enable PWM Output */
    PWM->CTRL |= (0x3F000000 | PWM_CTRL_PWMEN);//PWMʹ��
    PWM->ICCTRL = PWM_ICCTRL_PAD_EN;

    PWM->OUT |= PWM_OUT_OUT1;//PWM1���
    PWM->OUT |= PWM_OUT_OUT3;//PWM3���
    //PWM->OUT |= PWM_OUT_OUT5;//PWM5���
    PWM->OUT |= PWM_OUT_OUT4;//PWM5���

    PWM->CNTRINI = 0;

    PWM->CTRL |= PWM_CTRL_LDOK;//����Ƶֵ���������ģ����PWMֵ���ص�������
    //PWM->CNFG |=PWM_CNFG_WP;//д����
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