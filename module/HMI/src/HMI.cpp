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

#include "../../../project_config.h"

/* Private typedef ---------------------------------------------------------------*/
namespace HMI
{
  KNOB * pKnob;

  LED * pLed;

  MENU * pMenu;
  LCD * pLcd;
  CURSOR * pCursor;

  static void scrollMenuRefresh();
  static void refreshCursor(void);

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
void
HMI::init(void)
{

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

  //
  pLed->setColour(pMenu->pCurrentNode->color);
  pLed->send();
}

/**
 * @fn void HMI::scrollMenu(void)
 *
 * @details
 *
 */
void
HMI::scrollMenu(void)
{
  switch(pKnob->readDirection())
  {

    case HMI::KNOB::LEFT:	/**< moveDown */

      pCursor->operator++();

      scrollMenuRefresh();
      refreshCursor();

      break;

    case HMI::KNOB::RIGHT:	/**< moveUp */

      pCursor->operator--();

      scrollMenuRefresh();
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
void
HMI::jumpSubMenu(void)
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

	  if(pMenu->pCurrentNode->cfg_status.function) 	     { pLcd->locate(0, 15); pLcd->print(LCD_SIGN_FUNCTION_PRESENT); }
	  if(pMenu->pCurrentNode->pNext->cfg_status.function){ pLcd->locate(1, 15); pLcd->print(LCD_SIGN_FUNCTION_PRESENT); }
	  if(pMenu->pCurrentNode->cfg_status.submenu) 	     { pLcd->locate(0, 14); pLcd->print(LCD_SIGN_SUBMENU_PRESENT);  }
	  if(pMenu->pCurrentNode->pNext->cfg_status.submenu) { pLcd->locate(1, 14); pLcd->print(LCD_SIGN_SUBMENU_PRESENT);  }

	  refreshCursor();
	}
      break;
    }

}

/**
 * @fn void HMI::scrollMenuRefresh()
 *
 * @details
 *
 */
void
HMI::scrollMenuRefresh()
{

  switch(pCursor->getStatus())		/**< do not refresh screen if cursor is in scope */
  {
    case CURSOR::CURSOR_OVERFLOW:	/**< MOVE_UP */

      pLcd->clearBuffer();
      pLcd->locate(0, 1); pLcd->print(pMenu->pCurrentNode->pPrevious->pName);
      pLcd->locate(1, 1); pLcd->print(pMenu->pCurrentNode->pName);

      break;

    case CURSOR::CURSOR_UNDERFLOW:	/**< MOVE_DOWN */

      pLcd->clearBuffer();
      pLcd->locate(0, 1); pLcd->print(pMenu->pCurrentNode->pName);
      pLcd->locate(1, 1); pLcd->print(pMenu->pCurrentNode->pNext->pName);

      break;
  }

  if(pMenu->pCurrentNode->cfg_status.function) 	     { pLcd->locate(0, 15); pLcd->print(LCD_SIGN_FUNCTION_PRESENT); }
  if(pMenu->pCurrentNode->pNext->cfg_status.function){ pLcd->locate(1, 15); pLcd->print(LCD_SIGN_FUNCTION_PRESENT); }
  if(pMenu->pCurrentNode->cfg_status.submenu) 	     { pLcd->locate(0, 14); pLcd->print(LCD_SIGN_SUBMENU_PRESENT);  }
  if(pMenu->pCurrentNode->pNext->cfg_status.submenu) { pLcd->locate(1, 14); pLcd->print(LCD_SIGN_SUBMENU_PRESENT);  }

}

/**
 * @fn void HMI::refreshCursor(void)
 *
 * @details
 *
 */
void
HMI::refreshCursor(void)
{
  switch (pCursor->get())
  {
    case 0:
	pLcd->locate(0, 0); pLcd->print(LCD_CURSOR_SIGN);
        pLcd->locate(1, 0); pLcd->print(LCD_SPACE_SIGN);

        break;
    case 1:
	pLcd->locate(0, 0); pLcd->print(LCD_SPACE_SIGN);
        pLcd->locate(1, 0); pLcd->print(LCD_CURSOR_SIGN);

        break;
  }
}


using namespace HMI;

/**
 * @fn void CURSOR::init(int8_t init_min, int8_t init_max)
 *
 * @details
 *
 */
void
CURSOR::init(int8_t init_min, int8_t init_max)
{
  min = init_min;
  max = init_max;
  current_position = 0;
  status = CURSOR_IN_SCOPE;
}

/**
 * @fn CURSOR& CURSOR::operator++()
 *
 * @details
 *
 */
CURSOR&
CURSOR::operator++()
{
  current_position++;

  if(current_position > LCD_ROW_1)
    {
      current_position = LCD_ROW_1;
      status = CURSOR_OVERFLOW;		//MOVE_DOWN
    }
  else { status = CURSOR_IN_SCOPE; }

  pMenu->gotoNext();

  if(!pMenu->pCurrentNode->pParent)
    {
      pLed->setColour(pMenu->pCurrentNode->color);
      pLed->send();
    }

  return *this;
}

/**
 * @fn CURSOR& CURSOR::operator--()
 *
 * @details
 *
 */
CURSOR&
CURSOR::operator--()
{
  current_position--;

  if(current_position < LCD_ROW_0)
    {
      current_position = LCD_ROW_0;
      status = CURSOR_UNDERFLOW;	//MOVE_UP
    }
  else { status = CURSOR_IN_SCOPE; }

  pMenu->gotoPrevious();

  if(!pMenu->pCurrentNode->pParent)
    {
      pLed->setColour(pMenu->pCurrentNode->color);
      pLed->send();
    }


  return *this;
}

/**
 * @fn int8_t CURSOR::get()
 *
 * @details
 *
 */
int8_t
CURSOR::get() { return current_position; }

/**
 * @fn int8_t CURSOR::set(int8_t val)
 *
 * @details
 *
 */
int8_t
CURSOR::set(int8_t val)
{
  if(val > max || val < min) { return HMI_CURSOR_FAIL; }
  else
    {
      current_position = val;
      return HMI_CURSOR_OK;
    }
}

/**
 * @fn int8_t CURSOR::getStatus(void)
 *
 * @details
 *
 */
int8_t
CURSOR::getStatus(void) { return status; }

/*-------------------------------END OF FILE--------------------------------------*/
