/** @file functions.cpp
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Mar 9, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of functions.cpp.
*
* @page functions.cpp
* @details Detail description of functions.cpp.
*
*/
/* Includes ----------------------------------------------------------------------*/
#include <stdint.h>

#include <stm32f091xc.h>

#include "../inc/functions.h"
#include "../../../preamplifier/inc/preamp.h"
#include "../../inc/HMI.h"
/* Private typedef ---------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------*/

/* Private macro -----------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------*/

namespace HMI
{

  void changeFader_LR(void);
  void changeFader_RR(void);
  void changeFader_LF(void);
  void changeFader_RF(void);
  void changeVolume(void);
  void changeTreble(void);
  void changeBass(void);

}  // namespace HMI

/* Private function prototypes ---------------------------------------------------*/
/*
  Function:
  Input Data:
  Action:
*/
//static void printFunctionName(LMC1992_FUNCTION & function);
//static void printFunctionValueLine(LMC1992_FUNCTION & function, uint16_t val);
static void printFunctionValueLine(uint8_t max, uint8_t min, uint8_t val);

/* Private functions -------------------------------------------------------------*/
void
HMI::changeFader_LR()
{

  LMC1992_FUNCTION & function = preamp::pSource->fd_left_rear;

  pLcd->clearBuffer();
  pLcd->locate(0, 5); pLcd->print(preamp::FunctionNameTable[function.getAddress()]);
  pLcd->locate(1, 0);

  while(1)
    {
      switch(pKnob->readDirection())
      {
	    case KNOB::LEFT:
	      function.operator--();
	      break;

	    case KNOB::RIGHT:
	      function.operator++();
	      break;
      }


      if(pKnob->button.getStatus() == BUTTON::BUTTON_DOUBLE_PRESS )  { break; }
    }

  pKnob->button.clearStatus();
}

void
HMI::changeFader_RR()
{

  LMC1992_FUNCTION & function = preamp::pSource->fd_right_rear;

  pLcd->clearBuffer();
  pLcd->locate(0, 5); pLcd->print(preamp::FunctionNameTable[function.getAddress()]);
  pLcd->locate(1, 0);

  while(1)
    {
      switch(pKnob->readDirection())
      {
	    case KNOB::LEFT:
	      function.operator--();
	      break;

	    case KNOB::RIGHT:
	      function.operator++();
	      break;
      }


      if(pKnob->button.getStatus() == BUTTON::BUTTON_DOUBLE_PRESS )  { break; }
    }

  pKnob->button.clearStatus();
}

void
HMI::changeFader_LF()
{

  LMC1992_FUNCTION & function = preamp::pSource->fd_left_front;

  pLcd->clearBuffer();
  pLcd->locate(0, 5); pLcd->print(preamp::FunctionNameTable[function.getAddress()]);
  pLcd->locate(1, 0);

  while(1)
    {
      switch(pKnob->readDirection())
      {
	    case KNOB::LEFT:
	      function.operator--();
	      break;

	    case KNOB::RIGHT:
	      function.operator++();
	      break;
      }


      if(pKnob->button.getStatus() == BUTTON::BUTTON_DOUBLE_PRESS )  { break; }
    }

  pKnob->button.clearStatus();
}

void
HMI::changeFader_RF()
{

  LMC1992_FUNCTION & function = preamp::pSource->fd_right_front;

  pLcd->clearBuffer();
  pLcd->locate(0, 5); pLcd->print(preamp::FunctionNameTable[function.getAddress()]);
  pLcd->locate(1, 0);

  while(1)
    {
      switch(pKnob->readDirection())
      {
	    case KNOB::LEFT:
	      function.operator--();
	      break;

	    case KNOB::RIGHT:
	      function.operator++();
	      break;
      }


      if(pKnob->button.getStatus() == BUTTON::BUTTON_DOUBLE_PRESS )  { break; }
    }

  pKnob->button.clearStatus();
}

void
HMI::changeVolume()
{

  LMC1992_FUNCTION & function = preamp::pSource->volume;

  pLcd->clearBuffer();
  pLcd->locate(0, 5); pLcd->print(preamp::FunctionNameTable[function.getAddress()]);
  pLcd->locate(1, 0);

  while(1)
    {
      switch(pKnob->readDirection())
      {
	    case KNOB::LEFT:
	      function.operator--();
	      break;

	    case KNOB::RIGHT:
	      function.operator++();
	      break;
      }


      if(pKnob->button.getStatus() == BUTTON::BUTTON_DOUBLE_PRESS )  { break; }
    }

  pKnob->button.clearStatus();
}

void
HMI::changeTreble()
{

  LMC1992_FUNCTION & function = preamp::pSource->treble;

  pLcd->clearBuffer();
  pLcd->locate(0, 5); pLcd->print(preamp::FunctionNameTable[function.getAddress()]);
  pLcd->locate(1, 0);

  while(1)
    {
      switch(pKnob->readDirection())
      {
	    case KNOB::LEFT:
	      function.operator--();
	      break;

	    case KNOB::RIGHT:
	      function.operator++();
	      break;
      }


      if(pKnob->button.getStatus() == BUTTON::BUTTON_DOUBLE_PRESS )  { break; }
    }

  pKnob->button.clearStatus();
}


void
HMI::changeBass()
{

  LMC1992_FUNCTION & function = preamp::pSource->bass;

  pLcd->clearBuffer();

  pLcd->locate(0, 5); pLcd->print(preamp::FunctionNameTable[function.getAddress()]);
  pLcd->locate(1, 0);

  while(1)
    {
      switch(pKnob->readDirection())
      {
	    case KNOB::LEFT:
	      function.operator--();
	      break;

	    case KNOB::RIGHT:
	      function.operator++();
	      break;
      }

      if(pKnob->button.getStatus() == BUTTON::BUTTON_DOUBLE_PRESS )  { break; }
    }

  pKnob->button.clearStatus();
}
/*void
printFunctionName(LMC1992_FUNCTION & function)
{
  using namespace HMI;


}*/

void
printFunctionValueLine(uint8_t max, uint8_t min, uint8_t val)
{
  using namespace HMI;

  uint8_t i;
  uint16_t temp_val;
  float segments = (float) val/max;

  temp_val = segments / LCD_COLUMNS;

  for(i = 0; i < LCD_COLUMNS; i++)
    {
      if(i <= temp_val) { pLcd->print(0xff); }
      else 		{ pLcd->print(0x11); }
    }
}

/*-------------------------------END OF FILE--------------------------------------*/
