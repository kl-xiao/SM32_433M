/* Includes ------------------------------------------------------------------*/
#include "sm32f030_misc.h"

/** @addtogroup SM32F030_StdPeriph_Driver
  * @{
  */

/** @defgroup MISC 
  * @brief MISC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup MISC_Private_Functions
  * @{
  */

/**
  * @brief  Configures the SysTick clock source.
  * @param  SysTick_CLKSource: specifies the SysTick clock source.
  *          This parameter can be one of the following values:
  *            @arg SysTick_CLKSource_SystemClk_Div2: AHB clock divided by 8 selected as SysTick clock source.
  *            @arg SysTick_CLKSource_SystemClk: AHB clock selected as SysTick clock source.
  * @retval None
  */
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource)
{
  /* Check the parameters */
  assert_param(CNF_SYSTICK_CLK_SOURCE(SysTick_CLKSource));
  
  if (SysTick_CLKSource == SysTick_CLKSource_SystemClk)
  {
    SysTick->CTRL |= SysTick_CLKSource_SystemClk;
  }
  else
  {
    SysTick->CTRL &= SysTick_CLKSource_SystemClk_Div2;
  }
}


// nus <= 671088  (2^24 / 25)
void SysTick_Delay_us(uint32_t nus)
{
  uint32_t temp;
  SysTick->LOAD = nus * 25;   //SystemCoreClock 内核时钟为25Mhz
  SysTick->VAL = 0x00;
  SysTick->CTRL = (SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk);  //选择内核时钟源并开启SysTick
  do
  {
    temp = SysTick->CTRL;
  } while((temp&0x01) && !(temp&SysTick_CTRL_COUNTFLAG_Msk));
  
  SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
  SysTick->VAL =0X00;
}

// nms <= 1342  (2^24 / 12500)
void SysTick_Delay_ms(uint32_t nms)
{
  uint32_t temp;
  SysTick->LOAD = nms * 12500;   //SystemCoreClock/2   12.5Mhz
  SysTick->VAL = 0x00;
  SysTick->CTRL = SysTick_CTRL_ENABLE_Msk;  //选择SystemCoreClock/2并开启SysTick
  do
  {
    temp = SysTick->CTRL;
  } while((temp&0x01) && !(temp&SysTick_CTRL_COUNTFLAG_Msk));
  
  SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
  SysTick->VAL =0X00;
}

//Delay_ms函数 时间不超过32bit数据
//delay_ms最大只有1.3s
void Delay_ms(uint32_t ms)
{
    uint32_t tmp = ms;
    if(tmp > 1000)
    {
        ms = (973 * ms) >> 10;    //973/1025   时间补偿，调用函数导致比实际时间长
        while (ms--)
        {
            delay_ms(1);
        }        
    }
    else
        delay_ms(ms);
}

void delay_ns(uint16_t us)
{
    while(us--)
      NOP_1();    //
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

