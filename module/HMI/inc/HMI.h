/** @file HMI.h
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Feb 21, 2023
* @version 	1.0.0
* @copyright 	© 2022. All Rights Reserved.
*
* @brief brief description of HMI.h.
*
* @page HMI.h
* @details Detail description of HMI.h.
*
*/

/* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef _HMI_H_
#define _HMI_H_

/* Includes ----------------------------------------------------------------------*/

#include "../knob/inc/knob.h"
#include "../knob/led/inc/led.h"

#include "../menu/inc/menu.h"
#include "../menu/lcd/inc/lcd.h"

/* Exported define ---------------------------------------------------------------*/
/* Exported types ----------------------------------------------------------------*/

namespace HMI
{

  extern KNOB * pKnob ;
  extern LED * pLed;

  extern MENU * pMenu;
  extern LCD * pLcd;

  extern void init();

} // namespace HMI

/* Exported constants ------------------------------------------------------------*/
/* Exported macro ----------------------------------------------------------------*/
/* Exported functions ----------------------------------------------------------- */
/**
* @brief Brief description of function
*/

/* Exported Object types ---------------------------------------------------------*/
/* Exported Object constants -----------------------------------------------------*/
/* Exported Object macro ---------------------------------------------------------*/
/* Exported Object functions -----------------------------------------------------*/



#endif /* _HMI_H_ */

/*-------------------------------END OF FILE--------------------------------------*/
