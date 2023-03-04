/** @file button.cpp
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Feb 22, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of button.cpp.
*
* @page button.cpp
* @details Detail description of button.cpp.
*
*/
/* Includes ----------------------------------------------------------------------*/

#include <stdint.h>

#include <cmsis_gcc.h>
#include <stm32f091xc.h>

#include "../inc/button.h"

/* Private typedef ---------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------*/
#define TEST 0

#if (TEST == 1)
  #include <utils/test_io/inc/test_io.h>
#endif

#define BUTTON_READ_FUNCTION_DELAY_1		(500000U) /**< experimental result */
#define BUTTON_READ_FUNCTION_DELAY_2		(300000U) /**< experimental result */

/* Private macro -----------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------*/
/* Private function prototypes ---------------------------------------------------*/
/*
  Function:
  Input Data:
  Action:
*/

/* Private functions -------------------------------------------------------------*/

/**
 * @fn void HMI::BUTTON::init(GPIO_TypeDef * button_port, GpioPin button_pin)
 *
 * @details
 *
 */
void HMI::BUTTON::init(GPIO_TypeDef * button_port, GpioPin button_pin)
{
  status = BUTTON_NOT_INITIALIZED;

  GpioPinConfig(button_port, button_pin, gpio_input_floating);

  if(!(button_port->IDR & BUTTON_PIN))  { status = BUTTON_ON; }
  else 					{ status = BUTTON_OFF; }

#if (TEST == 1)
  init_test_io();
#endif
}

/**
 * @fn uint8_t HMI::BUTTON::getStatus(void)
 *
 * @details
 *
 * @return
 */
uint8_t HMI::BUTTON::getStatus(void) { return status; }

/**
 * @fn void HMI::BUTTON::read(void)
 *
 * @details
 *
 * @return
 */
void HMI::BUTTON::read(void)
{
  int32_t cnt1, cnt2;
  cnt1 = BUTTON_READ_FUNCTION_DELAY_1;
  cnt2 = BUTTON_READ_FUNCTION_DELAY_2;

  if( !(keylock) && !(BUTTON_PORT->IDR & BUTTON_PIN))
     {
      keylock = 1;

      while(cnt1--)					/**< single press */
	{
	  if(BUTTON_PORT->IDR & BUTTON_PIN)
	    {
	      while(cnt2--)				/**< double press */
		{
		  if(!(BUTTON_PORT->IDR & BUTTON_PIN))
		    {
		      status = BUTTON_DOUBLE_PRESS;

#if (TEST == 1)
		      TEST_IO_1_PORT->ODR ^= TEST_IO_1_PIN;
#endif
		      return;
		    }
		}
	      status = BUTTON_SINGLE_PRESS;

#if (TEST == 1)
	      TEST_IO_2_PORT->ODR ^= TEST_IO_2_PIN;
#endif
	      return;
	    }
	}

	//long press
	status = BUTTON_LONG_PRESS;
#if (TEST == 1)
	TEST_IO_3_PORT->ODR ^= TEST_IO_3_PIN;
#endif
     }
    else if (keylock && (BUTTON_PORT->IDR & BUTTON_PIN))
      {
	keylock++;
	status = BUTTON_OFF;
#if (TEST == 1)
	TEST_IO_1_CLEAR;	/**< double press */
	TEST_IO_3_CLEAR;	/**< long press */
#endif

      }
}
/*-------------------------------END OF FILE--------------------------------------*/
