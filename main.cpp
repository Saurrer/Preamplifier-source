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

#include <Utils/test_io/inc/test_io.h>

#include "project_config.h"			/** project configuration */
/*
+=============================================================================+
*/

/*
 * GPIO pin
 */

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

  module::init();
  SD_init();
  init_test_io();

  __DSB();
  __ISB();

  const char * tekst_1 = "Hello World\n";
  const char * tekst_2 = "kij w oko\n";
  const char * tekst_3 = "build date: ";
  const char * tekst_4 = "build time: ";

  FRESULT fr;
  FATFS fatfs;
  FIL file;
  UINT buf;


  uint8_t flag = 0;
  SysTick_Config(CPU_FREQUENCY/8/10);
  SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;

  for(;;)/*---------------------------------------- INFINITE LOOP ----------------------------------------------*/
    {
      HMI::scrollMenu();
      HMI::jumpSubMenu();


      if(flag == 1)
	{
	  fr = f_mount(&fatfs, "", 1);
	  if(fr == FR_OK)
	    {

	      fr = f_open(&file, "plik_testowy_6.txt", FA_CREATE_ALWAYS | FA_READ | FA_WRITE);

	      if(fr == FR_OK)
	        {

	          //Todo - sprawdzic kodowanie znakow

		    f_write(&file, tekst_1, sizeof(tekst_1), &buf);
		    f_write(&file, tekst_2, sizeof(tekst_2), &buf);

		    f_write(&file, tekst_3, sizeof(tekst_3), &buf);
		    f_write(&file, build_date, sizeof(build_date), &buf);

		    f_write(&file, tekst_4, sizeof(tekst_4), &buf);
		    f_write(&file, build_time, sizeof(build_time), &buf);



		    f_puts(tekst_1, &file);

		    f_puts(tekst_3, &file);
		    f_puts(build_date, &file);
		    f_puts("\n", &file);
		    f_puts(tekst_4, &file);
		    f_puts(build_time, &file);


	        }

	      f_sync(&file);
	      f_close(&file);

	    }

	  f_mount(0, "", 1);

	  flag = 0;
	}

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

