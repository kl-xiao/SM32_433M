#include "sm32f030_sysctrl.h"


void SYSCON_MemoryRemapConfig(SYSCON_MemoryRemap_TypeDef MemoryRemap)
{
  /* Check the parameters */
  assert_param(CNF_SYSCON_MEMORY_REMAP(MemoryRemap));
  
  SYSCON->SYSMEMREMAP = MemoryRemap;
}

void SYSCON_SelectMainClkSrc(SYSCON_MainClkSource_TypeDef MainClkSource)
{
  /* Check the parameters */
  assert_param(CNF_SYSCON_MAINCLKSOURCE(MainClkSource));
  
  SYSCON->MAINCLKUEN = 1;
  SYSCON->MAINCLKSEL = MainClkSource;
  SYSCON->MAINCLKUEN = 0;
}

void SYSCON_SelectClkOutSrc(SYSCON_ClkOutSource_TypeDef ClkOutSource)
{
  /* Check the parameters */
  assert_param(CNF_SYSCON_CLKOUTSOURCE(ClkOutSource));
  
  SYSCON->CLKOUTUEN = 1;
  SYSCON->CLKOUTCLKSEL = ClkOutSource;
  SYSCON->CLKOUTUEN = 0;
}

void SYSCON_ClkOutDivConfig(uint8_t Div)
{
  SYSCON->CLKOUTDIV = Div;
}


FlagStatus SYSCON_GetResetFlag(uint8_t ResetFlag)
{
  /* Check the parameters */
  assert_param(CNF_SYSCON_RST(ResetFlag));
  
  if(SYSCON->SYSRSTSTAT & ResetFlag)
    return SET;
  else
    return RESET;
}

void SYSCON_ClearResetFlag(uint8_t ResetFlag)
{
  /* Check the parameters */
  assert_param(CNF_SYSCON_RST(ResetFlag));

  SYSCON->SYSRSTSTAT = ResetFlag;
}


void SYSCON_AHBClockDivConfig(uint8_t Div)
{
  SYSCON->SYSAHBCLKDIV = Div;
}

void SYSCON_AHBPeriphClockCmd(uint32_t AHBClock, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(CNF_SYSCON_AHBCLK(AHBClock));
  assert_param(CNF_FUNCTIONAL_STATE(NewState));
  
  if(NewState == ENABLE)
    SYSCON->SYSAHBCLKCTRL |= AHBClock;
  else
    SYSCON->SYSAHBCLKCTRL &= ~AHBClock;
}


void SYSCON_AHBPeriphResetCmd(uint32_t AHBReset, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(CNF_SYSCON_AHBRESET(AHBReset));
  assert_param(CNF_FUNCTIONAL_STATE(NewState));
  
  if(NewState == ENABLE)
  {
    SYSCON->PRESETCTRL &= ~AHBReset;  /* 对应外设进入复位状态 */
  }
  else
  {
    SYSCON->PRESETCTRL |= AHBReset;   /* 对应外设退出复位状态 */
  }
}


