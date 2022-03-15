#include "wdt.h"

void WDT_Init(void)
{
    WDT_DeInit();
	WDT_ClockConfig(WDT_ClockSource_32KHz, 1);		//WDT_CLK = 32K / 4 = 8K

	WDT_SetMode(WDT_Mode_ChipReset);
	WDT_SetReload(4000);   // 1秒
	WDT_Feed();
    WDT_Cmd(ENABLE);
}