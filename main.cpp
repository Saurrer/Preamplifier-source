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
#include "config.h"
/*
+=============================================================================+
*/

/*
 * GPIO pin
 */

#define LED_1_PORT			GPIOA
#define LED_1_PIN			PA10

const char * build_time __attribute__((section(".rodata.compile_data"))) = __TIME__;	//widocznosc tych zmiennych to kwestia optymalizacji linkera
const char * build_date __attribute__((section(".rodata.compile_data"))) = __DATE__;	//widocznosc tych zmiennych to kwestia optymalizacji linkera

extern "C" void SysTick_Handler(void)
{
  GPIOA->ODR ^= GPIO_ODR_10;
}


int main(void)
{
  delay_init();

  GpioPinConfig(LED_1_PORT, LED_1_PIN, gpio_output_PP_PU_LS);

  HMI::init();

  __DSB();
  __ISB();

  uint8_t flag = 0;
  SysTick_Config(CPU_FREQUENCY/8/2);
  SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;


  for(;;)/*---------------------------------------- INFINITE LOOP ----------------------------------------------*/
    {
      HMI::pKnob->button.read();

      if(flag == 1)		/**< red */
	{
	  HMI::pLed->setColour(HMI::LED::color::red, 128);
	  flag = 0;
	}
      else if(flag == 2)	/**< green */
      	{
	  HMI::pLed->setColour(HMI::LED::color::green, 128);
	  flag = 0;
      	}
      else if(flag == 3)	/**< blue */
      	{
	  HMI::pLed->setColour(HMI::LED::color::blue, 128);
      	  flag = 0;
      	}
      else if(flag == 4)	/**< white */
      	{
	  HMI::pLed->setColour(HMI::LED::color::red, 128);
	  HMI::pLed->setColour(HMI::LED::color::green, 128);
	  HMI::pLed->setColour(HMI::LED::color::blue, 128);

	  flag = 0;
      	}
      else if(flag == 5)	/**< black */
      	{
	  HMI::pLed->reset(HMI::LED::color::red);
	  HMI::pLed->reset(HMI::LED::color::green);
	  HMI::pLed->reset(HMI::LED::color::blue);
      	  flag = 0;
      	}
      else if(flag == 6)	/**< send */
	{
	  HMI::pLed->send();
	  flag = 0;
	}

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

