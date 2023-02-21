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
* @page make_page_for_this_file_in_doxygen
*
* @details Detail description of file.
*
*/


#include <stdint.h>

#include <cmsis_gcc.h>
#include <stm32f091xc.h>

void SystemStartup(void);

void SystemStartup(void)
{
  RCC->AHBENR |=  RCC_AHBENR_GPIOAEN ;

  RCC->APB1ENR |= RCC_APB1ENR_TIM7EN	|	/** delay */
		  RCC_APB1ENR_TIM2EN	;	/** timer used by knob */

  //RCC->APB1ENR |= RCC_APB1ENR_USART2EN;	//logs

  __DSB();
  __ISB();
}


