/** @file SystemStartup.cpp
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		21 Feb 2023
* @version 	1.0.0
* @copyright 	� 2023. All Rights Reserved.
*
* @brief brief description of file.
*
* @page SystemStartup.cpp
*
* @details Detail description of file.
*
*/
/* Includes ----------------------------------------------------------------------*/

#include <stdint.h>

#include <cmsis_gcc.h>
#include <stm32f091xc.h>

#include "../inc/SystemStartup.h"

/* Private define ----------------------------------------------------------------*/
#define OSC_IN_PORT	GPIOF
#define OSC_IN_PIN	PF0

#define OSC_OUT_PORT	GPIOF
#define OSC_OUT_PIN	PF1

/* Private function prototypes ---------------------------------------------------*/

void SystemStartup(void);
void set_external_hse(void);

/* Private functions -------------------------------------------------------------*/
void SystemStartup(void)
{
  RCC->AHBENR |=  RCC_AHBENR_GPIOAEN 	|
		  RCC_AHBENR_DMA1EN	|	/** ws2812b interface */
		  RCC_AHBENR_DMA2EN  	;	/** ws2812b interface */

  RCC->APB1ENR |= RCC_APB1ENR_TIM7EN	|	/** delay */
		  RCC_APB1ENR_USART2EN	|	/** ws2812b interface */
		  RCC_APB1ENR_TIM2EN	;	/** timer used by knob */

  //RCC->APB1ENR |= RCC_APB1ENR_USART2EN;	//logs

  set_external_hse();

  __DSB();
  __ISB();
}


void set_external_hse(void)
{
  RCC->AHBENR |= RCC_AHBENR_GPIOFEN;
/*
 * When the HSE or LSE oscillator is switched ON (by setting the HSEON or LSEON bit in the
 * RCC_CSR register) the oscillator takes control of its associated pins and the GPIO
 * configuration of these pins has no effect
 */
  FLASH->ACR |= FLASH_ACR_PRFTBE;		/** enable prefetch buffer */

  /* GPIO remap */

  RCC->CR |= RCC_CR_CSSON;			/** enable Clock security system */
  __DSB();
  __ISB();

  RCC->CR |= RCC_CR_HSEON;
  while(!(RCC->CR & RCC_CR_HSERDY));		/** if hse is ready */

  /* PLL */
  RCC->CFGR2 = (1U << RCC_CFGR2_PREDIV_Pos);	/** PREDIV - div2 */
  RCC->CFGR |= (2U << RCC_CFGR_PLLSRC_Pos) |	/** PLLSRC - HSE */
	       (10U << RCC_CFGR_PLLMUL_Pos) ;	/** PLLMUL - x12 */
  __DSB();
  RCC->CR |= RCC_CR_PLLON;
  while(!(RCC->CR & RCC_CR_PLLRDY));

  /* FLASH latency */
  FLASH->ACR |= (1U << FLASH_ACR_LATENCY_Pos);	/** one wait state */
  while(!(FLASH->ACR & (1U << FLASH_ACR_LATENCY_Pos)));

  //RCC->CFGR |= (1U << RCC_CFGR_SW_Pos);	/** switch sys clk source to hse */
  //while(!((RCC->CFGR & RCC_CFGR_SWS) == RCC_CFGR_SWS_HSE));

  RCC->CFGR |= (2U << RCC_CFGR_SW_Pos);		/** switch sys clk source to PLL clk*/
  while(!((RCC->CFGR & RCC_CFGR_SWS) == RCC_CFGR_SWS_PLL));

  RCC->CFGR3 |= (1U << RCC_CFGR3_USART2SW_Pos);	/** set usart2 clock to sys clk */
}


