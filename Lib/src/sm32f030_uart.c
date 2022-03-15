#include "sm32f030_uart.h"

void UART_DeInit(UART_TypeDef* UARTx)
{
  /* Check the parameters */
  assert_param(CNF_UART_ALL_PERIPH(UARTx));
  
  if(UARTx == UART0)
  {
    SYSCON_AHBPeriphResetCmd(SYSCON_AHBRESET_UART0, ENABLE);
    SYSCON_AHBPeriphResetCmd(SYSCON_AHBRESET_UART0, DISABLE);
  }
  else if(UARTx == UART1)
  {
    SYSCON_AHBPeriphResetCmd(SYSCON_AHBRESET_UART1, ENABLE);
    SYSCON_AHBPeriphResetCmd(SYSCON_AHBRESET_UART1, DISABLE);
  }
}

void UART_Init(UART_TypeDef* UARTx, uint32_t Baud, uint32_t Parity, uint32_t Mode)
{
  uint32_t tmpreg;
  /* Check the parameters */
  assert_param(CNF_UART_ALL_PERIPH(UARTx));
  assert_param(CNF_UART_PARITY(Parity));
  assert_param(CNF_UART_MODE(Mode));
  
  if(UARTx == UART0)
    SYSCON->UART0CLKDIV = 1;
  else if(UARTx == UART1)
    SYSCON->UART1CLKDIV = 1;
  
  UARTx->BAUDDIV = my_div(MainClock , Baud);
  
  tmpreg = UARTx->CR;
  tmpreg &= 0xFF3FFCFF;
  tmpreg |= (Parity | Mode);
  UARTx->CR = tmpreg;
}

void UART_WriteFIFO(UART_TypeDef* UARTx, uint8_t Data)
{
  /* Check the parameters */
  assert_param(CNF_UART_ALL_PERIPH(UARTx));
  
  UARTx->DR = Data;
}

uint8_t UART_ReadFIFO(UART_TypeDef* UARTx)
{
  /* Check the parameters */
  assert_param(CNF_UART_ALL_PERIPH(UARTx));
  
  return UARTx->DR;
}

void UART_ClearFIFO(UART_TypeDef* UARTx, uint32_t UART_FIFO)
{
  /* Check the parameters */
  assert_param(CNF_UART_ALL_PERIPH(UARTx));
  assert_param(CNF_UART_FIFO(UART_FIFO));
  
  UARTx->FIFOCLR = UART_FIFO;
}

void UART_Send(UART_TypeDef* UARTx, const uint8_t* txBuf, uint16_t txLen)
{
  /* Check the parameters */
  assert_param(CNF_UART_ALL_PERIPH(UARTx));
  assert_param(txBuf != 0);
  
  while(txLen--)
  {
    while(UARTx->SR & UART_SR_TXF);
    UARTx->DR = *txBuf++;
  }
  
  while(UARTx->SR & UART_SR_TXNE);   //等待数据发送完成
}


void UART_ITConfig(UART_TypeDef* UARTx, uint8_t UART_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(CNF_UART_ALL_PERIPH(UARTx));
  assert_param(CNF_UART_IT(UART_IT));
  assert_param(CNF_FUNCTIONAL_STATE(NewState));
  
  if(NewState == ENABLE)
  {
    UARTx->CR |= UART_IT;
  }
  else
  {
    UARTx->CR &= (~UART_IT);
  }
}

FlagStatus UART_GetFlagStatus(UART_TypeDef* UARTx, uint8_t UART_FLAG)
{
  /* Check the parameters */
  assert_param(CNF_UART_ALL_PERIPH(UARTx));
  assert_param(CNF_UART_FLAG(UART_FLAG));
  
  if(UARTx->SR & UART_FLAG)
    return SET;
  else
    return RESET;
}

void UART_ClearFlag(UART_TypeDef* UARTx, uint8_t UART_FLAG)
{
  /* Check the parameters */
  assert_param(CNF_UART_ALL_PERIPH(UARTx));
  assert_param(CNF_UART_FLAG(UART_FLAG));
  
  UARTx->SR = UART_FLAG;
}

ITStatus UART_GetITStatus(UART_TypeDef* UARTx, uint8_t UART_IT) 
{
  /* Check the parameters */
  assert_param(CNF_UART_ALL_PERIPH(UARTx));
  assert_param(CNF_UART_IT(UART_IT));
  
  if(UARTx->ISR & UART_IT)
    return SET;
  else
    return RESET;
}

void UART_ClearITPendingBit(UART_TypeDef* UARTx, uint8_t UART_IT)
{
  /* Check the parameters */
  assert_param(CNF_UART_ALL_PERIPH(UARTx));
  assert_param(CNF_UART_IT(UART_IT));
  
  UARTx->ISR = UART_IT;
}







