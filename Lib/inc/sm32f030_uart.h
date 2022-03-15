#ifndef __SM32F030_UART_H
#define __SM32F030_UART_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "sm32f030.h"



#define CNF_UART_ALL_PERIPH(PERIPH) (((PERIPH) == UART0) || \
                                     ((PERIPH) == UART1))





/** @defgroup UART_Parity 
  * @{
  */ 
#define UART_Parity_No                      (0x00000000)
#define UART_Parity_Even                    UART_CR_PARIEN
#define UART_Parity_Odd                     (UART_CR_PARIEN | UART_CR_PARIODD) 
#define CNF_UART_PARITY(PARITY) (((PARITY) == UART_Parity_No)   || \
                                 ((PARITY) == UART_Parity_Even) || \
                                 ((PARITY) == UART_Parity_Odd))
/**
  * @}
  */ 

/** @defgroup UART_Mode 
  * @{
  */ 
#define UART_Mode_Rx                        UART_CR_RXEN
#define UART_Mode_Tx                        UART_CR_TXEN
#define CNF_UART_MODE(MODE) (((MODE) & (uint32_t)0xFF3FFFFF) == 0x00)






/** @defgroup UART_Flags 
  * @{
  */
#define UART_FLAG_TXNE                    UART_SR_TXNE
#define UART_FLAG_RXNE                    UART_SR_RXNE
#define UART_FLAG_TXF                     UART_SR_TXF
#define UART_FLAG_RXF                     UART_SR_RXF
#define UART_FLAG_TXHLF                   UART_SR_TXHLF
#define UART_FLAG_RXHLF                   UART_SR_RXHLF
#define UART_FLAG_PARIERR                 UART_SR_PARIERR
#define UART_FLAG_OVERRUN                 UART_SR_OVERRUN

#define CNF_UART_FLAG(FLAG) (1)
/**
  * @}
  */ 



/** @defgroup USART_Interrupt_definition 
  * @{
  */
#define UART_IT_TXE                       UART_ISR_TXEINT
#define UART_IT_RXNE                      UART_ISR_RXNEINT
#define UART_IT_TXF                       UART_ISR_TXFINT
#define UART_IT_RXF                       UART_ISR_RXFINT
#define UART_IT_TXHLF                     UART_ISR_TXHLFINT
#define UART_IT_RXHLF                     UART_ISR_RXHLFINT
#define UART_IT_PARIERR                   UART_ISR_PARIERRINT
#define UART_IT_OVERRUN                   UART_ISR_OVERRUNINT

#define CNF_UART_IT(IT) (1)
/**
  * @}
  */



/** @defgroup USART FIFO definition
  * @{
  */
#define UART_TX_FIFO                      (0x00000001)
#define UART_RX_FIFO                      (0x00000002)

#define CNF_UART_FIFO(FIFO) (((FIFO) & 0xFFFFFFFC) == 0x00)
  
/**
  * @}
  */



void UART_DeInit(UART_TypeDef* UARTx);
void UART_Init(UART_TypeDef* UARTx, uint32_t Baud, uint32_t Parity, uint32_t Mode);
void UART_WriteFIFO(UART_TypeDef* UARTx, uint8_t Data);
uint8_t UART_ReadFIFO(UART_TypeDef* UARTx);
void UART_ClearFIFO(UART_TypeDef* UARTx, uint32_t UART_FIFO);
void UART_Send(UART_TypeDef* UARTx, const uint8_t* txBuf, uint16_t txLen);
void UART_ITConfig(UART_TypeDef* UARTx, uint8_t UART_IT, FunctionalState NewState);
FlagStatus UART_GetFlagStatus(UART_TypeDef* UARTx, uint8_t UART_FLAG);
void UART_ClearFlag(UART_TypeDef* UARTx, uint8_t UART_FLAG);
ITStatus UART_GetITStatus(UART_TypeDef* UARTx, uint8_t UART_IT);
void UART_ClearITPendingBit(UART_TypeDef* UARTx, uint8_t UART_IT);


#ifdef __cplusplus
}
#endif

#endif /* __SM32F030_UART_H */

