#include "adc.h"
#include "uart.h"

void adc_init(uint8_t adc_ch)
{
    ADC_InitTypeDef ADC_InitStruct;

    for(uint8_t mask=0x01; mask!=0; mask<<=1)
    {
        switch (adc_ch & mask)
        {
            case 0x01: GPIO_Init(PA0, GPIO_Mode_IN, IOCFG_ADM | IOCFG_PA0_FUNC_ADC_IN0);    break;
            case 0x02: GPIO_Init(PA1, GPIO_Mode_IN, IOCFG_ADM | IOCFG_PA1_FUNC_ADC_IN1);    break;
            case 0x04: GPIO_Init(PA2, GPIO_Mode_IN, IOCFG_ADM | IOCFG_PA2_FUNC_ADC_IN2);    break;
            case 0x08: GPIO_Init(PA3, GPIO_Mode_IN, IOCFG_ADM | IOCFG_PA3_FUNC_ADC_IN3);    break;
            case 0x10: GPIO_Init(PA4, GPIO_Mode_IN, IOCFG_ADM | IOCFG_PA4_FUNC_ADC_IN4);    break;
            case 0x20: GPIO_Init(PA5, GPIO_Mode_IN, IOCFG_ADM | IOCFG_PA5_FUNC_ADC_IN5);    break;
            case 0x40: GPIO_Init(PA6, GPIO_Mode_IN, IOCFG_ADM | IOCFG_PA6_FUNC_ADC_IN6);    break;
            case 0x80: GPIO_Init(PA7, GPIO_Mode_IN, IOCFG_ADM | IOCFG_PA7_FUNC_ADC_IN7);    break;        
            default:    break;
        }        
    }

    ADC_InitStruct.ADC_BurstMode = DISABLE;    
    ADC_InitStruct.ADC_SampleRate = 1000000;   
    ADC_InitStruct.ADC_TriggerSource = ADC_TriggerSource_Software;
    ADC_InitStruct.ADC_TriggerEdge = ADC_TriggerEdge_Rising;  

    ADC_Init(&ADC_InitStruct);
	ADC_ChannelCmd(adc_ch, ENABLE);

    ADC_ITCmd(adc_ch, ENABLE);
}

uint16_t adc_getvalue(uint8_t ch)
{
    uint16_t adc_tmp = 0;
    for(uint8_t i=0; i<4; i++)
    {
        ADC_SoftwareTrigger();
        delay_us(100);
        adc_tmp += (ADC_GetDataRegister(ch) & ADC_DR_RESULT);
    }    
    return (adc_tmp>>2);
}