/** @file lmc1992n.cpp
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Mar 6, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of lmc1992n.cpp.
*
* @page lmc1992n.cpp
* @details Detail description of lmc1992n.cpp.
*
*/
/* Includes ----------------------------------------------------------------------*/

#include "../inc/lmc1992n.h"
/* Private typedef ---------------------------------------------------------------*/

typedef uint8_t LMC1992_function_data;

/* Private define ----------------------------------------------------------------*/
/* Private macro -----------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------*/
int8_t LMC1992_FUNCTION::init_flag {0};

MICROWIRE LMC1992_FUNCTION::interface;
/* Private function prototypes ---------------------------------------------------*/
/*
  Function:
  Input Data:
  Action:
*/

/* Private functions -------------------------------------------------------------*/
LMC1992_FUNCTION::LMC1992_FUNCTION
(uint8_t f_adr, int8_t f_min_val, int8_t f_max_val, int8_t f_init_val)
:address(f_adr),
 min(f_min_val), max(f_max_val),
 value(f_init_val)
{
  if(!(init_flag))
    {
      LMC1992_FUNCTION::interface.init();
      init_flag++;
    }
}

int8_t
LMC1992_FUNCTION::setValue(int8_t val)
{
  uint16_t temp_buf;

  if(value <= max && value >= min)
    {
      value = val;

      temp_buf = interface.build(address, value);
      interface.send(temp_buf);

      return 0;
    }
  else { return 1; }
}

int8_t
LMC1992_FUNCTION::getValue() { return value; }

LMC1992_FUNCTION&
LMC1992_FUNCTION::operator++()
{
  uint16_t temp_buf;
  value++;

  if(value > max) { value = max; }
  else
    {
      temp_buf = interface.build(address, value);
      interface.send(temp_buf);
    }

  return (*this);
}

LMC1992_FUNCTION&
LMC1992_FUNCTION::operator--()
{
  uint16_t temp_buf;
  value--;

  if(value < min) { value = min; }
  else
    {
      temp_buf = interface.build(address, value);
      interface.send(temp_buf);
    }

  return (*this);
}

uint8_t
LMC1992_FUNCTION::getAddress() { return value; }

/*-------------------------------END OF FILE--------------------------------------*/
