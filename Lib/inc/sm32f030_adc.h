#ifndef __SM32F030_ADC_H
#define __SM32F030_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "sm32f030.h"



// ADC转换时钟频率最大是16Mhz
#define ADC_ConvertClock_Max    (16000000)

// ADC采样率最大为1Mhz
#define ADC_SampleRate_Max      (1000000)
#define CNF_ADC_SAMPLERATE(RATE) ((RATE) <= ADC_SampleRate_Max)


#define ADC_Channel_0       (uint8_t)0x01
#define ADC_Channel_1       (uint8_t)0x02
#define ADC_Channel_2       (uint8_t)0x04
#define ADC_Channel_3       (uint8_t)0x08
#define ADC_Channel_4       (uint8_t)0x10
#define ADC_Channel_5       (uint8_t)0x20
#define ADC_Channel_6       (uint8_t)0x40
#define ADC_Channel_7       (uint8_t)0x80
#define ADC_Channel_All     (uint8_t)0xFF
#define CNF_ADC_CHANNEL(CHANNEL)  (1)


typedef enum
{
  ADC_TriggerSource_No            = 0x00000000,
  ADC_TriggerSource_Software      = ADC_CR_START_SOFTWARE,
  ADC_TriggerSource_TIM2_CAP0     = ADC_CR_START_TIM2_CAP0,
  ADC_TriggerSource_TIM2_CAP1     = ADC_CR_START_TIM2_CAP1,
  ADC_TriggerSource_TIM2_MAT0     = ADC_CR_START_TIM2_MAT0,
  ADC_TriggerSource_TIM2_MAT1     = ADC_CR_START_TIM2_MAT1,
  ADC_TriggerSource_TIM3_MAT0     = ADC_CR_START_TIM3_MAT0,
  ADC_TriggerSource_TIM3_MAT1     = ADC_CR_START_TIM3_MAT1,
  ADC_TriggerSource_PWM_Reload    = ADC_CR_START_PWM_RELOAD,
} ADCTriggerSource_TypeDef;
#define CNF_ADC_TRIGGERSOURCE(SOURCE) (((SOURCE) == ADC_TriggerSource_No)             || \
                                       ((SOURCE) == ADC_TriggerSource_Software)       || \
                                       ((SOURCE) == ADC_TriggerSource_TIM2_CAP0)      || \
                                       ((SOURCE) == ADC_TriggerSource_TIM2_CAP1)      || \
                                       ((SOURCE) == ADC_TriggerSource_TIM2_MAT0)      || \
                                       ((SOURCE) == ADC_TriggerSource_TIM2_MAT1)      || \
                                       ((SOURCE) == ADC_TriggerSource_TIM3_MAT0)      || \
                                       ((SOURCE) == ADC_TriggerSource_TIM3_MAT1))


typedef enum
{
  ADC_TriggerEdge_Rising          = 0x00000000,
  ADC_TriggerEdge_Falling         = ADC_CR_EDGE,
} ADCTriggerEdge_TypeDef;
#define CNF_ADC_TRIGGEREDGE(EDGE) (((EDGE) == ADC_TriggerEdge_Rising) || ((EDGE) == ADC_TriggerEdge_Falling))




/** 
  * @brief  ADC Init structure definition
  */ 
typedef struct
{
  FunctionalState           ADC_BurstMode;        /*!< ENABLE: ADC work in burstmode; DISABLE: ADC work in trigger mode */
  uint32_t                  ADC_SampleRate;       /*!< Specifies ADC Sample Rate ( <= 1000000Hz ) */
  ADCTriggerSource_TypeDef  ADC_TriggerSource;    /*!< If ADC_BurstMode is DISABLE, this member select trigger source */
  ADCTriggerEdge_TypeDef    ADC_TriggerEdge;      /*!< Specifies ADC trigger edge */
} ADC_InitTypeDef;




/** @defgroup ADC_Interrupts
  * @{
  */
#define ADC_IT_CH0      (uint16_t)0x0001
#define ADC_IT_CH1      (uint16_t)0x0002
#define ADC_IT_CH2      (uint16_t)0x0004
#define ADC_IT_CH3      (uint16_t)0x0008
#define ADC_IT_CH4      (uint16_t)0x0010
#define ADC_IT_CH5      (uint16_t)0x0020
#define ADC_IT_CH6      (uint16_t)0x0040
#define ADC_IT_CH7      (uint16_t)0x0080
#define ADC_IT_GCH      (uint16_t)0x0100
#define CNF_ADC_IT(IT) (1)
/**
  * @}
  */



/** @defgroup ADC_Flags 
  * @{
  */
#define ADC_FLAG_CH0_DONE         ADC_STAT_DR0_DONE
#define ADC_FLAG_CH1_DONE         ADC_STAT_DR1_DONE
#define ADC_FLAG_CH2_DONE         ADC_STAT_DR2_DONE
#define ADC_FLAG_CH3_DONE         ADC_STAT_DR3_DONE
#define ADC_FLAG_CH4_DONE         ADC_STAT_DR4_DONE
#define ADC_FLAG_CH5_DONE         ADC_STAT_DR5_DONE
#define ADC_FLAG_CH6_DONE         ADC_STAT_DR6_DONE
#define ADC_FLAG_CH7_DONE         ADC_STAT_DR7_DONE
#define ADC_FLAG_ADINT            ADC_STAT_ADINT
#define ADC_FLAG_HILMTFLAG0       ADC_STAT_HILMTFLAG0
#define ADC_FLAG_HILMTFLAG1       ADC_STAT_HILMTFLAG1
#define ADC_FLAG_LOLMTFLAG0       ADC_STAT_LOLMTFLAG0
#define ADC_FLAG_LOLMTFLAG1       ADC_STAT_LOLMTFLAG1
#define ADC_FLAG_ADCRDY           ADC_STAT_ADCRDY
#define CNF_ADC_FLAG(FLAG)    (1)
/**
  * @}
  */ 




void ADC_DeInit(void);
void ADC_Init(ADC_InitTypeDef* ADC_InitStruct);
void ADC_ChannelCmd(uint8_t ADC_Channel, FunctionalState NewState);
void ADC_ITCmd(uint16_t ADC_IT, FunctionalState NewState);
FlagStatus ADC_GetFlagStatus(uint32_t ADC_FLAG);
void ADC_ClearFlag(uint32_t ADC_FLAG);
uint32_t ADC_GetDataRegister(uint8_t iDR);    //参数范围 0-7
void ADC_HiLimit0Config(uint16_t HiLimit0, FunctionalState INT_NEWSTATE);
void ADC_HiLimit1Config(uint16_t HiLimit1, FunctionalState INT_NEWSTATE);
void ADC_LoLimit0Config(uint16_t LoLimit0, FunctionalState INT_NEWSTATE);
void ADC_LoLimit1Config(uint16_t LoLimit1, FunctionalState INT_NEWSTATE);
#define ADC_SoftwareTrigger()   (ADC->SSCR = 1)     //软件触发一次转换



#ifdef __cplusplus
}
#endif

#endif /* __SM32F030_ADC_H */

