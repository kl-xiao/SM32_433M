#include "sm32f030_tim.h"


void TIM_DeInit(TIM_TypeDef* TIMx)
{
  uint32_t tmpFlag;
  /* Check the parameters */
  assert_param(CNF_TIM_ALL_PERIPH(TIMx));
  
  switch((uint32_t)TIMx)
  {
  case TIM0_BASE:
    tmpFlag = SYSCON_AHBRESET_TIM0;
    break;
  case TIM1_BASE:
    tmpFlag = SYSCON_AHBRESET_TIM1;
    break;
  case TIM2_BASE:
    tmpFlag = SYSCON_AHBRESET_TIM2;
    break;
  case TIM3_BASE:
    tmpFlag = SYSCON_AHBRESET_TIM3;
    break;
  default:
    return;
  }
  
  SYSCON_AHBPeriphResetCmd(tmpFlag, ENABLE);
  SYSCON_AHBPeriphResetCmd(tmpFlag, DISABLE);
}


void TIM_SetPrescaler(TIM_TypeDef* TIMx, uint16_t Prescaler)
{
  /* Check the parameters */
  assert_param(CNF_TIM_ALL_PERIPH(TIMx));
  
  TIMx->PR = Prescaler;
}

void TIM_SetCounter(TIM_TypeDef* TIMx, uint16_t Counter)
{
  /* Check the parameters */
  assert_param(CNF_TIM_ALL_PERIPH(TIMx));
  
  TIMx->TC = Counter;
}

uint16_t TIM_GetPrescaler(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(CNF_TIM_ALL_PERIPH(TIMx));
  
  return TIMx->PR;
}

uint16_t TIM_GetCounter(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(CNF_TIM_ALL_PERIPH(TIMx));
  
  return TIMx->TC;
}

// 复位计数器和预分频器的计数器  复位之后，TIM会关闭
void TIM_CounterReset(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(CNF_TIM_ALL_PERIPH(TIMx));
  
  TIMx->TCR |= TIM_TCR_CRST;
  TIMx->TCR = 0x00;
}

void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(CNF_TIM_ALL_PERIPH(TIMx));
  assert_param(CNF_FUNCTIONAL_STATE(NewState));
  
  if(NewState != DISABLE)
  {
    /* Enable the TIMx peripheral */
    TIMx->TCR |= TIM_TCR_CEN;
  }
  else
  {
    /* Disable the TIMx peripheral */
    TIMx->TCR &= (~TIM_TCR_CEN);
  }
}

void TIM_Match0Config(TIM_TypeDef* TIMx, uint16_t Match, uint16_t TIM_MatchMode)
{
  uint32_t tmpreg;
  /* Check the parameters */
  assert_param(CNF_TIM_ALL_PERIPH(TIMx));
  assert_param(CNF_TIM_MATCH(TIM_MatchMode));
  
  TIMx->MR0 = Match; 
  
  tmpreg = TIMx->MCR;
  tmpreg &= 0xFFFFFFF8;
  tmpreg |= TIM_MatchMode;
  TIMx->MCR = tmpreg;
}

void TIM_Match1Config(TIM_TypeDef* TIMx, uint16_t Match, uint16_t TIM_MatchMode)
{
  uint32_t tmpreg;
  /* Check the parameters */
  assert_param(CNF_TIM_ALL_PERIPH(TIMx));
  assert_param(CNF_TIM_MATCH(TIM_MatchMode));
  
  TIMx->MR1 = Match; 
  
  tmpreg = TIMx->MCR;
  tmpreg &= 0xFFFFFFC7;
  tmpreg |= (TIM_MatchMode << 3);
  TIMx->MCR = tmpreg;
}

void TIM_Match2Config(TIM_TypeDef* TIMx, uint16_t Match, uint16_t TIM_MatchMode)
{
  uint32_t tmpreg;
  /* Check the parameters */
  assert_param(CNF_TIM_ALL_PERIPH(TIMx));
  assert_param(CNF_TIM_MATCH(TIM_MatchMode));
  
  TIMx->MR2 = Match; 
  
  tmpreg = TIMx->MCR;
  tmpreg &= 0xFFFFFE3F;
  tmpreg |= (TIM_MatchMode << 6);
  TIMx->MCR = tmpreg;
}

void TIM_Match3Config(TIM_TypeDef* TIMx, uint16_t Match, uint16_t TIM_MatchMode)
{
  uint32_t tmpreg;
  /* Check the parameters */
  assert_param(CNF_TIM_ALL_PERIPH(TIMx));
  assert_param(CNF_TIM_MATCH(TIM_MatchMode));
  
  TIMx->MR3 = Match; 
  
  tmpreg = TIMx->MCR;
  tmpreg &= 0xFFFFF1FF;
  tmpreg |= (TIM_MatchMode << 9);
  TIMx->MCR = tmpreg;
}

ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, uint8_t TIM_IT)
{
  /* Check the parameters */
  assert_param(CNF_TIM_ALL_PERIPH(TIMx));
  assert_param(CNF_TIM_IT(TIM_IT));
  
  if(TIMx->IR & TIM_IT)
    return SET;
  else
    return RESET;
}

void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint8_t TIM_IT)
{
  /* Check the parameters */
  assert_param(CNF_TIM_ALL_PERIPH(TIMx));
  assert_param(CNF_TIM_IT(TIM_IT));
  
  TIMx->IR = TIM_IT;
}




