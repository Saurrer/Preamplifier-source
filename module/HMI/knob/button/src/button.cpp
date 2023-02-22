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

#include <STM32/gpio/inc/gpio.h>
#include "../inc/button.h"

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
BUTTON::BUTTON(GPIO_TypeDef * const __restrict button_port, GpioPin button_pin);

/*
  Function:
  Input Data:
  Action:
*/
uint8_t BUTTON::getStatus(void);

/*
  Function:
  Input Data:
  Action:
*/
void BUTTON::read(void);

/* Private functions -------------------------------------------------------------*/
BUTTON::BUTTON(GPIO_TypeDef * const __restrict button_port, GpioPin button_pin)
:status{BUTTON_NOT_INITIALIZED}
{
  GpioPinConfig(button_port, button_pin, gpio_input_floating);

  if(!(button_port->IDR & BUTTON_PIN))  { status = BUTTON_ON; }
  else 					{ status = BUTTON_OFF; }

}

uint8_t BUTTON::getStatus(void) { return status; }

void BUTTON::read(void)
{
  uint32_t cnt1, cnt2;
  cnt1 = 200000;		//doświadczalnie
  cnt2 = 100000;		//doświadczalnie

  if( !(keylock) && !(BUTTON_PORT->IDR & BUTTON_PIN))
     {
      keylock = 1;

      while(cnt1--)
	{
	  if(BUTTON_PORT->IDR & BUTTON_PIN)
	    {
	      while(cnt2--)
		{
		  if(!(BUTTON_PORT->IDR & BUTTON_PIN))
		    {
		      //double press
		      status = BUTTON_DOUBLE_PRESS;
		      //LED_GREEN_PORT->ODR ^= LED_GREEN_PIN;
		      return;
		    }
		}
	      status = BUTTON_SINGLE_PRESS;
	      //LED_RED_PORT->ODR ^= LED_RED_PIN;
	      return;
	    }
	}

	//long press
	status = BUTTON_LONG_PRESS;

	//LED_YELLOW_PORT->ODR ^= LED_YELLOW_PIN;
     }
    else if (keylock && (BUTTON_PORT->IDR & BUTTON_PIN))
      {
	keylock++;
	status = BUTTON_OFF;
	//LED_GREEN_LOW;
	//LED_YELLOW_LOW;
      }
}
/*-------------------------------END OF FILE--------------------------------------*/
