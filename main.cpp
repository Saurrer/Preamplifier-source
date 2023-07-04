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

/* test utils */
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

extern "C" void SysTick_Handler(void)
{
  TEST_IO_4_PORT->ODR ^= TEST_IO_4_PIN;

  HMI::pLcd->refreshDisplay();
}

extern "C" void HardFault_Handler(void)
{
  for(;;);
}


int main(void)
{
  uint8_t buffer[8192];

  DIR dir;
  FATFS fatfs;
  FIL file;
  FILINFO fno;
  FRESULT res;
  UINT read_bytes;
  char cwd_name[64] = {0};

  pPlayer = new(MUSIC_PLAYER);

  __DSB();
  __ISB();

  res = f_mount(&fatfs, "", 1);			//inicjalizacja warstwy aplikacji
  f_getcwd(cwd_name, sizeof(cwd_name));

  res = f_opendir(&dir, cwd_name);

  if(res == FR_OK) { pPlayer->playlist.init(&dir); }

  /* utils */
  delay_init();
  init_test_io();

  /* modules */
  module::init();

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
      else if (flag == 16)
	{
	  pPlayer->resetFileIndex();
	  pPlayer->resetFileSize();

	  __DSB();
	  __ISB();

	  flag = 0;
	}

      else if (flag == 21)
	{

	  res = f_open(&file, "ShootingStars_sd.wav", FA_READ);
	  uint8_t i;
	  if(res == FR_OK)
	    {
	      /*
	       * FRESULT f_read (
	       * FIL* fp,      [IN] File object
	       * void* buff,   [OUT] Buffer to store read data
	       * UINT btr,     [IN] Number of bytes to read
	       * UINT* br      [OUT] Number of bytes read
	       * );
	       *
	       * typedef unsigned int		UINT;	int must be 16-bit or 32-bit
	       * typedef unsigned char		BYTE;	 char must be 8-bit
	       *
	       */
	      f_read(&file, file.buf, FF_MAX_SS, &read_bytes);

	      int x;
	      for(x = 0; x < FF_MAX_SS; x++)
		{
		  pPlayer->current_buffer->put(*(file.buf + x));
		}

	      if(x != (pPlayer->current_buffer->getCount())) { return 1; }	//odczytano

	      pPlayer->parseHeaderWAV();
	      //pPlayer->parseHeaderWAV(file.buf);
	      int z;
	      for(;;)
		{
		  f_read(&file, buffer, sizeof(buffer), &read_bytes);
		  if (read_bytes == 0) { break; } /* error or eof */
		}

	      //uint8_t some_char = *(file.buf + WAV_HEADER_SIZE);	/**< beginning of data */
	      i++;

	      //fr = f_sync(&file);
	      res = f_close(&file);
	    }

	  flag = 0;
	}
      else if(flag == 22)
	{
	  pPlayer->playSample();

	  flag = 0;
	}
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
