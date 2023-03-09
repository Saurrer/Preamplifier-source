/** @file main.cpp
*
* @author
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Feb 19, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of main.cpp.
*
* @page main.cpp
* @details Detail description of main.cpp.
*
*/

/*
+=============================================================================+
| includes
+=============================================================================+
*/

#include "inc/main.h"

#include "config.h"			/** project configuration */
#include <Utils/test_io/inc/test_io.h>
/*
+=============================================================================+
*/

/*
 * GPIO pin
 */
#define LCD_BRIGHTNESS_PORT	GPIOB
#define LCD_BRIGHTNESS_PIN	PB1


const char * build_time __attribute__((section(".rodata.compile_data"))) = __TIME__;	//widocznosc tych zmiennych to kwestia optymalizacji linkera
const char * build_date __attribute__((section(".rodata.compile_data"))) = __DATE__;	//widocznosc tych zmiennych to kwestia optymalizacji linkera

extern "C" void SysTick_Handler(void)
{
  TEST_IO_4_PORT->ODR ^= TEST_IO_4_PIN;

  HMI::pLcd->refreshDisplay();
}


int main(void)
{

  delay_init();

  GpioPinConfig(LCD_BRIGHTNESS_PORT, LCD_BRIGHTNESS_PIN, gpio_output_PP_PU_LS);
  LCD_BRIGHTNESS_PORT->BSRR|= GPIO_BSRR_BS_1;

  init_test_io();

  HMI::init();
  Preamplifier::init();

  __DSB();
  __ISB();

  uint8_t flag = 0;
  SysTick_Config(CPU_FREQUENCY/8/10);
  SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;

  for(;;)/*---------------------------------------- INFINITE LOOP ----------------------------------------------*/
    {
      HMI::scrollMenu();
      HMI::jumpSubMenu();


/*
      if(flag == 1)		*< red
	{
	  HMI::pLed->setColour(HMI::LED::color::red, 128);
	  flag = 0;
	}
      else if(flag == 2)	*< green
      	{
	  HMI::pLed->setColour(HMI::LED::color::green, 128);
	  flag = 0;
      	}
      else if(flag == 3)	*< blue
      	{
	  HMI::pLed->setColour(HMI::LED::color::blue, 128);
      	  flag = 0;
      	}
      else if(flag == 4)	*< white
      	{
	  HMI::pLed->setColour(HMI::LED::color::red, 128);
	  HMI::pLed->setColour(HMI::LED::color::green, 128);
	  HMI::pLed->setColour(HMI::LED::color::blue, 128);

	  flag = 0;
      	}
      else if(flag == 5)	*< black
      	{
	  HMI::pLed->reset(HMI::LED::color::red);
	  HMI::pLed->reset(HMI::LED::color::green);
	  HMI::pLed->reset(HMI::LED::color::blue);
      	  flag = 0;
      	}
      else if(flag == 6)	*< send
	{
	  HMI::pLed->send();
	  flag = 0;
	}
*/


/*
      else if (flag == 6)	*<
	{
	  hsv_1 = colours::rgb2hsv(&rgb_1);
	  flag = 0;
	}
      else if (flag == 7)	*<
	{
	  rgb_2 = colours::hsv2rgb(&hsv_2);
	  flag = 0;
	}
*/

    }
}

