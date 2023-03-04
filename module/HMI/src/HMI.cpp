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

    case (1):	//movedown

/*
	    pSP->increment_position();
	    if(pSP->check())
	      {
*/

		if(pMenu->gotoNext())
		  {

/*
		    refreshScreen(1);
		    pSP->set_position(1);
		    pSP->refresh();
*/

		  }

/*
	      }
	    else
	      {
		pSP->refresh();
	      }
*/

	      break;

    case (-1):	//moveup

/*
	    pSP->decrement_position();
	    if(pSP->check())
	      {
*/

		if(pMenu->gotoPrevious())
		  {

/*
		    refreshScreen(-1);
		    pSP->set_position(0);
		    pSP->refresh();
*/

		  }

/*
	      }
	    else
	      {
		pSP->refresh();
	      }
*/

	      break;

    default:
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
  pKnob->button.read();

  switch(pKnob->button.getStatus())
  {

    case HMI::BUTTON::BUTTON_SINGLE_PRESS:	/**< BUTTON_SINGLE_PRESS */
	    if(pMenu->gotoChild())
	      {
/*
		refreshScreen(-1);
		pSP->set_position(0);
		pSP->refresh();
*/

	      }
	      break;

    case HMI::BUTTON::BUTTON_DOUBLE_PRESS:	/**< BUTTON_DOUBLE_PRESS */
	    if(pMenu->gotoParent())
	      {

/*
		refreshScreen(-1);
		pSP->set_position(0);
		pSP->refresh();
*/

	      }
	      break;

    case HMI::BUTTON::BUTTON_LONG_PRESS:	/**< BUTTON_LONG_PRESS */
	    if(pMenu->exeFunction())
	      {
/*		pMenu->pCurrentNode->function();*/

	      }
	      break;
    }
}

/*-------------------------------END OF FILE--------------------------------------*/
