#ifndef __SM32F030_TIM_H
#define __SM32F030_TIM_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "sm32f030.h"



#define CNF_TIM_ALL_PERIPH(PERIPH) (((PERIPH) == TIM0) || \
                                    ((PERIPH) == TIM1) || \
                                    ((PERIPH) == TIM2) || \
                                    ((PERIPH) == TIM3))
                                    
                                    
#define CNF_TIM_ADVANCED_PERIPH(PERIPH) (((PERIPH) == TIM2) || \
                                         ((PERIPH) == TIM3))





/** @defgroup TIM_Match_Mode
  * @{
  */
  
#define TIM_Match_Interrupt           (0x00000001)    /* 当匹配寄存器的值与计数器的值匹配时，触发中断 */
#define TIM_Match_CounterReset        (0x00000002)    /* 当匹配寄存器的值与计数器的值匹配时，计数器归零 */
#define TIM_Match_Stop                (0x00000004)    /* 当匹配寄存器的值与计数器的值匹配时，定时器停止 */

#define CNF_TIM_MATCH(MATCH) (1)

/**
  * @}
  */ 
  
  
  
  
/** @defgroup TIM_Interrupt_definition 
  * @{
  */
#define TIM_IT_MAT0                       TIM_IR_MR0INT
#define TIM_IT_MAT1                       TIM_IR_MR1INT
#define TIM_IT_MAT2                       TIM_IR_MR2INT
#define TIM_IT_MAT3                       TIM_IR_MR3INT
#define TIM_IT_CAP0                       TIM_IR_CR0INT
#define TIM_IT_CAP1                       TIM_IR_CR1INT
#define TIM_IT_CAP2                       TIM_IR_CR2INT
#define TIM_IT_CAP3                       TIM_IR_CR3INT

#define CNF_TIM_IT(IT) (1)
/**
  * @}
  */





void TIM_DeInit(TIM_TypeDef* TIMx);
void TIM_SetPrescaler(TIM_TypeDef* TIMx, uint16_t Prescaler);
void TIM_SetCounter(TIM_TypeDef* TIMx, uint16_t Counter);
uint16_t TIM_GetPrescaler(TIM_TypeDef* TIMx);
uint16_t TIM_GetCounter(TIM_TypeDef* TIMx);
void TIM_CounterReset(TIM_TypeDef* TIMx);
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_Match0Config(TIM_TypeDef* TIMx, uint16_t Match, uint16_t TIM_MatchMode);
void TIM_Match1Config(TIM_TypeDef* TIMx, uint16_t Match, uint16_t TIM_MatchMode);
void TIM_Match2Config(TIM_TypeDef* TIMx, uint16_t Match, uint16_t TIM_MatchMode);
void TIM_Match3Config(TIM_TypeDef* TIMx, uint16_t Match, uint16_t TIM_MatchMode);
ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, uint8_t TIM_IT);
void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint8_t TIM_IT);


#ifdef __cplusplus
}
#endif

#endif /* __SM32F030_TIM_H */

