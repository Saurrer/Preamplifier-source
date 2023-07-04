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

#include "../../../../project_config.h"

#include "../inc/functions.h"
#include "../../../preamplifier/inc/preamp.h"
#include "../../inc/HMI.h"

#include <stm32/timer/inc/timer.h>

/* Private typedef ---------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------*/

/* Private macro -----------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------*/

namespace HMI
{
  /* Preamplifier */
  void changeInput(void);
  void changeFader_LR(void);
  void changeFader_RR(void);
  void changeFader_LF(void);
  void changeFader_RF(void);
  void changeVolume(void);
  void changeTreble(void);
  void changeBass(void);

  void changeLCDBrightness(void);
}  // namespace HMI

/* Private function prototypes ---------------------------------------------------*/
/*
  Function:
  Input Data:
  Action:
*/
static void printFunctionValueLine(LMC1992_FUNCTION & f);

/*
 * Template function
 *
 *
  void
  HMI::function()
  {

    // some tasks before enter to loop (refresh screen etc.)

    while(1)	//loop
      {
	// some tasks

	// exit procedure
      }

    // some tasks before exit function

}
 */

/* Private functions -------------------------------------------------------------*/
void
HMI::changeInput()
{
  uint16_t i = 0;
  uint8_t len;
  uint8_t previous_val = 0;

  LMC1992_FUNCTION & function = preamp::pSource->source;

  pLcd->clearBuffer();
  pLcd->locate(0, 5); pLcd->print(preamp::FunctionNameTable[function.getAddress()]);

  pLed->setColour(pMenu->pCurrentNode->color);		/**< set colour of front panel */
  pLed->send();

  TIM_setAutoReloadReg(LED_TIMER_2, 100);

  TIM_Enable(LED_TIMER_2);				/**< turn on timers for pulse colour effect */
  TIM_Enable(LED_TIMER_1);

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

      if(!(i % LED_SOFT_DELAY))		/**<this function cannot be executed too fast cause of error on RGB leds - needed soft delay */
	{
	  pLed->setValue(LED_TIMER_2->CNT);
	  pLed->send();
	}

      pLcd->locate(1, 0);		/**< set lcd pointer at the beginning */
      len = pLcd->print(preamp::FunctionSourceTable[function.getValue()]);
      len = LCD_COLUMNS - len;
      while(len--)
	{
	  pLcd->print(LCD_SIGN_VOID);
	}

      previous_val = function.getValue();

      i++;

      if(pKnob->button.getStatus() == BUTTON::BUTTON_DOUBLE_PRESS )  { break; }
    }

  pLed->setColour(pMenu->pCurrentNode->pParent->color);		/**< bring back parent's node color to front panel */
  pLed->send();

  TIM_Disable(LED_TIMER_2);		/**< turn off timers */
  TIM_Disable(LED_TIMER_1);

  pKnob->button.clearStatus();
}

void
HMI::changeFader_LR()
{
  uint16_t i = 0;

  LMC1992_FUNCTION & function = preamp::pSource->fd_left_rear;

  pLcd->clearBuffer();
  pLcd->locate(0, 5); pLcd->print(preamp::FunctionNameTable[function.getAddress()]);

  pLed->setColour(pMenu->pCurrentNode->color);		/**< set colour of front panel */
  pLed->send();

  TIM_setAutoReloadReg(LED_TIMER_2, 100);

  TIM_Enable(LED_TIMER_2);				/**< turn on timers for pulse colour effect */
  TIM_Enable(LED_TIMER_1);

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

      if(!(i % LED_SOFT_DELAY))		/**<this function cannot be executed too fast cause of error on RGB leds - needed soft delay */
	{
	  pLed->setValue(LED_TIMER_2->CNT);
	  pLed->send();
	}

      pLcd->locate(1, 0);		/**< set lcd pointer at the beginning */
      printFunctionValueLine(function);

      i++;

      if(pKnob->button.getStatus() == BUTTON::BUTTON_DOUBLE_PRESS )  { break; }
    }

  pLed->setColour(pMenu->pCurrentNode->pParent->color);		/**< bring back parent's node color to front panel */
  pLed->send();

  TIM_Disable(LED_TIMER_2);		/**< turn off timers */
  TIM_Disable(LED_TIMER_1);

  pKnob->button.clearStatus();
}

void
HMI::changeFader_RR()
{
  uint16_t i = 0;

  LMC1992_FUNCTION & function = preamp::pSource->fd_right_rear;

  pLcd->clearBuffer();
  pLcd->locate(0, 5); pLcd->print(preamp::FunctionNameTable[function.getAddress()]);

  pLed->setColour(pMenu->pCurrentNode->color);		/**< set colour of front panel */
  pLed->send();

  TIM_setAutoReloadReg(LED_TIMER_2, 100);

  TIM_Enable(LED_TIMER_2);				/**< turn on timers for pulse colour effect */
  TIM_Enable(LED_TIMER_1);

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

      if(!(i % LED_SOFT_DELAY))		/**<this function cannot be executed too fast cause of error on RGB leds - needed soft delay */
	{
	  pLed->setValue(LED_TIMER_2->CNT);
	  pLed->send();
	}

      pLcd->locate(1, 0);		/**< set lcd pointer at the beginning */
      printFunctionValueLine(function);

      i++;

      if(pKnob->button.getStatus() == BUTTON::BUTTON_DOUBLE_PRESS )  { break; }
    }

  pLed->setColour(pMenu->pCurrentNode->pParent->color);		/**< bring back parent's node color to front panel */
  pLed->send();

  TIM_Disable(LED_TIMER_2);		/**< turn off timers */
  TIM_Disable(LED_TIMER_1);

  pKnob->button.clearStatus();
}

void
HMI::changeFader_LF()
{
  uint16_t i = 0;

  LMC1992_FUNCTION & function = preamp::pSource->fd_left_front;

  pLcd->clearBuffer();
  pLcd->locate(0, 5); pLcd->print(preamp::FunctionNameTable[function.getAddress()]);

  pLed->setColour(pMenu->pCurrentNode->color);		/**< set colour of front panel */
  pLed->send();

  TIM_setAutoReloadReg(LED_TIMER_2, 100);

  TIM_Enable(LED_TIMER_2);				/**< turn on timers for pulse colour effect */
  TIM_Enable(LED_TIMER_1);

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

      if(!(i % LED_SOFT_DELAY))		/**<this function cannot be executed too fast cause of error on RGB leds - needed soft delay */
	{
	  pLed->setValue(LED_TIMER_2->CNT);
	  pLed->send();
	}

      pLcd->locate(1, 0);		/**< set lcd pointer at the beginning */
      printFunctionValueLine(function);

      i++;

      if(pKnob->button.getStatus() == BUTTON::BUTTON_DOUBLE_PRESS )  { break; }
    }

  pLed->setColour(pMenu->pCurrentNode->pParent->color);		/**< bring back parent's node color to front panel */
  pLed->send();

  TIM_Disable(LED_TIMER_2);		/**< turn off timers */
  TIM_Disable(LED_TIMER_1);

  pKnob->button.clearStatus();
}

void
HMI::changeFader_RF()
{
  uint16_t i = 0;

  LMC1992_FUNCTION & function = preamp::pSource->fd_right_front;

  pLcd->clearBuffer();
  pLcd->locate(0, 5); pLcd->print(preamp::FunctionNameTable[function.getAddress()]);

  pLed->setColour(pMenu->pCurrentNode->color);		/**< set colour of front panel */
  pLed->send();

  TIM_setAutoReloadReg(LED_TIMER_2, 100);

  TIM_Enable(LED_TIMER_2);				/**< turn on timers for pulse colour effect */
  TIM_Enable(LED_TIMER_1);

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

      if(!(i % LED_SOFT_DELAY))		/**<this function cannot be executed too fast cause of error on RGB leds - needed soft delay */
	{
	  pLed->setValue(LED_TIMER_2->CNT);
	  pLed->send();
	}

      pLcd->locate(1, 0);		/**< set lcd pointer at the beginning */
      printFunctionValueLine(function);

      i++;

      if(pKnob->button.getStatus() == BUTTON::BUTTON_DOUBLE_PRESS )  { break; }
    }

  pLed->setColour(pMenu->pCurrentNode->pParent->color);		/**< bring back parent's node color to front panel */
  pLed->send();

  TIM_Disable(LED_TIMER_2);		/**< turn off timers */
  TIM_Disable(LED_TIMER_1);

  pKnob->button.clearStatus();
}

void
HMI::changeVolume()
{
  uint16_t i = 0;

  LMC1992_FUNCTION & function = preamp::pSource->volume;

  pLcd->clearBuffer();
  pLcd->locate(0, 5); pLcd->print(preamp::FunctionNameTable[function.getAddress()]);

  pLed->setColour(pMenu->pCurrentNode->color);		/**< set colour of front panel */
  pLed->send();

  TIM_setAutoReloadReg(LED_TIMER_2, 100);

  TIM_Enable(LED_TIMER_2);				/**< turn on timers for pulse colour effect */
  TIM_Enable(LED_TIMER_1);

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

      if(!(i % LED_SOFT_DELAY))		/**<this function cannot be executed too fast cause of error on RGB leds - needed soft delay */
	{
	  pLed->setValue(LED_TIMER_2->CNT);
	  pLed->send();
	}

      pLcd->locate(1, 0);		/**< set lcd pointer at the beginning */
      printFunctionValueLine(function);

      i++;

      if(pKnob->button.getStatus() == BUTTON::BUTTON_DOUBLE_PRESS )  { break; } 	/**< check exit condition */
    }

  pLed->setColour(pMenu->pCurrentNode->pParent->color);		/**< bring back parent's node color to front panel */
  pLed->send();

  TIM_Disable(LED_TIMER_2);		/**< turn off timers */
  TIM_Disable(LED_TIMER_1);


  pKnob->button.clearStatus();
}

void
HMI::changeTreble()
{
  uint16_t i = 0;

  LMC1992_FUNCTION & function = preamp::pSource->treble;

  pLcd->clearBuffer();
  pLcd->locate(0, 5); pLcd->print(preamp::FunctionNameTable[function.getAddress()]);

  pLed->setColour(pMenu->pCurrentNode->color);		/**< set colour of front panel */
  pLed->send();

  TIM_setAutoReloadReg(LED_TIMER_2, 100);

  TIM_Enable(LED_TIMER_2);				/**< turn on timers for pulse colour effect */
  TIM_Enable(LED_TIMER_1);

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

      if(!(i % LED_SOFT_DELAY))		/**<this function cannot be executed too fast cause of error on RGB leds - needed soft delay */
	{
	  pLed->setValue(LED_TIMER_2->CNT);
	  pLed->send();
	}

      pLcd->locate(1, 0);		/**< set lcd pointer at the beginning */
      printFunctionValueLine(function);

      i++;

      if(pKnob->button.getStatus() == BUTTON::BUTTON_DOUBLE_PRESS )  { break; }
    }


  pLed->setColour(pMenu->pCurrentNode->pParent->color);		/**< bring back parent's node color to front panel */
  pLed->send();

  TIM_Disable(LED_TIMER_2);		/**< turn off timers */
  TIM_Disable(LED_TIMER_1);

  pKnob->button.clearStatus();
}


void
HMI::changeBass()
{
  uint16_t i = 0;

  LMC1992_FUNCTION & function = preamp::pSource->bass;

  pLcd->clearBuffer();
  pLcd->locate(0, 5); pLcd->print(preamp::FunctionNameTable[function.getAddress()]);

  pLed->setColour(pMenu->pCurrentNode->color);		/**< set colour of front panel */
  pLed->send();

  TIM_setAutoReloadReg(LED_TIMER_2, 100);

  TIM_Enable(LED_TIMER_2);				/**< turn on timers for pulse colour effect */
  TIM_Enable(LED_TIMER_1);

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

      if(!(i % LED_SOFT_DELAY))		/**<this function cannot be executed too fast cause of error on RGB leds - needed soft delay */
	{
	  pLed->setValue(LED_TIMER_2->CNT);
	  pLed->send();
	}


      pLcd->locate(1, 0);		/**< set lcd pointer at the beginning */
      printFunctionValueLine(function);

      i++;

      if(pKnob->button.getStatus() == BUTTON::BUTTON_DOUBLE_PRESS )  { break; }
    }


  pLed->setColour(pMenu->pCurrentNode->pParent->color);		/**< bring back parent's node color to front panel */
  pLed->send();

  TIM_Disable(LED_TIMER_2);		/**< turn off timers */
  TIM_Disable(LED_TIMER_1);

  pKnob->button.clearStatus();
}


void
HMI::changeLCDBrightness()
{
  uint16_t i = 0;

  pLcd->clearBuffer();
  pLcd->locate(0, 3); pLcd->print(SUB_MENU_2_1_NAME);
  pLcd->locate(1, 0);

  pLed->setColour(pMenu->pCurrentNode->color);		/**< set colour of front panel */
  pLed->send();

  TIM_setAutoReloadReg(LED_TIMER_2, 100);

  TIM_Enable(LED_TIMER_2);				/**< turn on timers for pulse colour effect */
  TIM_Enable(LED_TIMER_1);

  while(1)
    {
      switch(pKnob->readDirection())
      {
	case KNOB::LEFT:
	  pLcd->bright.operator--(); break;

	case KNOB::RIGHT:
	  pLcd->bright.operator++(); break;
      }

      if(!(i % LED_SOFT_DELAY))		/**<this function cannot be executed too fast cause of error on RGB leds - needed soft delay */
	{
	  pLed->setValue(LED_TIMER_2->CNT);
	  pLed->send();
	}

      i++;

      if(pKnob->button.getStatus() == BUTTON::BUTTON_DOUBLE_PRESS )  { break; }
    }

  pLed->setColour(pMenu->pCurrentNode->pParent->color);		/**< bring back parent's node color to front panel */
  pLed->send();

  TIM_Disable(LED_TIMER_2);		/**< turn off timers */
  TIM_Disable(LED_TIMER_1);

  pKnob->button.clearStatus();
}


void
printFunctionValueLine(LMC1992_FUNCTION & f)
{
  using namespace HMI;

  uint8_t i;
  uint16_t temp_val;
  float segments = (float) f.getValue()/f.getMax();

  temp_val = segments * LCD_COLUMNS;

  for(i = 0; i < LCD_COLUMNS; i++)
    {
      if(i <= temp_val) { pLcd->print(LCD_SIGN_FILL); }
      else 		{ pLcd->print(LCD_SIGN_VOID); }
    }
}

/*-------------------------------END OF FILE--------------------------------------*/
