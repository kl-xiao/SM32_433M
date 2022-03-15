#ifndef __SM32F030_SYSCTRL_H
#define __SM32F030_SYSCTRL_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "sm32f030.h"





typedef enum
{
  SYSCON_MemoryRemap_Bootloader   = SYSCON_SYSMEMREMAP_BOOTLOADER,    /* = 0x00, */
  SYSCON_MemoryRemap_SRAM         = SYSCON_SYSMEMREMAP_SRAM,          /* = 0x01, */
  SYSCON_MemoryRemap_Flash        = SYSCON_SYSMEMREMAP_FLASH          /* = 0x02 */
} SYSCON_MemoryRemap_TypeDef;

#define CNF_SYSCON_MEMORY_REMAP(REMAP) (((REMAP) == SYSCON_MemoryRemap_Bootloader)  || \
                                        ((REMAP) == SYSCON_MemoryRemap_SRAM)          || \
                                        ((REMAP) == SYSCON_MemoryRemap_Flash))


typedef enum
{
  SYSCON_MainClkSource_IRC = SYSCON_MAINCLKSEL_IRC, /* = 0x00, */
  SYSCON_MainClkSource_WDT = SYSCON_MAINCLKSEL_WDT  /* = 0x02 */
} SYSCON_MainClkSource_TypeDef;

#define CNF_SYSCON_MAINCLKSOURCE(SOURCE) (((SOURCE) == SYSCON_MainClkSource_IRC) || \
                                          ((SOURCE) == SYSCON_MainClkSource_WDT))


typedef enum
{
  SYSCON_ClkOutSource_IRC     = SYSCON_CLKOUTCLKSEL_IRC,      /* = 0x00, */
  SYSCON_ClkOutSource_SYSCLK  = SYSCON_CLKOUTCLKSEL_SYSCLK,   /* = 0x01, */
  SYSCON_ClkOutSource_WDT     = SYSCON_CLKOUTCLKSEL_WDT,      /* = 0x02, */
  SYSCON_ClkOutSource_MAINCLK = SYSCON_CLKOUTCLKSEL_MAINCLK,  /* = 0x03, */
  SYSCON_ClkOutSource_RTCOSC  = SYSCON_CLKOUTCLKSEL_RTCOSC    /* = 0x04, */
} SYSCON_ClkOutSource_TypeDef;

#define CNF_SYSCON_CLKOUTSOURCE(SOURCE) (((SOURCE) == SYSCON_ClkOutSource_IRC)     || \
                                         ((SOURCE) == SYSCON_ClkOutSource_SYSCLK)  || \
                                         ((SOURCE) == SYSCON_ClkOutSource_WDT)     || \
                                         ((SOURCE) == SYSCON_ClkOutSource_MAINCLK) || \
                                         ((SOURCE) == SYSCON_ClkOutSource_RTCOSC))





#define SYSCON_AHBRESET_SPI     SYSCON_PRESETCTRL_SPI_RST_N
#define SYSCON_AHBRESET_I2C     SYSCON_PRESETCTRL_I2C_RST_N
#define SYSCON_AHBRESET_UART0   SYSCON_PRESETCTRL_UART0_RST_N
#define SYSCON_AHBRESET_UART1   SYSCON_PRESETCTRL_UART1_RST_N
#define SYSCON_AHBRESET_TIM0    SYSCON_PRESETCTRL_TIM0_RST_N
#define SYSCON_AHBRESET_TIM1    SYSCON_PRESETCTRL_TIM1_RST_N
#define SYSCON_AHBRESET_TIM2    SYSCON_PRESETCTRL_TIM2_RST_N
#define SYSCON_AHBRESET_TIM3    SYSCON_PRESETCTRL_TIM3_RST_N
#define SYSCON_AHBRESET_PWM     SYSCON_PRESETCTRL_PWM_RST_N
#define SYSCON_AHBRESET_CRC     SYSCON_PRESETCTRL_CRC_RST_N
#define SYSCON_AHBRESET_ADC     SYSCON_PRESETCTRL_ADC_RST_N

#define CNF_SYSCON_AHBRESET(AHBRESET)   (1)
#define CNF_SYSCON_ALL_AHBRESET(AHBRESET) (((AHBRESET) == SYSCON_AHBRESET_SPI)    || \
                                           ((AHBRESET) == SYSCON_AHBRESET_I2C)    || \
                                           ((AHBRESET) == SYSCON_AHBRESET_UART0)  || \
                                           ((AHBRESET) == SYSCON_AHBRESET_UART1)  || \
                                           ((AHBRESET) == SYSCON_AHBRESET_TIM0)   || \
                                           ((AHBRESET) == SYSCON_AHBRESET_TIM1)   || \
                                           ((AHBRESET) == SYSCON_AHBRESET_TIM2)   || \
                                           ((AHBRESET) == SYSCON_AHBRESET_TIM3)   || \
                                           ((AHBRESET) == SYSCON_AHBRESET_PWM)    || \
                                           ((AHBRESET) == SYSCON_AHBRESET_CRC)    || \
                                           ((AHBRESET) == SYSCON_AHBRESET_ADC))




#define SYSCON_AHBCLK_SYS       SYSCON_SYSAHBCLKCTRL_SYSEN
#define SYSCON_AHBCLK_RAM       SYSCON_SYSAHBCLKCTRL_RAMEN
#define SYSCON_AHBCLK_I2C       SYSCON_SYSAHBCLKCTRL_I2CEN
#define SYSCON_AHBCLK_CRC       SYSCON_SYSAHBCLKCTRL_CRCEN
#define SYSCON_AHBCLK_TIM0      SYSCON_SYSAHBCLKCTRL_TIM0EN
#define SYSCON_AHBCLK_TIM1      SYSCON_SYSAHBCLKCTRL_TIM1EN
#define SYSCON_AHBCLK_TIM2      SYSCON_SYSAHBCLKCTRL_TIM2EN
#define SYSCON_AHBCLK_TIM3      SYSCON_SYSAHBCLKCTRL_TIM3EN
#define SYSCON_AHBCLK_SPI       SYSCON_SYSAHBCLKCTRL_SPIEN
#define SYSCON_AHBCLK_UART0     SYSCON_SYSAHBCLKCTRL_UART0EN
#define SYSCON_AHBCLK_UART1     SYSCON_SYSAHBCLKCTRL_UART1EN
#define SYSCON_AHBCLK_ADC       SYSCON_SYSAHBCLKCTRL_ADCEN
#define SYSCON_AHBCLK_WDT       SYSCON_SYSAHBCLKCTRL_WDTEN
#define SYSCON_AHBCLK_IOCON     SYSCON_SYSAHBCLKCTRL_IOCONEN
#define SYSCON_AHBCLK_PWM       SYSCON_SYSAHBCLKCTRL_PWMEN
#define SYSCON_AHBCLK_RTC       SYSCON_SYSAHBCLKCTRL_RTCEN
#define SYSCON_AHBCLK_GPIOA     SYSCON_SYSAHBCLKCTRL_GPIOAEN
#define SYSCON_AHBCLK_GPIOB     SYSCON_SYSAHBCLKCTRL_GPIOBEN
#define SYSCON_AHBCLK_GPIOC     SYSCON_SYSAHBCLKCTRL_GPIOCEN

#define CNF_SYSCON_AHBCLK(AHBCLK)   (1)
#define CNF_SYSCON_ALL_AHBCLK(AHBCLK) (((AHBCLK) == SYSCON_AHBCLK_SYS)     || \
                                       ((AHBCLK) == SYSCON_AHBCLK_RAM)     || \
                                       ((AHBCLK) == SYSCON_AHBCLK_I2C)     || \
                                       ((AHBCLK) == SYSCON_AHBCLK_CRC)     || \
                                       ((AHBCLK) == SYSCON_AHBCLK_TIM0)    || \
                                       ((AHBCLK) == SYSCON_AHBCLK_TIM1)    || \
                                       ((AHBCLK) == SYSCON_AHBCLK_TIM2)    || \
                                       ((AHBCLK) == SYSCON_AHBCLK_TIM3)    || \
                                       ((AHBCLK) == SYSCON_AHBCLK_SPI)     || \
                                       ((AHBCLK) == SYSCON_AHBCLK_UART0)   || \
                                       ((AHBCLK) == SYSCON_AHBCLK_UART1)   || \
                                       ((AHBCLK) == SYSCON_AHBCLK_ADC)     || \
                                       ((AHBCLK) == SYSCON_AHBCLK_WDT)     || \
                                       ((AHBCLK) == SYSCON_AHBCLK_IOCON)   || \
                                       ((AHBCLK) == SYSCON_AHBCLK_PWM)     || \
                                       ((AHBCLK) == SYSCON_AHBCLK_RTC)     || \
                                       ((AHBCLK) == SYSCON_AHBCLK_GPIOA)   || \
                                       ((AHBCLK) == SYSCON_AHBCLK_GPIOB)   || \
                                       ((AHBCLK) == SYSCON_AHBCLK_GPIOC))



#define SYSCON_RST_POR          (uint8_t)SYSCON_SYSRSTSTAT_POR
#define SYSCON_RST_EXTRST       (uint8_t)SYSCON_SYSRSTSTAT_EXTRST
#define SYSCON_RST_WDT          (uint8_t)SYSCON_SYSRSTSTAT_WDT
#define SYSCON_RST_BOD          (uint8_t)SYSCON_SYSRSTSTAT_BOD
#define SYSCON_RST_SYSRST       (uint8_t)SYSCON_SYSRSTSTAT_SYSRST

#define CNF_SYSCON_RST(RST)   (1)



void SYSCON_MemoryRemapConfig(SYSCON_MemoryRemap_TypeDef SYSCON_MemoryRemap);
void SYSCON_SelectMainClkSrc(SYSCON_MainClkSource_TypeDef MainClkSource);
void SYSCON_SelectClkOutSrc(SYSCON_ClkOutSource_TypeDef ClkOutSource);
void SYSCON_ClkOutDivConfig(uint8_t Div);
FlagStatus SYSCON_GetResetFlag(uint8_t ResetFlag);
void SYSCON_ClearResetFlag(uint8_t ResetFlag);
void SYSCON_AHBClockDivConfig(uint8_t Div);
void SYSCON_AHBPeriphClockCmd(uint32_t AHBClock, FunctionalState NewState);
void SYSCON_AHBPeriphResetCmd(uint32_t AHBReset, FunctionalState NewState);









#ifdef __cplusplus
}
#endif

#endif /* __SM32F030_SYSCTRL_H */
