/**
  ******************************************************************************
  * @file      startup_sm32f030x8.s
  * @author    MCD Application Team
  * @brief     SM32F030x8 devices vector table for GCC toolchain.
  *            This module performs:
  *                - Set the initial SP
  *                - Set the initial PC == Reset_Handler,
  *                - Set the vector table entries with the exceptions ISR address
  *                - Branches to main in the C library (which eventually
  *                  calls main()).
  *            After Reset the Cortex-M0 processor is in Thread mode,
  *            priority is Privileged, and the Stack is set to Main.
  ******************************************************************************
  * 
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of smicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

  .syntax unified
  .cpu cortex-m0
  .fpu softvfp
  .thumb

.global g_pfnVectors
.global Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word _sidata
/* start address for the .data section. defined in linker script */
.word _sdata
/* end address for the .data section. defined in linker script */
.word _edata
/* start address for the .bss section. defined in linker script */
.word _sbss
/* end address for the .bss section. defined in linker script */
.word _ebss

  .section .text.Reset_Handler
  .weak Reset_Handler
  .type Reset_Handler, %function
Reset_Handler:
  ldr   r0, =_estack
  mov   sp, r0          /* set stack pointer */

/* Copy the data segment initializers from flash to SRAM */
  ldr r0, =_sdata
  ldr r1, =_edata
  ldr r2, =_sidata
  movs r3, #0
  b LoopCopyDataInit

CopyDataInit:
  ldr r4, [r2, r3]
  str r4, [r0, r3]
  adds r3, r3, #4

LoopCopyDataInit:
  adds r4, r0, r3
  cmp r4, r1
  bcc CopyDataInit
  
/* Zero fill the bss segment. */
  ldr r2, =_sbss
  ldr r4, =_ebss
  movs r3, #0
  b LoopFillZerobss

FillZerobss:
  str  r3, [r2]
  adds r2, r2, #4

LoopFillZerobss:
  cmp r2, r4
  bcc FillZerobss

/* Call the clock system intitialization function.*/
  bl  SystemInit
/* Call static constructors */
  bl __libc_init_array
/* Call the application's entry point.*/
  bl main

LoopForever:
    b LoopForever


.size Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval : None
*/
    .section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b Infinite_Loop
  .size Default_Handler, .-Default_Handler
/******************************************************************************
*
* The minimal vector table for a Cortex M0.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
   .section .isr_vector,"a",%progbits
  .type g_pfnVectors, %object
  .size g_pfnVectors, .-g_pfnVectors


g_pfnVectors:
  .word  _estack
  .word  Reset_Handler
  .word  NMI_Handler
  .word  HardFault_Handler
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  SVC_Handler
  .word  0
  .word  0
  .word  PendSV_Handler
  .word  SysTick_Handler
  
  .word  WakeUp_IRQHandler         /* 16+0:  Wakeup 0 Handler	*/
  .word  PWM_Fault_IRQHandler      /* 16+1:  PWM Fault interrupt Handler	*/
  .word  I2C_IRQHandler            /* 16+2:  TWS interrupt Handler	*/
  .word  TIM0_IRQHandler           /* 16+3,  16-bit Timer0 Interrupt Handler */
  .word  TIM1_IRQHandler           /* 16+4,  16-bit Timer1 Interrupt Handler */
  .word  TIM2_IRQHandler           /* 16+5,  16-bit Timer2 Interrupt Handler */
  .word  TIM3_IRQHandler           /* 16+6,  16-bit Timer3 Interrupt Handler */
  .word  UART0_IRQHandler          /* 16+7,  UART0 Interrupt Handler   */
  .word  UART1_IRQHandler          /* 16+8,  UART1 Interrupt Handler   */ 
  .word  ADC_IRQHandler            /* 16+9,  A/D Converter Interrupt Handler	*/
  .word  WDT_IRQHandler            /* 16+10, Watchdog timer Interrupt Handler   */
  .word  BOD_IRQHandler            /* 16+11, Brown Out Detect(BOD) Interrupt Handler	*/
  .word  GPIOA_IRQHandler          /* 16+12, External Interrupt 0 Interrupt Handler	*/
  .word  GPIOB_IRQHandler          /* 16+13, External Interrupt 1 Interrupt Handler	*/
  .word  GPIOC_IRQHandler          /* 16+14, External Interrupt 2 Interrupt Handler	*/
  .word  RTC_IRQHandler            /* 16+15, RTC Interrupt Handler   */        
  .word  SPI_IRQHandler            /* 16+16, SSP Interrupt Handler   */        
  .word  PWM_Reload_IRQHandler     /* 16+17, PWM Timer Interrupt Handler */    
  .word  0           /* 16+18: Reserved 	*/               
  .word  0           /* 16+19: Reserved		*/
  .word  0           /* 16+20: Reserved  	*/              
  .word  0           /* 16+21: Reserved		*/
  .word  0           /* 16+22: Reserved     */           
  .word  0           /* 16+23: Reserved		*/
  .word  0           /* 16+24: Reserved		*/
  .word  0           /* 16+25: Reserved		*/
  .word  0           /* 16+26: Reserved		*/
  .word  0           /* 16+27: Reserved		*/
  .word  0           /* 16+28: Reserved		*/
  .word  0           /* 16+29: Reserved		*/
  .word  0           /* 16+30: Reserved		*/
  .word  0           /* 16+31: Reserved     */                 

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

  .weak      NMI_Handler
  .thumb_set NMI_Handler,Default_Handler

  .weak      HardFault_Handler
  .thumb_set HardFault_Handler,Default_Handler

  .weak      SVC_Handler
  .thumb_set SVC_Handler,Default_Handler

  .weak      PendSV_Handler
  .thumb_set PendSV_Handler,Default_Handler

  .weak      SysTick_Handler
  .thumb_set SysTick_Handler,Default_Handler

  .weak      WakeUp_IRQHandler
  .thumb_set WakeUp_IRQHandler,Default_Handler

  .weak      PWM_Fault_IRQHandler
  .thumb_set PWM_Fault_IRQHandler,Default_Handler

  .weak      I2C_IRQHandler
  .thumb_set I2C_IRQHandler,Default_Handler

  .weak      TIM0_IRQHandler
  .thumb_set TIM0_IRQHandler,Default_Handler

  .weak      TIM1_IRQHandler
  .thumb_set TIM1_IRQHandler,Default_Handler

  .weak      TIM2_IRQHandler
  .thumb_set TIM2_IRQHandler,Default_Handler

  .weak      TIM3_IRQHandler
  .thumb_set TIM3_IRQHandler,Default_Handler

  .weak      UART0_IRQHandler
  .thumb_set UART0_IRQHandler,Default_Handler

  .weak      UART1_IRQHandler
  .thumb_set UART1_IRQHandler,Default_Handler

  .weak      ADC_IRQHandler
  .thumb_set ADC_IRQHandler,Default_Handler

  .weak      WDT_IRQHandler
  .thumb_set WDT_IRQHandler,Default_Handler

  .weak      BOD_IRQHandler
  .thumb_set BOD_IRQHandler,Default_Handler

  .weak      GPIOA_IRQHandler
  .thumb_set GPIOA_IRQHandler,Default_Handler

  .weak      GPIOB_IRQHandler
  .thumb_set GPIOB_IRQHandler,Default_Handler

  .weak      GPIOC_IRQHandler
  .thumb_set GPIOC_IRQHandler,Default_Handler

  .weak      RTC_IRQHandler
  .thumb_set RTC_IRQHandler,Default_Handler

  .weak      SPI_IRQHandler
  .thumb_set SPI_IRQHandler,Default_Handler

  .weak      PWM_Reload_IRQHandler
  .thumb_set PWM_Reload_IRQHandler,Default_Handler


/************************ (C) COPYRIGHT SMicroelectronics *****END OF FILE****/

