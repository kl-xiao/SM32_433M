#include "key.h"


/**
 * @函数功能:  按键初始化
 * @函数形参:
 * @返回值:
 * @备注:       PA0--key0 PA1--key2  PA11--key3 PA12--key4
 */
void key_init(void)
{
    SYSCON->SYSAHBCLKCTRL |= SYSCON_SYSAHBCLKCTRL_GPIOAEN;//打开PA组时钟

    //PA0--key0
    IOCFG->PA0 = IOCFG_PA0_FUNC_PA0;//PA0配置为IO功能
    GPIOA->DIR &= ~(GPIO_DIR_0);//PA0配置为输入
    //PA1--key2
    IOCFG->PA1 = IOCFG_PA1_FUNC_PA1;//PA1配置为IO功能
    GPIOA->DIR &= ~(GPIO_DIR_1);//PA1配置为输入
    //PA11--key3
    IOCFG->PA11 = IOCFG_PA11_FUNC_PA11;//PA11配置为IO功能
    GPIOA->DIR &= ~(GPIO_DIR_11);//PA11配置为输入
    //PA12--key4
    IOCFG->PA12 = IOCFG_PA12_FUNC_PA12;//PA12配置为IO功能
    GPIOA->DIR &= ~(GPIO_DIR_12);//PA12配置为输入

}

/**
 * @函数功能:  按键检测，长按
 * @函数形参:
 * @返回值:    键值
 * @备注:       PA0--key0 PA1--key2  PA11--key3 PA12--key4
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
            return 5;//长按
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
            return 6;//长按
        }
    }
    return 3;
}
/**
 * @函数功能:  按键检测,短按
 * @函数形参:
 * @返回值:    按键号
 * @备注:      PA0--key0 PA1--key2  PA11--key3 PA12--key4
 */

uint8_t key_scan(void)
{
    static uint8_t key_flag =0 ;

    if( (!key_flag ) && ( (key4==0) || (key2==0 ) || (key3==0) || ( key1==0) ) ) //检测按键是否被按下
    {
        key_flag  = 1;
        delay_ms(30);//延时消抖


         if( key2 == 0 )
        {
            return 2;      //按键2按下返回2
        }
        else if( key3 == 0 )
        {
            return key3_scan();      //按键3按下返回3
        }
         else if( key4 == 0 )
        {
            return key4_scan();      //按键4按下返回4
        }
        else if( key1 ==0 )
        {
            return 1;       //按键1按下返回1
        }
    }
    else if( (key1==1 ) &&(key2 ==1)  && (key3 ==1) && (key4==1))//没有按键按下
    {
        key_flag = 0;
    }
    return 0;
}


