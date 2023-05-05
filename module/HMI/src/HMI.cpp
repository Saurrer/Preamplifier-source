/** @file HMI.cpp
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Feb 21, 2023
* @version 	1.0.0
* @copyright 	© 2022. All Rights Reserved.
*
* @brief brief description of HMI.cpp.
*
* @page HMI.cpp
* @details Detail description of HMI.cpp.
*
*/
/* Includes ----------------------------------------------------------------------*/
#include <stdint.h>

#include <cmsis_gcc.h>
#include <stm32f091xc.h>

#include "../inc/HMI.h"
/* Private typedef ---------------------------------------------------------------*/
namespace HMI
{
  KNOB * pKnob;

  LED * pLed;

  MENU * pMenu;
  LCD * pLcd;
  CURSOR * pCursor;

} // namespace HMI

/* Private define ----------------------------------------------------------------*/
/* Private macro -----------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------*/
/* Private function prototypes ---------------------------------------------------*/
/*
  Function:
  Input Data:
  Action:
*/
/* Private functions -------------------------------------------------------------*/

/**
 * @fn void HMI::init(void)
 *
 * @details
 *
 */
void HMI::init(void)
{
  using namespace HMI;

  pKnob = new (KNOB);
  pKnob->init(TIM2);

  pLed = new (LED);

  pMenu = new (MENU);
  pLcd = new (LCD);
  pLcd->init();

  pCursor = new(CURSOR);
  pCursor->init(0, 2);

  pLcd->clearBuffer();
  pLcd->locate(0, 1); pLcd->print(pMenu->pCurrentNode->pName);
  pLcd->locate(1, 1); pLcd->print(pMenu->pCurrentNode->pNext->pName);
  refreshCursor();
}

/**
 * @fn void HMI::scrollMenu(void)
 *
 * @details
 *
 */
void HMI::scrollMenu(void)
{

  switch(pKnob->readDirection())
  {

    case HMI::KNOB::LEFT:	/**< moveDown */

      pCursor->operator++();

      refreshScreen();
      refreshCursor();

      break;

    case HMI::KNOB::RIGHT:	/**< moveUp */

      pCursor->operator--();

      refreshScreen();
      refreshCursor();

      break;

  }

}


/**
 * @fn void HMI::jumpSubMenu(void)
 *
 * @details
 *
 */
void HMI::jumpSubMenu(void)
{

  switch(pKnob->button.getStatus())
  {

    case HMI::BUTTON::BUTTON_SINGLE_PRESS:	/**< BUTTON_SINGLE_PRESS */

      if(pMenu->gotoChild())
	{
	  pCursor->set(0);
	  pLcd->clearBuffer();
	  pLcd->locate(0, 1); pLcd->print(pMenu->pCurrentNode->pName);
	  pLcd->locate(1, 1); pLcd->print(pMenu->pCurrentNode->pNext->pName);
	  refreshCursor();
	}

      break;

    case HMI::BUTTON::BUTTON_DOUBLE_PRESS:	/**< BUTTON_DOUBLE_PRESS */

      if(pMenu->gotoParent())
	{
	  pCursor->set(0);
	  pLcd->clearBuffer();
	  pLcd->locate(0, 1); pLcd->print(pMenu->pCurrentNode->pName);
	  pLcd->locate(1, 1); pLcd->print(pMenu->pCurrentNode->pNext->pName);

	  refreshCursor();
	}

      break;

    case HMI::BUTTON::BUTTON_LONG_PRESS:	/**< BUTTON_LONG_PRESS */

      if(pMenu->exeFunction())
	{
	  pMenu->pCurrentNode->function();

	  pCursor->set(0);
	  pLcd->clearBuffer();
	  pLcd->locate(0, 1); pLcd->print(pMenu->pCurrentNode->pName);
	  pLcd->locate(1, 1); pLcd->print(pMenu->pCurrentNode->pNext->pName);

	  refreshCursor();
	}
      break;
    }
}


void HMI::refreshScreen()
{

  switch(pCursor->getFlag())
  {
    case CURSOR::CURSOR_OVERFLOW:
      pLcd->clearBuffer();
      pLcd->locate(0, 1); pLcd->print(pMenu->pCurrentNode->pPrevious->pName);
      pLcd->locate(1, 1); pLcd->print(pMenu->pCurrentNode->pName);

      break;
    case CURSOR::CURSOR_UNDERFLOW:
      pLcd->clearBuffer();
      pLcd->locate(0, 1); pLcd->print(pMenu->pCurrentNode->pName);
      pLcd->locate(1, 1); pLcd->print(pMenu->pCurrentNode->pNext->pName);

      break;
  }
}


void HMI::refreshCursor(void)
{
  switch (pCursor->get())
  {
    case 0:
	pLcd->locate(0, 0); pLcd->print(HMI_CURSOR_SIGN);
        pLcd->locate(1, 0); pLcd->print(HMI_SPACE_SIGN);

        break;
    case 1:
	pLcd->locate(0, 0); pLcd->print(HMI_SPACE_SIGN);
        pLcd->locate(1, 0); pLcd->print(HMI_CURSOR_SIGN);

        break;

  }

}

using namespace HMI;


void CURSOR::init(int8_t init_min, int8_t init_max)
{
  min = init_min;
  max = init_max;
  current_position = 0;
  limit_status_flag = 0;
}

CURSOR& CURSOR::operator++()
{
  current_position++;

  if(current_position > 1)
    {
      current_position = 1;
      limit_status_flag = CURSOR_OVERFLOW;
    }
  else { limit_status_flag = CURSOR_IN_SCOPE; }

  pMenu->gotoNext();

  return *this;
}
CURSOR& CURSOR::operator--()
{
  current_position--;

  if(current_position < 0)
    {
      current_position = 0;
      limit_status_flag = CURSOR_UNDERFLOW;
    }
  else { limit_status_flag = CURSOR_IN_SCOPE; }

  pMenu->gotoPrevious();

  return *this;
}

int8_t CURSOR::get() { return current_position; }
int8_t CURSOR::set(int8_t val)
{
  if(val > max || val < min) { return 1; }
  else
    {
      current_position = val;
      return 0;
    }
}
int8_t CURSOR::getFlag(void) { return limit_status_flag; }

/*-------------------------------END OF FILE--------------------------------------*/
