/** @file led.cpp
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Feb 28, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of led.cpp.
*
* @page led.cpp
* @details Detail description of led.cpp.
*
*/
/* Includes ----------------------------------------------------------------------*/

#include <stdint.h>

#include <cmsis_gcc.h>
#include <stm32f091xc.h>

#include "../inc/led.h"
/* Private typedef ---------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------*/
#define LED_FIRST_TIME_INIT_INTERFACE		(0U)

/* Private macro -----------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------*/
int8_t HMI::LED::init_flag {0};			/**< init_flag = 0 - no initialization take place */

WS2812B HMI::LED::interface;			/**< WS2812B communication interface */
/* Private function prototypes ---------------------------------------------------*/

using namespace colour;

/*
  Function:
  Input Data:
  Action:
*/

/* Private functions -------------------------------------------------------------*/
HMI::LED::LED()
{
  if(init_flag == LED_FIRST_TIME_INIT_INTERFACE)
    {
      LED::interface.Init();
      init_flag = 1;
    }
}

void
HMI::LED::setColour(LED::color col, RGB_DATATYPE val)
{
  uint32_t grb_data = 0;

  switch(col)
  {
    case color::red:
	 rgb.red= val;
	 break;
    case color::green:
	 rgb.green = val;
	 break;
    case color::blue:
	 rgb.blue = val;
	 break;
  }

  grb_data =   (rgb.green << 16U);
  grb_data |=  (rgb.red   << 8U);
  grb_data |=  (rgb.blue  << 0U);

  interface.send(grb_data);
}

void
HMI::LED::reset(LED::color col)
{
  uint32_t temp_rgb_colour = 0;

  switch(col)
  {
    case color::red:
	    rgb.red   = RGB_DEFAULT; break;
    case color::green:
	    rgb.green = RGB_DEFAULT; break;
    case color::blue:
	    rgb.blue  = RGB_DEFAULT; break;
  }

  interface.send(temp_rgb_colour);
}
/*-------------------------------END OF FILE--------------------------------------*/
