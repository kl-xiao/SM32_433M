#include "sm32f030_pwm.h"

void PWM_DeInit(void)
{
	SYSCON_AHBPeriphResetCmd(SYSCON_AHBRESET_PWM, ENABLE);
	SYSCON_AHBPeriphResetCmd(SYSCON_AHBRESET_PWM, DISABLE);
}

void PWM_SetPrescaler(PWMPrescaler_TypeDef Prescaler)
{
	uint32_t tmpreg;
	/* Check the parameters */
	assert_param(CNF_PWM_PRESCALER(Prescaler));

	tmpreg = PWM->CTRL & (~PWM_CTRL_PRSC);
	tmpreg |= (uint32_t)(Prescaler);
	PWM->CTRL = tmpreg;
}

void PWM_SetModulo(uint16_t Modulo)
{
	PWM->CMOD = Modulo;
}

void PWM_OutputPairConfig(PWMOutputPair_TypeDef OutputPair, PWMOutputMode_TypeDef OutputMode)
{
	/* Check the parameters */
	assert_param(CNF_PWM_OUTPUTPAIR(OutputPair));
	assert_param(CNF_PWM_OUTPUTMODE(OutputMode));

	if (PWM_OutputMode_Independent == OutputMode)
	{
		PWM->CNFG |= (0x01 << (uint32_t)OutputPair);
	}
	else
	{
		PWM->CNFG &= ~(0x01 << (uint32_t)OutputPair);
	}
}

void PWM_Init(PWMPrescaler_TypeDef Prescaler, uint16_t Modulo, PWMAlign_TypeDef Align)
{
	uint32_t tmpreg;
	/* Check the parameters */
	assert_param(CNF_PWM_PRESCALER(Prescaler));
	assert_param(CNF_PWM_ALIGN(Align));

	tmpreg = PWM->CTRL & (~PWM_CTRL_PRSC);
	PWM->CTRL = tmpreg | (uint32_t)(Prescaler);

	PWM->CNFG = (uint32_t)(Align);

	PWM->CMOD = Modulo;

	PWM->CTRL |= PWM_CTRL_LDOK;
}

void PWM_Cmd(FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(CNF_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
	{
		/* Enable PWM Output */
		PWM->CTRL |= (0x3F000000 | PWM_CTRL_PWMEN);
		PWM->ICCTRL = PWM_ICCTRL_PAD_EN;
		PWM->OUT = 0x3F;
		PWM->CNTRINI = 0;

		PWM->CTRL |= PWM_CTRL_LDOK;
	}
	else
	{
		/* Disable PWM_Output */
		PWM->CTRL &= (~(0x3F000000 | PWM_CTRL_PWMEN));
		PWM->ICCTRL = 0;
		PWM->OUT = 0;

		PWM->CTRL |= PWM_CTRL_LDOK;
	}
}

void PWM_SetCompare0(uint16_t Compare0)
{
	PWM->VAL0 = Compare0;
}

void PWM_SetCompare1(uint16_t Compare1)
{
	PWM->VAL1 = Compare1;
}

void PWM_SetCompare2(uint16_t Compare2)
{
	PWM->VAL2 = Compare2;
}

void PWM_SetCompare3(uint16_t Compare3)
{
	PWM->VAL3 = Compare3;
}

void PWM_SetCompare4(uint16_t Compare4)
{
	PWM->VAL4 = Compare4;
}

void PWM_SetCompare5(uint16_t Compare5)
{
	PWM->VAL5 = Compare5;
}

void PWM_SetRiseDeadZone(uint16_t nCycles)
{
	PWM->DTIM0 = nCycles;
}

void PWM_SetFallDeadZone(uint16_t nCycles)
{
	PWM->DTIM1 = nCycles;
}
