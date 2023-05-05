/** @file startup_stm32f091xc.c
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Nov 3, 2022
* @version 	1.0.0
* @copyright 	© 2022. All Rights Reserved.
*
* @brief brief description of sstartup_stm32f091xc.c
*
* @page startup_stm32f411xe.c
*
* @details Detail description of startup_stm32f091xc.c
*
*/

#include "../inc/SystemStartup.h"

/*
 * Variables defined in linker script
 */

/* global symbols at end of code */
extern unsigned long _etext;


/* used by the startup to initialize data */
extern unsigned long _sidata;		/* pierwsze 4 bajty danych
					   inicjowanych w FLASH */

/* global symbol at data start */
extern unsigned long _sdata;		/* pierwsze 4 bajty danych
					   inicjowanych w RAM */

/* global symbol at data end */
extern unsigned long _edata;		/* 4 bajty tuż za danymi
					   inicjowanymi w RAM */

/* global symbol at bss start */
extern unsigned long _sbss;		/* pierwsze 4 bajty danych
					   nieinicjowanych w RAM */

/* global symbol at bss end */
extern unsigned long _ebss;		/* 4 bajty tuż za danymi
					   nieinicjowanymi w RAM */

/* end of RAM */
extern unsigned long _estack;		/* początkowy wierzchołek stosu */

							
/* Deklaracja głównej funkcji programu */
int main(void);

/* Domyślna procedura obsługi przerwania - nieoczekiwane
   przerwanie zawiesza mikrokontroler. */
static void 
Default_Handler(void) 
{
  for (;;);
}

/* Procedura wołana po resecie mikrokontrolera */
static void 
Reset_Handler(void) 
{
  unsigned long *src;
  unsigned long *dst;

  /* Copy .data from Flash to RAM */
  for(dst = &_sdata, src = &_sidata;
      dst < &_edata;
      ++dst, ++src)
    {
      *dst = *src;
    }

  /* Reset noinit data */
  for(*dst = &_sbss; dst < &_ebss; ++dst)
    {
      *dst = 0;
    }

  /* Call SystemInit function */
  SystemStartup();

  /* Call main function */
  main();

  /* if somehow program would back from main */
  for(;;);
}

/* Assign unhandled interrupts to default handler */

void  NMI_Handler (void) 			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void  HardFault_Handler (void) 			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void  SVC_Handler (void) 			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void  PendSV_Handler (void) 			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void  SysTick_Handler (void) 			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void  WWDG_IRQHandler (void) 			__attribute__((weak, target("thumb"), alias("Default_Handler")));

void PVD_VDDIO2_IRQHandler(void)		__attribute__((weak, target("thumb"), alias("Default_Handler")));
void RTC_IRQHandler(void)			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void FLASH_IRQHandler(void)			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void RCC_CRS_IRQHandler(void)			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void EXTI0_1_IRQHandler(void)			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void EXTI2_3_IRQHandler(void)			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void EXTI4_15_IRQHandler(void)			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void TSC_IRQHandler(void)			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void DMA1_Ch1_IRQHandler(void)			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler(void)	__attribute__((weak, target("thumb"), alias("Default_Handler")));
void DMA1_Ch4_7_DMA2_Ch3_5_IRQHandler(void)	__attribute__((weak, target("thumb"), alias("Default_Handler")));
void ADC1_COMP_IRQHandler(void)			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void TIM1_BRK_UP_TRG_COM_IRQHandler(void)	__attribute__((weak, target("thumb"), alias("Default_Handler")));
void TIM1_CC_IRQHandler(void)			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void TIM2_IRQHandler(void)			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void TIM3_IRQHandler(void)			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void TIM6_DAC_IRQHandler(void)			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void TIM7_IRQHandler(void)			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void TIM14_IRQHandler(void)			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void TIM15_IRQHandler(void)			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void TIM16_IRQHandler(void)			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void TIM17_IRQHandler(void)			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void I2C1_IRQHandler(void)			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void I2C2_IRQHandler(void)			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void SPI1_IRQHandler(void)			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void SPI2_IRQHandler(void)			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void USART1_IRQHandler(void)			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void USART2_IRQHandler(void)			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void USART3_8_IRQHandler(void)			__attribute__((weak, target("thumb"), alias("Default_Handler")));
void CEC_CAN_IRQHandler(void)			__attribute__((weak, target("thumb"), alias("Default_Handler")));

void (* const g_pfnVectors[])(void) __attribute__((section(".isr_vector"))) =
{
  (void *)&_estack,        	 		/* Początkowa wartość wskaźnika stosu */
  Reset_Handler,        	     		/* Reset is invoked on power up or a warm reset */

  /* Cortex-M0 interrupts */
  NMI_Handler,
  HardFault_Handler,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  SVC_Handler,
  0,
  0,
  PendSV_Handler,
  SysTick_Handler,
  WWDG_IRQHandler,				/* Window WatchDog              */
  PVD_VDDIO2_IRQHandler,			/* PVD and VDDIO2 through EXTI Line detect */
  RTC_IRQHandler,				/* RTC through the EXTI line    */
  FLASH_IRQHandler,				/* FLASH                        */
  RCC_CRS_IRQHandler,				/* RCC and CRS                  */
  EXTI0_1_IRQHandler,				/* EXTI Line 0 and 1            */
  EXTI2_3_IRQHandler,				/* EXTI Line 2 and 3            */
  EXTI4_15_IRQHandler,				/* EXTI Line 4 to 15            */
  TSC_IRQHandler,				/* TSC                          */
  DMA1_Ch1_IRQHandler,				/* DMA1 Channel 1               */
  DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler,		/* DMA1 Channel 2 and 3 & DMA2 Channel 1 and 2 */
  DMA1_Ch4_7_DMA2_Ch3_5_IRQHandler,		/* DMA1 Channel 4 to 7 & DMA2 Channel 3 to 5 */
  ADC1_COMP_IRQHandler,				/* ADC1, COMP1 and COMP2        */
  TIM1_BRK_UP_TRG_COM_IRQHandler,		/* TIM1 Break, Update, Trigger and Commutation */
  TIM1_CC_IRQHandler,				/* TIM1 Capture Compare         */
  TIM2_IRQHandler,				/* TIM2                         */
  TIM3_IRQHandler,				/* TIM3                         */
  TIM6_DAC_IRQHandler,				/* TIM6 and DAC                 */
  TIM7_IRQHandler,				/* TIM7                         */
  TIM14_IRQHandler,				/* TIM14                        */
  TIM15_IRQHandler,				/* TIM15                        */
  TIM16_IRQHandler,				/* TIM16                        */
  TIM17_IRQHandler,				/* TIM17                        */
  I2C1_IRQHandler,				/* I2C1                         */
  I2C2_IRQHandler,				/* I2C2                         */
  SPI1_IRQHandler,				/* SPI1                         */
  SPI2_IRQHandler,				/* SPI2                         */
  USART1_IRQHandler,				/* USART1                       */
  USART2_IRQHandler,				/* USART2                       */
  USART3_8_IRQHandler,				/* USART3, USART4, USART5, USART6, USART7, USART8 */
  CEC_CAN_IRQHandler,				/* CEC and CAN                  */
};
