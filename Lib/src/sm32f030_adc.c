#include "sm32f030_adc.h"


void ADC_DeInit(void)
{
  //Reset ADC
  SYSCON->PRESETCTRL &= (~SYSCON_PRESETCTRL_ADC_RST_N);
  SYSCON->PRESETCTRL |= SYSCON_PRESETCTRL_ADC_RST_N;
  //Power down ADC
  SYSCON->PDRUNCFG |= SYSCON_PDRUNCFG_ADC_PD;
  //disable clock of ADC digital
  SYSCON->SYSAHBCLKCTRL &= (~SYSCON_SYSAHBCLKCTRL_ADCEN);
}

void ADC_Init(ADC_InitTypeDef* ADC_InitStruct)
{
  uint8_t div;
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(CNF_FUNCTIONAL_STATE(ADC_InitStruct->ADC_BurstMode));
  assert_param(CNF_ADC_SAMPLERATE(ADC_InitStruct->ADC_SampleRate));
  assert_param(CNF_ADC_TRIGGERSOURCE(ADC_InitStruct->ADC_TriggerSource));
  assert_param(CNF_ADC_TRIGGEREDGE(ADC_InitStruct->ADC_TriggerEdge));
  
  // Power up ADC
  SYSCON->PDRUNCFG &= (~SYSCON_PDRUNCFG_ADC_PD);
  SYSCON->SYSAHBCLKCTRL |= SYSCON_SYSAHBCLKCTRL_ADCEN;
  
  ADC->CHSEL = 0x76543210;
  
  div = SystemCoreClock / (ADC_InitStruct->ADC_SampleRate * 16);
  
  // 确保转换时钟频率不超过16Mhz
  if((SystemCoreClock / div) > ADC_ConvertClock_Max)
    ++div;
  
  /* Set CLKDIV bits */
  tmpreg |= div << 8;
  
  if(ADC_InitStruct->ADC_BurstMode != DISABLE)
    tmpreg |= ADC_CR_BURST;
  
  tmpreg |= ADC_InitStruct->ADC_TriggerSource;
  tmpreg |= ADC_InitStruct->ADC_TriggerEdge;
  
  ADC->CR = tmpreg;
  
  //insert a delay
  div = 0xFF;
  while(div--);
  
  /* SCMODE must be 1 */
  ADC->CR |= ADC_CR_SCMODE;
  
  /* wait ADC ready */
  while(!(ADC->STAT & ADC_STAT_ADCRDY));
}

void ADC_ChannelCmd(uint8_t ADC_Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(CNF_ADC_CHANNEL(ADC_Channel));

  ADC->CR &= ~ADC_CR_SCMODE;

  if(NewState != DISABLE)
    ADC->CR |= ADC_Channel;
  else
    ADC->CR &= (~ADC_Channel);

  ADC->CR |= ADC_CR_SCMODE;
}

void ADC_ITCmd(uint16_t ADC_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(CNF_ADC_IT(ADC_IT));
  assert_param(CNF_FUNCTIONAL_STATE(NewState));

  if(NewState != DISABLE)
  {
    ADC->INTEN |= ADC_IT;
  }
  else
  {
    ADC->INTEN &= (~ADC_IT);
  }
}


FlagStatus ADC_GetFlagStatus(uint32_t ADC_FLAG)
{
  /* Check the parameters */
  assert_param(CNF_ADC_FLAG(ADC_FLAG));
  
  if(ADC->STAT & ADC_FLAG)
    return SET;
  else
    return RESET;
}

void ADC_ClearFlag(uint32_t ADC_FLAG)
{
  /* Check the parameters */
  assert_param(CNF_ADC_FLAG(ADC_FLAG));
  
  ADC->STAT = ADC_FLAG;
}

/**
 * 获取ADC 相应数据寄存器的值
**/
uint32_t ADC_GetDataRegister(uint8_t iDR)
{
  if(iDR>7)   iDR = 0;
  return ADC->DR[iDR];
}

void ADC_HiLimit0Config(uint16_t HiLimit0, FunctionalState INT_NEWSTATE)
{
  uint32_t tmpreg;
  /* Check the parameters */
  assert_param(CNF_FUNCTIONAL_STATE(INT_NEWSTATE));
  
  tmpreg = ADC->HILMT & 0xFFFF0000;
  tmpreg |= (HiLimit0 & 0x0FFF);
  if(INT_NEWSTATE != DISABLE)
  {
    tmpreg |= ADC_HILMT_INTEN0;
  }
  
  ADC->HILMT = tmpreg;
}


void ADC_HiLimit1Config(uint16_t HiLimit1, FunctionalState INT_NEWSTATE)
{
  uint32_t tmpreg;
  /* Check the parameters */
  assert_param(CNF_FUNCTIONAL_STATE(INT_NEWSTATE));
  
  tmpreg = ADC->HILMT & 0x0000FFFF;
  tmpreg |= ((HiLimit1 & 0x0FFF) << 16);
  if(INT_NEWSTATE != DISABLE)
  {
    tmpreg |= ADC_HILMT_INTEN1;
  }
  
  ADC->HILMT = tmpreg;
}

void ADC_LoLimit0Config(uint16_t LoLimit0, FunctionalState INT_NEWSTATE)
{
  uint32_t tmpreg;
  /* Check the parameters */
  assert_param(CNF_FUNCTIONAL_STATE(INT_NEWSTATE));
  
  tmpreg = ADC->LOLMT & 0xFFFF0000;
  tmpreg |= (LoLimit0 & 0x0FFF);
  if(INT_NEWSTATE != DISABLE)
  {
    tmpreg |= ADC_LOLMT_INTEN0;
  }
  
  ADC->LOLMT = tmpreg;
}

void ADC_LoLimit1Config(uint16_t LoLimit1, FunctionalState INT_NEWSTATE)
{
  uint32_t tmpreg;
  /* Check the parameters */
  assert_param(CNF_FUNCTIONAL_STATE(INT_NEWSTATE));
  
  tmpreg = ADC->LOLMT & 0x0000FFFF;
  tmpreg |= ((LoLimit1 & 0x0FFF) << 16);
  if(INT_NEWSTATE != DISABLE)
  {
    tmpreg |= ADC_LOLMT_INTEN1;
  }
  
  ADC->LOLMT = tmpreg;
}









