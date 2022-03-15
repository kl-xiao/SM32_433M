#include "key.h"


/**
 * @��������:  ������ʼ��
 * @�����β�:
 * @����ֵ:
 * @��ע:       PA0--key0 PA1--key2  PA11--key3 PA12--key4
 */
void key_init(void)
{
    SYSCON->SYSAHBCLKCTRL |= SYSCON_SYSAHBCLKCTRL_GPIOAEN;//��PA��ʱ��

    //PA0--key0
    IOCFG->PA0 = IOCFG_PA0_FUNC_PA0;//PA0����ΪIO����
    GPIOA->DIR &= ~(GPIO_DIR_0);//PA0����Ϊ����
    //PA1--key2
    IOCFG->PA1 = IOCFG_PA1_FUNC_PA1;//PA1����ΪIO����
    GPIOA->DIR &= ~(GPIO_DIR_1);//PA1����Ϊ����
    //PA11--key3
    IOCFG->PA11 = IOCFG_PA11_FUNC_PA11;//PA11����ΪIO����
    GPIOA->DIR &= ~(GPIO_DIR_11);//PA11����Ϊ����
    //PA12--key4
    IOCFG->PA12 = IOCFG_PA12_FUNC_PA12;//PA12����ΪIO����
    GPIOA->DIR &= ~(GPIO_DIR_12);//PA12����Ϊ����

}

/**
 * @��������:  ������⣬����
 * @�����β�:
 * @����ֵ:    ��ֵ
 * @��ע:       PA0--key0 PA1--key2  PA11--key3 PA12--key4
 */
static uint8_t key4_scan(void)
{
    uint8_t count = 0;
    while(key4 == ON)
    {
        count++;
        delay_ms(10);
        if(count == 50)
        {
            count = 0;
            return 5;//����
        }
    }
    return 4;
}

static uint8_t key3_scan(void)
{
    uint8_t count = 0;
    while(key3 == ON)
    {
        count++;
        delay_ms(10);
        if(count == 50)
        {
            count = 0;
            return 6;//����
        }
    }
    return 3;
}
/**
 * @��������:  �������,�̰�
 * @�����β�:
 * @����ֵ:    ������
 * @��ע:      PA0--key0 PA1--key2  PA11--key3 PA12--key4
 */

uint8_t key_scan(void)
{
    static uint8_t key_flag =0 ;

    if( (!key_flag ) && ( (key4==0) || (key2==0 ) || (key3==0) || ( key1==0) ) ) //��ⰴ���Ƿ񱻰���
    {
        key_flag  = 1;
        delay_ms(30);//��ʱ����


         if( key2 == 0 )
        {
            return 2;      //����2���·���2
        }
        else if( key3 == 0 )
        {
            return key3_scan();      //����3���·���3
        }
         else if( key4 == 0 )
        {
            return key4_scan();      //����4���·���4
        }
        else if( key1 ==0 )
        {
            return 1;       //����1���·���1
        }
    }
    else if( (key1==1 ) &&(key2 ==1)  && (key3 ==1) && (key4==1))//û�а�������
    {
        key_flag = 0;
    }
    return 0;
}


