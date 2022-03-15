#ifndef __SM32F030_GPIO_H
#define __SM32F030_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "sm32f030.h"


#define CNF_GPIO_ALL_PORT(PORT)   (((PORT) == GPIOA) || \
                                   ((PORT) == GPIOB) || \
                                   ((PORT) == GPIOC))
                                  
#define CNF_GPIO_IOCFG_FUNC(FUNC) ((FUNC) <= 0x07)



#define GPIO_Pin_0                 ((uint16_t)0x0001)  /*!< Pin 0     */
#define GPIO_Pin_1                 ((uint16_t)0x0002)  /*!< Pin 1     */
#define GPIO_Pin_2                 ((uint16_t)0x0004)  /*!< Pin 2     */
#define GPIO_Pin_3                 ((uint16_t)0x0008)  /*!< Pin 3     */
#define GPIO_Pin_4                 ((uint16_t)0x0010)  /*!< Pin 4     */
#define GPIO_Pin_5                 ((uint16_t)0x0020)  /*!< Pin 5     */
#define GPIO_Pin_6                 ((uint16_t)0x0040)  /*!< Pin 6     */
#define GPIO_Pin_7                 ((uint16_t)0x0080)  /*!< Pin 7     */
#define GPIO_Pin_8                 ((uint16_t)0x0100)  /*!< Pin 8     */
#define GPIO_Pin_9                 ((uint16_t)0x0200)  /*!< Pin 9     */
#define GPIO_Pin_10                ((uint16_t)0x0400)  /*!< Pin 10    */
#define GPIO_Pin_11                ((uint16_t)0x0800)  /*!< Pin 11    */
#define GPIO_Pin_12                ((uint16_t)0x1000)  /*!< Pin 12    */
#define GPIO_Pin_13                ((uint16_t)0x2000)  /*!< Pin 13    */
#define GPIO_Pin_14                ((uint16_t)0x4000)  /*!< Pin 14    */
#define GPIO_Pin_15                ((uint16_t)0x8000)  /*!< Pin 15    */
#define GPIO_Pin_All               ((uint16_t)0xFFFF)  /*!< All pins  */

#define CNF_GPIO_PIN(PIN) ((PIN) <= 0xFFFF)



typedef enum
{
  PA0  = (((GPIOA_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_0  << 12) | ((uint32_t)&IOCFG->PA0  - IOCFG_BASE)),
  PA1  = (((GPIOA_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_1  << 12) | ((uint32_t)&IOCFG->PA1  - IOCFG_BASE)),
  PA2  = (((GPIOA_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_2  << 12) | ((uint32_t)&IOCFG->PA2  - IOCFG_BASE)),
  PA3  = (((GPIOA_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_3  << 12) | ((uint32_t)&IOCFG->PA3  - IOCFG_BASE)),
  PA4  = (((GPIOA_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_4  << 12) | ((uint32_t)&IOCFG->PA4  - IOCFG_BASE)),
  PA5  = (((GPIOA_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_5  << 12) | ((uint32_t)&IOCFG->PA5  - IOCFG_BASE)),
  PA6  = (((GPIOA_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_6  << 12) | ((uint32_t)&IOCFG->PA6  - IOCFG_BASE)),
  PA7  = (((GPIOA_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_7  << 12) | ((uint32_t)&IOCFG->PA7  - IOCFG_BASE)),
  PA8  = (((GPIOA_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_8  << 12) | ((uint32_t)&IOCFG->PA8  - IOCFG_BASE)),
  PA9  = (((GPIOA_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_9  << 12) | ((uint32_t)&IOCFG->PA9  - IOCFG_BASE)),
  PA10 = (((GPIOA_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_10 << 12) | ((uint32_t)&IOCFG->PA10 - IOCFG_BASE)),
  PA11 = (((GPIOA_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_11 << 12) | ((uint32_t)&IOCFG->PA11 - IOCFG_BASE)),
  PA12 = (((GPIOA_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_12 << 12) | ((uint32_t)&IOCFG->PA12 - IOCFG_BASE)),
  PA13 = (((GPIOA_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_13 << 12) | ((uint32_t)&IOCFG->PA13 - IOCFG_BASE)),
  PA14 = (((GPIOA_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_14 << 12) | ((uint32_t)&IOCFG->PA14 - IOCFG_BASE)),
  PA15 = (((GPIOA_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_15 << 12) | ((uint32_t)&IOCFG->PA15 - IOCFG_BASE)),
  PB0  = (((GPIOB_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_0  << 12) | ((uint32_t)&IOCFG->PB0  - IOCFG_BASE)),
  PB1  = (((GPIOB_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_1  << 12) | ((uint32_t)&IOCFG->PB1  - IOCFG_BASE)),
  PB2  = (((GPIOB_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_2  << 12) | ((uint32_t)&IOCFG->PB2  - IOCFG_BASE)),
  PB3  = (((GPIOB_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_3  << 12) | ((uint32_t)&IOCFG->PB3  - IOCFG_BASE)),
  PB4  = (((GPIOB_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_4  << 12) | ((uint32_t)&IOCFG->PB4  - IOCFG_BASE)),
  PB5  = (((GPIOB_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_5  << 12) | ((uint32_t)&IOCFG->PB5  - IOCFG_BASE)),
  PB6  = (((GPIOB_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_6  << 12) | ((uint32_t)&IOCFG->PB6  - IOCFG_BASE)),
  PB7  = (((GPIOB_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_7  << 12) | ((uint32_t)&IOCFG->PB7  - IOCFG_BASE)),
  PB8  = (((GPIOB_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_8  << 12) | ((uint32_t)&IOCFG->PB8  - IOCFG_BASE)),
  PB9  = (((GPIOB_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_9  << 12) | ((uint32_t)&IOCFG->PB9  - IOCFG_BASE)),
  PB10 = (((GPIOB_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_10 << 12) | ((uint32_t)&IOCFG->PB10 - IOCFG_BASE)),
  PB11 = (((GPIOB_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_11 << 12) | ((uint32_t)&IOCFG->PB11 - IOCFG_BASE)),
  PB12 = (((GPIOB_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_12 << 12) | ((uint32_t)&IOCFG->PB12 - IOCFG_BASE)),
  PB13 = (((GPIOB_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_13 << 12) | ((uint32_t)&IOCFG->PB13 - IOCFG_BASE)),
  PB14 = (((GPIOB_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_14 << 12) | ((uint32_t)&IOCFG->PB14 - IOCFG_BASE)),
  PB15 = (((GPIOB_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_15 << 12) | ((uint32_t)&IOCFG->PB15 - IOCFG_BASE)),
#if !defined(SM32F030x8)
  PC0  = (((GPIOC_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_0  << 12) | ((uint32_t)&IOCFG->PC0  - IOCFG_BASE)),
  PC1  = (((GPIOC_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_1  << 12) | ((uint32_t)&IOCFG->PC1  - IOCFG_BASE)),
  PC2  = (((GPIOC_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_2  << 12) | ((uint32_t)&IOCFG->PC2  - IOCFG_BASE)),
  PC3  = (((GPIOC_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_3  << 12) | ((uint32_t)&IOCFG->PC3  - IOCFG_BASE)),
  PC4  = (((GPIOC_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_4  << 12) | ((uint32_t)&IOCFG->PC4  - IOCFG_BASE)),
  PC5  = (((GPIOC_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_5  << 12) | ((uint32_t)&IOCFG->PC5  - IOCFG_BASE)),
  PC6  = (((GPIOC_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_6  << 12) | ((uint32_t)&IOCFG->PC6  - IOCFG_BASE)),
#endif
  PC7  = (((GPIOC_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_7  << 12) | ((uint32_t)&IOCFG->PC7  - IOCFG_BASE)),
  PC8  = (((GPIOC_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_8  << 12) | ((uint32_t)&IOCFG->PC8  - IOCFG_BASE)),
  PC9  = (((GPIOC_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_9  << 12) | ((uint32_t)&IOCFG->PC9  - IOCFG_BASE)),
  PC10 = (((GPIOC_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_10 << 12) | ((uint32_t)&IOCFG->PC10 - IOCFG_BASE)),
  PC11 = (((GPIOC_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_11 << 12) | ((uint32_t)&IOCFG->PC11 - IOCFG_BASE)),
  PC12 = (((GPIOC_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_12 << 12) | ((uint32_t)&IOCFG->PC12 - IOCFG_BASE)),
  PC13 = (((GPIOC_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_13 << 12) | ((uint32_t)&IOCFG->PC13 - IOCFG_BASE)),
  PC14 = (((GPIOC_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_14 << 12) | ((uint32_t)&IOCFG->PC14 - IOCFG_BASE)),
  PC15 = (((GPIOC_BASE&0x00030000) >> 8) | ((uint32_t)GPIO_Pin_15 << 12) | ((uint32_t)&IOCFG->PC15 - IOCFG_BASE))
}GPIOPortPin_TypeDef;

#if !defined(SM32F030x8)
#define CNF_GPIO_ALL_PORT_PINS(PORT_PIN) (((PORT_PIN) == PA0 ) || \
                                          ((PORT_PIN) == PA1 ) || \
                                          ((PORT_PIN) == PA2 ) || \
                                          ((PORT_PIN) == PA3 ) || \
                                          ((PORT_PIN) == PA4 ) || \
                                          ((PORT_PIN) == PA5 ) || \
                                          ((PORT_PIN) == PA6 ) || \
                                          ((PORT_PIN) == PA7 ) || \
                                          ((PORT_PIN) == PA8 ) || \
                                          ((PORT_PIN) == PA9 ) || \
                                          ((PORT_PIN) == PA10) || \
                                          ((PORT_PIN) == PA11) || \
                                          ((PORT_PIN) == PA12) || \
                                          ((PORT_PIN) == PA13) || \
                                          ((PORT_PIN) == PA14) || \
                                          ((PORT_PIN) == PA15) || \
                                          ((PORT_PIN) == PB0 ) || \
                                          ((PORT_PIN) == PB1 ) || \
                                          ((PORT_PIN) == PB2 ) || \
                                          ((PORT_PIN) == PB3 ) || \
                                          ((PORT_PIN) == PB4 ) || \
                                          ((PORT_PIN) == PB5 ) || \
                                          ((PORT_PIN) == PB6 ) || \
                                          ((PORT_PIN) == PB7 ) || \
                                          ((PORT_PIN) == PB8 ) || \
                                          ((PORT_PIN) == PB9 ) || \
                                          ((PORT_PIN) == PB10) || \
                                          ((PORT_PIN) == PB11) || \
                                          ((PORT_PIN) == PB12) || \
                                          ((PORT_PIN) == PB13) || \
                                          ((PORT_PIN) == PB14) || \
                                          ((PORT_PIN) == PB15) || \
                                          ((PORT_PIN) == PC0 ) || \
                                          ((PORT_PIN) == PC1 ) || \
                                          ((PORT_PIN) == PC2 ) || \
                                          ((PORT_PIN) == PC3 ) || \
                                          ((PORT_PIN) == PC4 ) || \
                                          ((PORT_PIN) == PC5 ) || \
                                          ((PORT_PIN) == PC6 ) || \
                                          ((PORT_PIN) == PC7 ) || \
                                          ((PORT_PIN) == PC8 ) || \
                                          ((PORT_PIN) == PC9 ) || \
                                          ((PORT_PIN) == PC10) || \
                                          ((PORT_PIN) == PC11) || \
                                          ((PORT_PIN) == PC12) || \
                                          ((PORT_PIN) == PC13) || \
                                          ((PORT_PIN) == PC14) || \
                                          ((PORT_PIN) == PC15))
#else /* !defined(SM32F030x8) */
#define CNF_GPIO_ALL_PORT_PINS(PORT_PIN) (((PORT_PIN) == PA0 ) || \
                                          ((PORT_PIN) == PA1 ) || \
                                          ((PORT_PIN) == PA2 ) || \
                                          ((PORT_PIN) == PA3 ) || \
                                          ((PORT_PIN) == PA4 ) || \
                                          ((PORT_PIN) == PA5 ) || \
                                          ((PORT_PIN) == PA6 ) || \
                                          ((PORT_PIN) == PA7 ) || \
                                          ((PORT_PIN) == PA8 ) || \
                                          ((PORT_PIN) == PA9 ) || \
                                          ((PORT_PIN) == PA10) || \
                                          ((PORT_PIN) == PA11) || \
                                          ((PORT_PIN) == PA12) || \
                                          ((PORT_PIN) == PA13) || \
                                          ((PORT_PIN) == PA14) || \
                                          ((PORT_PIN) == PA15) || \
                                          ((PORT_PIN) == PB0 ) || \
                                          ((PORT_PIN) == PB1 ) || \
                                          ((PORT_PIN) == PB2 ) || \
                                          ((PORT_PIN) == PB3 ) || \
                                          ((PORT_PIN) == PB4 ) || \
                                          ((PORT_PIN) == PB5 ) || \
                                          ((PORT_PIN) == PB6 ) || \
                                          ((PORT_PIN) == PB7 ) || \
                                          ((PORT_PIN) == PB8 ) || \
                                          ((PORT_PIN) == PB9 ) || \
                                          ((PORT_PIN) == PB10) || \
                                          ((PORT_PIN) == PB11) || \
                                          ((PORT_PIN) == PB12) || \
                                          ((PORT_PIN) == PB13) || \
                                          ((PORT_PIN) == PB14) || \
                                          ((PORT_PIN) == PB15) || \
                                          ((PORT_PIN) == PC7 ) || \
                                          ((PORT_PIN) == PC8 ) || \
                                          ((PORT_PIN) == PC9 ) || \
                                          ((PORT_PIN) == PC10) || \
                                          ((PORT_PIN) == PC11) || \
                                          ((PORT_PIN) == PC12) || \
                                          ((PORT_PIN) == PC13) || \
                                          ((PORT_PIN) == PC14) || \
                                          ((PORT_PIN) == PC15))
#endif /* !defined(SM32F030x8) */






typedef enum
{
  GPIO_Mode_IN   = 0x00, /*!< GPIO Input Mode              */
  GPIO_Mode_OUT  = 0x01, /*!< GPIO Output Mode             */
} GPIOMode_TypeDef;

#define CNF_GPIO_MODE(MODE) (((MODE) == GPIO_Mode_IN) || ((MODE) == GPIO_Mode_OUT))



typedef enum
{
  GPIO_Interrupt_Low            = 0x00, /*!< GPIO Interrupt Low Active     */
  GPIO_Interrupt_High           = 0x01, /*!< GPIO Interrupt High Active     */
  GPIO_Interrupt_Rising         = 0x02, /*!< GPIO Interrupt Rising Active     */
  GPIO_Interrupt_Falling        = 0x03, /*!< GPIO Interrupt Falling Active     */
  GPIO_Interrupt_Rising_Falling = 0x04, /*!< GPIO Interrupt Rising and Falling Active     */
} GPIOInterrupt_TypeDef;
#define CNF_GPIO_INTERRUPT(INT) (((INT) == GPIO_Interrupt_Low)            || \
                                 ((INT) == GPIO_Interrupt_High)           || \
                                 ((INT) == GPIO_Interrupt_Rising)         || \
                                 ((INT) == GPIO_Interrupt_Falling)        || \
                                 ((INT) == GPIO_Interrupt_Rising_Falling))


void GPIO_Init(GPIOPortPin_TypeDef PortPin, GPIOMode_TypeDef Mode, uint32_t IoConfig);
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t Value);
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_ClearBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_InvertBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_SetMask(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_GetMask(GPIO_TypeDef* GPIOx);
void GPIO_SetMode(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef Mode);
uint16_t GPIO_GetMode(GPIO_TypeDef* GPIOx);

void GPIO_ITConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOInterrupt_TypeDef GPIO_Int);
void GPIO_ITCmd(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, FunctionalState NewState);
ITStatus GPIO_GetRawITStatus(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
ITStatus GPIO_GetITStatus(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_ClearITPendingBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#ifdef __cplusplus
}
#endif

#endif /* __SM32F030_GPIO_H */

