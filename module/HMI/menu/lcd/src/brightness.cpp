/** @file brightness.cpp
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Mar 18, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of brightness.cpp.
*
* @page brightness.cpp
* @details Detail description of brightness.cpp.
*
*/
/* Includes ----------------------------------------------------------------------*/
#include <stdint.h>

#include <cmsis_gcc.h>
#include <stm32f091xc.h>

#include <stm32/timer/inc/timer.h>
#include <stm32/gpio/inc/gpio.h>

#include "../inc/brightness.h"
/* Private typedef ---------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------*/

/* Private macro -----------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------*/
uint8_t HMI::BRIGHTNESS::init_flag {0};
/* Private function prototypes ---------------------------------------------------*/
/*
  Function:
  Input Data:
  Action:
*/

/* Private functions -------------------------------------------------------------*/
void HMI::BRIGHTNESS::init(void)
{
  GpioPinConfig(LCD_BRIGHTNESS_PORT, LCD_BRIGHTNESS_PIN, gpio_AF0_PP_HS);

//  GpioPinConfig(LCD_BRIGHTNESS_PORT, LCD_BRIGHTNESS_PIN, gpio_output_PP_PU_LS);
//  LCD_BRIGHTNESS_PORT->BSRR|= GPIO_BSRR_BS_1;

  TIM_setPrescaler(LCD_BRIGHTNESS_TIMER, 3);

  TIM_setAutoReloadReg(LCD_BRIGHTNESS_TIMER, LCD_BRIGHTNESS_RESOLUTION);
  TIM_setCapCompReg(LCD_BRIGHTNESS_TIMER, TIMER_CHANNEL_1, LCD_BRIGHTNESS_RESOLUTION/2);

  LCD_BRIGHTNESS_TIMER->CCMR1 |= (6U << TIM_CCMR1_OC1M_Pos)	|	 /**<  */
				 (1U << TIM_CCMR1_OC1PE_Pos)	;	 /**<  */
  LCD_BRIGHTNESS_TIMER->CCER |=  (1U << TIM_CCER_CC1E_Pos);

  LCD_BRIGHTNESS_TIMER->BDTR |= TIM_BDTR_MOE;

}

/*-------------------------------END OF FILE--------------------------------------*/
