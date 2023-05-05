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
void fillbuffer(uint8_t * buf, uint16_t buf_size, uint8_t dumbdata);

const char * build_time = __TIME__;	//widocznosc tych zmiennych to kwestia optymalizacji linkera
const char * build_date = __DATE__;	//widocznosc tych zmiennych to kwestia optymalizacji linkera
//__attribute__((section(".rodata.compile_data")))

SD_CardStatus status;
uint8_t result;
//__attribute__((section(".rodata.compile_data")))

extern "C" void SysTick_Handler(void)
{
  TEST_IO_4_PORT->ODR ^= TEST_IO_4_PIN;

  HMI::pLcd->refreshDisplay();
}

extern "C" void HardFault_Handler(void)
{
  for(;;);
}

//__attribute__( (optimize("-O1")) );
int main(void)
{
  FRESULT res;
  char *fn;
  FILINFO fno;

  FRESULT fr;
  DIR dir;
  FATFS fatfs;
  FIL file;
  UINT buf;

  char cwd_name[64] = {0};

  pPlayer = new(MUSIC_PLAYER);

  __DSB();
  __ISB();

  fr = f_mount(&fatfs, "", 1);			//inicjalizacja warstwy aplikacji
  status = (SD_CardStatus) disk_initialize(0);	//inicjalizacja warstwy fizycznej

  f_getcwd(cwd_name, sizeof(cwd_name));

  res = f_opendir(&dir, cwd_name);

  if(res == FR_OK) { pPlayer->playlist.init(&dir); }
  pPlayer->init();

  delay_init();

  module::init();

  init_test_io();

  const char * tekst_3 = "build date: ";
  const char * tekst_4 = "build time: ";

  uint8_t flag = 0;
  SysTick_Config(CPU_FREQUENCY/8/10);
  SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;

  for(;;)/*---------------------------------------- INFINITE LOOP ----------------------------------------------*/
    {
      HMI::scrollMenu();
      HMI::jumpSubMenu();

      if(flag == 2)
	{
	  readOCR_reg(pOCR);

	  flag = 0;
	}
      else if(flag == 3)
	{
	  readCID_reg(pCID);

	  flag = 0;
	}
      else if(flag == 4)
	{
	  readCSD_reg(pCSD);

	  flag = 0;
	}
      else if(flag == 5)
	{
	  check(pCSD);
	  flag = 0;
	}

      if(flag == 15)
	{
	  pPlayer->enableMusic();
	  pPlayer->enableMusic();

	  flag = 0;
	}
      else if (flag == 16)
	{
	  pPlayer->resetFileIndex();
	  pPlayer->resetFileSize();

	  __DSB();
	  __ISB();

	  flag = 0;
	}
      else if (flag == 17)
	{
	  preamp::pSource->changeSource(preamp::INPUT::minijack);
	  flag = 0;
	}
      else if (flag == 18)
	{
	  preamp::pSource->changeSource(preamp::INPUT::microSD);
	  flag = 0;
	}

/*
      else if (flag == 21)
	{
	  fr = f_open(&file, "sample.wav", FA_READ);

	  if(fr == FR_OK)
	    {
	      for(;;)
		{
		  f_read(&file, buff, btr, br)
		}
	    }

	  fr = f_sync(&file);
	  fr = f_close(&file);

	  flag = 0;
	}
*/

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

void fillbuffer(uint8_t * buf, uint16_t buf_size, uint8_t dumbdata)
{
  uint16_t i;

  for(i = 0; i < buf_size; i++)
    {
      buf[i] = dumbdata;
    }
}
