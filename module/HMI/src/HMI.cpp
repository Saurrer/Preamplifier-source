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
void HMI::init()
{
  using namespace HMI;

  pKnob = new (KNOB);
  pKnob->init(TIM2);

  pLed = new (LED);

  pMenu = new (MENU);
  pLcd = new (LCD);
  pLcd->init();
}

/*-------------------------------END OF FILE--------------------------------------*/
