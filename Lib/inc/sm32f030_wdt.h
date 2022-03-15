#ifndef __SM32F030_WDT_H
#define __SM32F030_WDT_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "sm32f030.h"



typedef enum
{
  WDT_ClockSource_IRC   = 0x0000,
  WDT_ClockSource_32KHz = 0x1000,
} WDTClockSource_TypeDef;

#define CNF_WDT_CLOCKSOURCE(CLOCKSOURCE) (((CLOCKSOURCE) == WDT_ClockSource_IRC) || ((CLOCKSOURCE) == WDT_ClockSource_32KHz)) 




typedef enum
{
  WDT_Mode_Interrupt  = 0x0002,
  WDT_Mode_ChipReset  = 0x0000,
} WDTMode_TypeDef;

#define CNF_WDT_MODE(MODE) (((MODE) == WDT_Mode_Interrupt) || ((MODE) == WDT_Mode_ChipReset))


#define CNF_WDT_CLOCKDIVSEL(DIVSEL) ((DIVSEL) < 0x20)


#define CNF_WDT_RELOAD(RELOAD) ((RELOAD) < 0x1000000)


#define CNF_WDT_WARNING_VALUE(VALUE) ((VALUE) < 0x400)


#define CNF_WDT_WINDOW_VALUE(VALUE) ((VALUE) < 0x1000000)





/** @defgroup WDT_Flags 
  * @{
  */
#define WDT_IT_OVERFLOW     WDT_MODE_WDTOF
#define WDT_IT_WARNING      WDT_MODE_WDINT

#define CNF_WDT_IT(IT) (((IT) & 0xFFFFFFF3) == 0)

/**
  * @}
  */ 






void WDT_DeInit(void);
void WDT_ClockConfig(WDTClockSource_TypeDef ClockSource, uint16_t DivSel);
void WDT_SetMode(WDTMode_TypeDef Mode);
void WDT_SetReload(uint32_t Reload);
void WDT_Cmd(FunctionalState NewState);
void WDT_Feed(void);
void WDT_SetWarningValue(uint16_t Value);
void WDT_SetWindowValue(uint32_t WindowValue);

ITStatus WDT_GetITStatus(uint8_t WDT_IT);
void WDT_ClearITPendingBit(uint8_t WDT_IT);

#ifdef __cplusplus
}
#endif

#endif /* __SM32F030_WDT_H */

