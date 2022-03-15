/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SM32F030_MISC_H
#define __SM32F030_MISC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "sm32f030.h"

/** @addtogroup SM32F030_StdPeriph_Driver
  * @{
  */

/** @addtogroup MISC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**  
  *
@verbatim   

@endverbatim
*/

/* Exported constants --------------------------------------------------------*/

/** @defgroup MISC_Exported_Constants
  * @{
  */



/** @defgroup MISC_SysTick_clock_source 
  * @{
  */

#define SysTick_CLKSource_SystemClk_Div2    ((uint32_t)0xFFFFFFFB)
#define SysTick_CLKSource_SystemClk         ((uint32_t)0x00000004)
#define CNF_SYSTICK_CLK_SOURCE(SOURCE) (((SOURCE) == SysTick_CLKSource_SystemClk) || \
                                        ((SOURCE) == SysTick_CLKSource_SystemClk_Div2))
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 

#define delay_us(x) SysTick_Delay_us(x)
#define delay_ms(x) SysTick_Delay_ms(x)

//#define  _nop_()  __asm volatile("nop")

#define  NOP(N)    do{ NOP_##N(); }while(0)

#define  NOP_0()
#define  NOP_1()   asm("nop")
#define  NOP_2()   NOP_1();asm("nop")
#define  NOP_3()   NOP_2();asm("nop")
#define  NOP_4()   NOP_3();asm("nop")
#define  NOP_5()   NOP_4();asm("nop")
#define  NOP_6()   NOP_5();asm("nop")
#define  NOP_7()   NOP_6();asm("nop")
#define  NOP_8()   NOP_7();asm("nop")
#define  NOP_9()   NOP_8();asm("nop")
#define  NOP_10()  NOP_9();asm("nop")
#define  NOP_11()  NOP_10();asm("nop")
#define  NOP_12()  NOP_11();asm("nop")
#define  NOP_13()  NOP_12();asm("nop")
#define  NOP_14()  NOP_13();asm("nop")
#define  NOP_15()  NOP_14();asm("nop")
#define  NOP_16()  NOP_15();asm("nop")
#define  NOP_17()  NOP_16();asm("nop")
#define  NOP_18()  NOP_17();asm("nop")
#define  NOP_19()  NOP_18();asm("nop")
#define  NOP_20()  NOP_19();asm("nop")
#define  NOP_21()  NOP_20();asm("nop")
#define  NOP_22()  NOP_21();asm("nop")
#define  NOP_23()  NOP_22();asm("nop")
#define  NOP_24()  NOP_23();asm("nop")
#define  NOP_25()  NOP_24();asm("nop")
#define  NOP_26()  NOP_25();asm("nop")
#define  NOP_27()  NOP_26();asm("nop")
#define  NOP_28()  NOP_27();asm("nop")
#define  NOP_29()  NOP_28();asm("nop")
#define  NOP_30()  NOP_29();asm("nop")


void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource);

void SysTick_Delay_us(uint32_t nus);
void SysTick_Delay_ms(uint32_t nms);
void Delay_ms(uint32_t ms);
void delay_ns(uint16_t us);

#ifdef __cplusplus
}
#endif

#endif /* __SM32F030_MISC_H */

/**
  * @}
  */

/**
  * @}
  */

