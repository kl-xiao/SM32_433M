#include "sm32f030_gpio.h"


// 初始化 IO
// PortPin: 取值为 PA0 、PA1 ....
void GPIO_Init(GPIOPortPin_TypeDef PortPin, GPIOMode_TypeDef Mode, uint32_t IoConfig)
{
  uint32_t tmp1, tmp2;
  /* Check the parameters */
  assert_param(CNF_GPIO_ALL_PORT_PINS(PortPin));
  assert_param(CNF_GPIO_MODE(Mode));
  
  tmp2 = (PortPin >> 12);   //GPIO_PIN
  tmp1 = ((PortPin & 0x00000300) << 8) | GPIO_BASE;   //GPIO_Port
  if(Mode == GPIO_Mode_IN)
    ((GPIO_TypeDef*)tmp1)->DIR &= (~tmp2);
  else if(Mode == GPIO_Mode_OUT)
    ((GPIO_TypeDef*)tmp1)->DIR |= tmp2;
    
  tmp1 = ((PortPin & 0x000000FF) | IOCFG_BASE);
  *(uint32_t*)(tmp1) = IoConfig; 
}

void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t Value)
{
  /* Check the parameters */
  assert_param(CNF_GPIO_ALL_PORT(GPIOx));
  
  GPIOx->OUT = Value;
}

void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(CNF_GPIO_ALL_PORT(GPIOx));
  assert_param(CNF_GPIO_PIN(GPIO_Pin));
  
  GPIOx->SET = GPIO_Pin;
}

void GPIO_ClearBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(CNF_GPIO_ALL_PORT(GPIOx));
  assert_param(CNF_GPIO_PIN(GPIO_Pin));
  
  GPIOx->CLR = GPIO_Pin;
}

void GPIO_InvertBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(CNF_GPIO_ALL_PORT(GPIOx));
  assert_param(CNF_GPIO_PIN(GPIO_Pin));
  
  GPIOx->NOT = GPIO_Pin;
}


uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
{
  /* Check the parameters */
  assert_param(CNF_GPIO_ALL_PORT(GPIOx));
  
  return GPIOx->OUT;
}

uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(CNF_GPIO_ALL_PORT(GPIOx));
  assert_param(CNF_GPIO_PIN(GPIO_Pin));
  
  if(GPIOx->OUT & GPIO_Pin)
    return 1;
  else
    return 0;
}

uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
{
  /* Check the parameters */
  assert_param(CNF_GPIO_ALL_PORT(GPIOx));
  
  return GPIOx->PIN;
}

uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(CNF_GPIO_ALL_PORT(GPIOx));
  assert_param(CNF_GPIO_PIN(GPIO_Pin));
  
  if(GPIOx->PIN & GPIO_Pin)
    return 1;
  else
    return 0;
}


void GPIO_SetMask(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(CNF_GPIO_ALL_PORT(GPIOx));
  assert_param(CNF_GPIO_PIN(GPIO_Pin));
  
  GPIOx->MASK = GPIO_Pin;
}


uint16_t GPIO_GetMask(GPIO_TypeDef* GPIOx)
{
  /* Check the parameters */
  assert_param(CNF_GPIO_ALL_PORT(GPIOx));
  
  return GPIOx->MASK;
}


void GPIO_SetMode(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef Mode)
{
  /* Check the parameters */
  assert_param(CNF_GPIO_ALL_PORT(GPIOx));
  assert_param(CNF_GPIO_PIN(GPIO_Pin));
  assert_param(CNF_GPIO_MODE(Mode));
  
  if(Mode == GPIO_Mode_IN)
    GPIOx->DIR &= ~GPIO_Pin;
  else if(Mode == GPIO_Mode_OUT)
    GPIOx->DIR |= GPIO_Pin;
}

uint16_t GPIO_GetMode(GPIO_TypeDef* GPIOx)
{
  /* Check the parameters */
  assert_param(CNF_GPIO_ALL_PORT(GPIOx));
  
  return GPIOx->DIR;
}


void GPIO_ITConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOInterrupt_TypeDef GPIO_Int)
{
  /* Check the parameters */
  assert_param(CNF_GPIO_ALL_PORT(GPIOx));
  assert_param(CNF_GPIO_PIN(GPIO_Pin));
  assert_param(CNF_GPIO_INTERRUPT(GPIO_Int));
  
  switch(GPIO_Int)
  {
  case GPIO_Interrupt_Low:
    GPIOx->IS  |= GPIO_Pin;
    GPIOx->IBE &= ~GPIO_Pin;
    GPIOx->IEV &= ~GPIO_Pin;
    break;
  case GPIO_Interrupt_High:
    GPIOx->IS  |= GPIO_Pin;
    GPIOx->IBE &= ~GPIO_Pin;
    GPIOx->IEV |= GPIO_Pin;
    break;
  case GPIO_Interrupt_Rising:
    GPIOx->IS  &= ~GPIO_Pin;
    GPIOx->IBE &= ~GPIO_Pin;
    GPIOx->IEV |= GPIO_Pin;
    break;
  case GPIO_Interrupt_Falling:
    GPIOx->IS  &= ~GPIO_Pin;
    GPIOx->IBE &= ~GPIO_Pin;
    GPIOx->IEV &= ~GPIO_Pin;
    break;
  case GPIO_Interrupt_Rising_Falling:
    GPIOx->IS  &= ~GPIO_Pin;
    GPIOx->IBE |= GPIO_Pin;
    /* GPIOx->IEV not care */
    break;
  }
}

void GPIO_ITCmd(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(CNF_GPIO_ALL_PORT(GPIOx));
  assert_param(CNF_GPIO_PIN(GPIO_Pin));
  assert_param(CNF_FUNCTIONAL_STATE(NewState));
  
  if(NewState == ENABLE)
    GPIOx->IE |= GPIO_Pin;
  else
    GPIOx->IE &= ~GPIO_Pin;
}

ITStatus GPIO_GetRawITStatus(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(CNF_GPIO_ALL_PORT(GPIOx));
  assert_param(CNF_GPIO_PIN(GPIO_Pin));
  
  if(GPIOx->RIS & GPIO_Pin)
    return SET;
  else
    return RESET;
}

ITStatus GPIO_GetITStatus(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(CNF_GPIO_ALL_PORT(GPIOx));
  assert_param(CNF_GPIO_PIN(GPIO_Pin));
  
  if(GPIOx->MIS & GPIO_Pin)
    return SET;
  else
    return RESET;
}

void GPIO_ClearITPendingBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(CNF_GPIO_ALL_PORT(GPIOx));
  assert_param(CNF_GPIO_PIN(GPIO_Pin));
  
  GPIOx->IC = GPIO_Pin;
}

