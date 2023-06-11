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
#include <colour/inc/colour.h>
#include <stm32/timer/inc/timer.h>

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

      TIM_setCenterAlignMode(LED_TIMER, TIMER_CENTER_ALIGN_MODE_1);
      TIM_setPrescaler(LED_TIMER, UINT16_MAX);
      TIM_setAutoReloadReg(LED_TIMER, 100);
//      TIM_setCapCompReg(LED_TIMER, TIMER_CHANNEL_1, 255);

      init_flag = 1;
    }
}

void
HMI::LED::setColour(LED::color col, RGB_DATATYPE val)
{

  switch(col)
  {
    case color::red:
	 rgb.red= val; 	  break;
    case color::green:
	 rgb.green = val; break;
    case color::blue:
	 rgb.blue = val;  break;
  }


  hsv = rgb2hsv(&rgb);
}

void
HMI::LED::setColour(colour::RGB colour_name)
{
  rgb = colour_name;
  hsv = rgb2hsv(&rgb);
}


void
HMI::LED::setHue(uint16_t data)
{
  if(data > HSV_HUE_MAX) { return; }

  hsv.hue = data;

  rgb = hsv2rgb(&hsv);
}

void
HMI::LED::setSaturation(uint8_t data)
{
  if(data > HSV_SAT_MAX) { return; }

  hsv.saturation = data;

  rgb = hsv2rgb(&hsv);
}

void
HMI::LED::setValue(uint8_t data)
{
  if(data > HSV_VAL_MAX) { return; }

  hsv.value = data;

  rgb = hsv2rgb(&hsv);
}


void
HMI::LED::reset(LED::color col)
{

  switch(col)
  {
    case color::red:
	    rgb.red   = RGB_DEFAULT; break;
    case color::green:
	    rgb.green = RGB_DEFAULT; break;
    case color::blue:
	    rgb.blue  = RGB_DEFAULT; break;

    default:
	    rgb.red = rgb.green = rgb.blue = RGB_DEFAULT;

  }

}

void
HMI::LED::send()
{
  interface.build(&rgb);
  interface.send();
}



/*-------------------------------END OF FILE--------------------------------------*/
