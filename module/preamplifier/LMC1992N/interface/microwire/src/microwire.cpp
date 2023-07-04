/** @file microwire.cpp
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Mar 5, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of microwire.cpp.
*
* @page microwire.cpp
* @details Detail description of microwire.cpp.
*
*/
/* Includes ----------------------------------------------------------------------*/
#include <stdint.h>

#include <cmsis_gcc.h>
#include <stm32f091xc.h>

#include "../inc/microwire.h"
#include <stm32/gpio/inc/gpio.h>
/* Private typedef ---------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------*/
#define LMC1992N_FRAME_LENGTH					(11U)
#define LMC1992N_FRAME_CHIP_ADDRESS_Pos				(9U)
#define LMC1992N_FRAME_FUNCTION_ADDRESS_Pos			(6U)
#define LMC1992N_FRAME_DATA_Pos					(0U)

#define MASK_3							0x03
#define MASK_7							0x07
#define MASK_63							0x3F

#define LMC1992N_CHIP_SELECT_ADDRESS				(0x02)
/* Private macro -----------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------*/
uint8_t MICROWIRE::chip_select_address = {LMC1992N_CHIP_SELECT_ADDRESS};
/* Private function prototypes ---------------------------------------------------*/
/*
  Function:
  Input Data:
  Action:
*/

/* Private functions -------------------------------------------------------------*/
void
MICROWIRE::init(void)
{
  buf.frame = 0;

  GpioPinConfig(MICROWIRE_DATA_PORT, MICROWIRE_DATA_PIN, gpio_output_PP_PU_MS);
  GpioPinConfig(MICROWIRE_CLK_PORT, MICROWIRE_CLK_PIN, gpio_output_PP_PU_MS);
  GpioPinConfig(MICROWIRE_ENABLE_PORT, MICROWIRE_ENABLE_PIN, gpio_output_PP_PU_MS);

  MICROWIRE_ENABLE_SET;
  MICROWIRE_CLK_CLEAR;
}

uint16_t
MICROWIRE::build(uint8_t f_adr, uint8_t f_data)
{

  lmc1992n_frame temp_buf;

  temp_buf.frame = 0;

  temp_buf.chip_address = chip_select_address;
  temp_buf.function_address = f_adr;
  temp_buf.data = f_data;

  return temp_buf.frame;
}

void
MICROWIRE::send(uint16_t frame)
{
  int8_t i;
  lmc1992n_frame temp_buf;

  temp_buf.frame = frame;

  MICROWIRE_ENABLE_CLEAR;

  for(i = LMC1992N_FRAME_LENGTH - 1; i >= 0; i--)
    {
      if(temp_buf.frame & (1U << i)) { MICROWIRE_DATA_SET; }
      else 			     { MICROWIRE_DATA_CLEAR; }

      MICROWIRE_CLK_SET;
      MICROWIRE_CLK_CLEAR;
    }

  MICROWIRE_ENABLE_SET;
}
/*-------------------------------END OF FILE--------------------------------------*/
