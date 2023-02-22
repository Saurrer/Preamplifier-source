/** @file knob.cpp
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Feb 21, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of encoder.cpp.
*
* @page encoder.cpp
* @details Detail description of encoder.cpp.
*
*/

/* Includes ----------------------------------------------------------------------*/
#include <stdint.h>

#include <cmsis_gcc.h>
#include <stm32f091xc.h>

#include "../inc/knob.h"
#include <STM32/gpio/inc/gpio.h>

/* Private typedef ---------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------*/

/* Private macro -----------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------*/
/* Private function prototypes ---------------------------------------------------*/
/*
  Function:
  Input Data:
  Action:
*/

/* Private functions -------------------------------------------------------------*/
void HMI::KNOB::init(TIM_TypeDef * __restrict__ pu32TIM)
{
  this->button.init(KNOB_BUTTON_PORT, KNOB_BUTTON_PIN);
  GpioPinConfig(ENCODER_PORT_A, ENCODER_PIN_A, gpio_AF2_OD_MS);
  GpioPinConfig(ENCODER_PORT_B, ENCODER_PIN_B, gpio_AF2_OD_MS);

  position = &pu32TIM->CNT;		//count's up by 2 -- probably it count 2 edges
  dir = NO_MOVE;
  flag_context = 0;

  pu32TIM->CR1 |= (1U << TIM_CR1_CKD_Pos); 	/** Clock division. */

  /*
   * CC1 channel is configured as input, IC1 is mapped on TI1.
   * CC2 channel is configured as input, IC2 is mapped on TI2.
   *
   * IC1F: Input capture 1 filter:
   * 1111: fSAMPLING=fDTS/32, N=8
   */
  pu32TIM->CCMR1 = (1U << TIM_CCMR1_CC1S_Pos) |	/** CC1 channel is configured as input, IC1 is mapped on TI1 */
		   (1U << TIM_CCMR1_CC2S_Pos) ;	/** CC2 channel is configured as input, IC2 is mapped on TI2 */


  //pu32_TIM->CCER |=   (1U << TIM_CCER_CC1P_Pos) ;	/** 01 - inverted falling edge - pomiar zbocza wystepuje na wejsciu TI1 */
		      //(1U << TIM_CCER_CC2P_Pos) ;

  /*
   * SMS - 001 - Encoder mode 1 - Counter counts up/down on TI2FP1 edge depending on TI1FP2 level.
   * SMS - 010 - Encoder mode 2 - Counter counts up/down on TI1FP2 edge depending on TI2FP1 level.
   * SMS - 011 - Encoder mode 3 - Counter counts up/down on both TI1FP1 and TI2FP2 edges depending on the level of the other input.
   */
  pu32TIM->SMCR |= (2U << TIM_SMCR_SMS_Pos);

  pu32TIM->ARR = UINT16_MAX;			/** auto-reload reg */
  pu32TIM->CNT = UINT16_MAX / 2;		/** counter */

  pu32TIM->CR1 |= TIM_CR1_CEN;			/** TIM enable */

}

/*-------------------------------END OF FILE--------------------------------------*/
