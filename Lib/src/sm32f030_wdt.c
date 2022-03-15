#include "sm32f030_wdt.h"


void WDT_DeInit(void)
{
  SYSCON_AHBPeriphClockCmd(SYSCON_AHBCLK_WDT, DISABLE);
  SYSCON_AHBPeriphClockCmd(SYSCON_AHBCLK_WDT, ENABLE);
}

//配置看门狗计数器的时钟
//WDT_CLK = Fsource / (4 * DivSel)
void WDT_ClockConfig(WDTClockSource_TypeDef ClockSource, uint16_t DivSel)
{
  uint32_t tmpreg;
  /* Check the parameters */
  assert_param(CNF_WDT_CLOCKSOURCE(ClockSource));
  assert_param(CNF_WDT_CLOCKDIVSEL(DivSel));
  
  /* Clear DIVSEL and WDTCLKSOURCE bits */
  tmpreg = SYSCON->WDTOSCCTRL;
  tmpreg &= (0xFFFFEFE0);
  /* Configure WDTCLKSOURCE and DIVSEL */
  tmpreg |= ClockSource;
  tmpreg |= (DivSel & SYSCON_WDTOSCCTRL_DIVSEL);
  
  SYSCON->WDTOSCCTRL = tmpreg;
}

void WDT_SetMode(WDTMode_TypeDef Mode)
{
  uint32_t tmpreg;
  /* Check the parameters */
  assert_param(CNF_WDT_MODE(Mode));
  
  tmpreg = WDT->MODE;
  tmpreg &= ~(WDT_MODE_WDRESET);
  WDT->MODE = tmpreg | Mode;
}

void WDT_SetReload(uint32_t Reload)
{
  /* Check the parameters */
  assert_param(CNF_WDT_RELOAD(Reload));
  
  WDT->TC = Reload;
}

void WDT_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(CNF_FUNCTIONAL_STATE(NewState));
  
  if(NewState != DISABLE)
  {
    /* Enable the WDT peripheral */
    WDT->MODE |= WDT_MODE_WDEN;
  }
  else
  {
    /* Disable the WDT peripheral */
    WDT->MODE &= (~WDT_MODE_WDEN);
  }
}

void WDT_Feed(void)
{
  WDT->FEED = WDT_FEED_CMD1;
  WDT->FEED = WDT_FEED_CMD2;
}

void WDT_SetWarningValue(uint16_t Value)
{
  /* Check the parameters */
  assert_param(CNF_WDT_WARNING_VALUE(Value));
  
  WDT->WARNINT = Value;
}

void WDT_SetWindowValue(uint32_t WindowValue)
{
  /* Check the parameters */
  assert_param(CNF_WDT_WINDOW_VALUE(WindowValue));
  
  WDT->WINDOW = WindowValue;
}


ITStatus WDT_GetITStatus(uint8_t WDT_IT)
{
  /* Check the parameters */
  assert_param(CNF_WDT_IT(WDT_IT));
  
  if(WDT->MODE & WDT_IT)
    return SET;
  else
    return RESET;
}

void WDT_ClearITPendingBit(uint8_t WDT_IT)
{
  uint32_t tmpreg;
  /* Check the parameters */
  assert_param(CNF_WDT_IT(WDT_IT));
  
  tmpreg = WDT->MODE;
  tmpreg &= 0xFFFFFFF3;
  WDT->MODE = tmpreg | (WDT_IT ^ WDT_IT_OVERFLOW);
}






