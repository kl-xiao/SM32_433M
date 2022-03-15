#ifndef __SM32F030_PWM_H
#define __SM32F030_PWM_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "sm32f030.h"



typedef enum
{
  PWM_Prescaler_Div1 = 0x00,
  PWM_Prescaler_Div2 = 0x20,
  PWM_Prescaler_Div4 = 0x40,
  PWM_Prescaler_Div8 = 0x60,
} PWMPrescaler_TypeDef;
#define CNF_PWM_PRESCALER(PRESCALER) (((PRESCALER) == PWM_Prescaler_Div1) || \
                                      ((PRESCALER) == PWM_Prescaler_Div2) || \
                                      ((PRESCALER) == PWM_Prescaler_Div4) || \
                                      ((PRESCALER) == PWM_Prescaler_Div8))

typedef enum
{
  PWM_Align_Center  = 0x00,
  PWM_Align_Edge    = PWM_CNFG_EDG,
} PWMAlign_TypeDef;
#define CNF_PWM_ALIGN(ALIGN) (((ALIGN) == PWM_Align_Center) || \
                              ((ALIGN) == PWM_Align_Edge))

typedef enum
{
  PWM_OutputPair01 = 1,
  PWM_OutputPair23 = 2,
  PWM_OutputPair45 = 3,
} PWMOutputPair_TypeDef;
#define CNF_PWM_OUTPUTPAIR(PAIR) (((PAIR) == PWM_OutputPair01) || \
                                  ((PAIR) == PWM_OutputPair23) || \
                                  ((PAIR) == PWM_OutputPair45))

typedef enum
{
  PWM_OutputMode_Independent = 0,
  PWM_OutputMode_Complementary = 1,
} PWMOutputMode_TypeDef;
#define CNF_PWM_OUTPUTMODE(MODE) (((MODE) == PWM_OutputMode_Independent) || \
                                  ((MODE) == PWM_OutputMode_Complementary))





#define PWM_Channel_0       0x01
#define PWM_Channel_1       0x02
#define PWM_Channel_2       0x04
#define PWM_Channel_3       0x08
#define PWM_Channel_4       0x10
#define PWM_Channel_5       0x20
#define CNF_PWM_CHANNEL(CHANNEL) (((CHANNEL) & 0xC0) == 0x00)

void PWM_DeInit(void);
void PWM_SetPrescaler(PWMPrescaler_TypeDef Prescaler);
void PWM_SetModulo(uint16_t Modulo);
void PWM_OutputPairConfig(PWMOutputPair_TypeDef OutputPair, PWMOutputMode_TypeDef OutputMode);
void PWM_Init(PWMPrescaler_TypeDef Prescaler, uint16_t Modulo, PWMAlign_TypeDef Align);
void PWM_SetCompare0(uint16_t Compare0);
void PWM_SetCompare1(uint16_t Compare1);
void PWM_SetCompare2(uint16_t Compare2);
void PWM_SetCompare3(uint16_t Compare3);
void PWM_SetCompare4(uint16_t Compare4);
void PWM_SetCompare5(uint16_t Compare5);
void PWM_SetRiseDeadZone(uint16_t nCycles);
void PWM_SetFallDeadZone(uint16_t nCycles);
void PWM_Cmd(FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif /* __SM32F030_PWM_H */

