/*
 ============================================================================
 Name        : main.cpp
 Author      : Mariusz Mikulski
 Date	     : 21 Feb 2023
 Version     : 1
 Copyright   : Your copyright notice (� 2021. All Rights Reserved.)
 Description : write description of file.
 ============================================================================
*/

/*
+=============================================================================+
| includes
+=============================================================================+
*/

#include "inc/main.h"

/*
+=============================================================================+
*/

/*
 * GPIO pin
 */

#define LED_1_PORT			GPIOA
#define LED_1_PIN			PA10

#define LED_2_PORT			GPIOA
#define LED_2_PIN			PA9

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
  GpioPinConfig(LED_2_PORT, LED_2_PIN, gpio_output_PP_PU_LS);

  __DSB();
  __ISB();

  SysTick_Config(8000000/2);
  for(;;)/*---------------------------------------- INFINITE LOOP ----------------------------------------------*/
    {
      GPIOA->ODR ^= GPIO_ODR_9;
      delay_ms(100);
    }
}

