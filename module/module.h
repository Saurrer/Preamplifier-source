/** @file module.h
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Feb 19, 2023
* @version 	1.0.0
* @copyright 	© 2022. All Rights Reserved.
*
* @brief brief description of module.h.
*
* @page module.h
* @details Detail description of module.h.
*
*/

/* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef _MODULE_H_
#define _MODULE_H_

/* Includes ----------------------------------------------------------------------*/
#include <stdint.h>

#include <cmsis_gcc.h>
#include <stm32f091xc.h>

#include "HMI/inc/HMI.h"
#include "preamplifier/inc/preamp.h"
/* Exported define ---------------------------------------------------------------*/
/* Exported types ----------------------------------------------------------------*/
/* Exported constants ------------------------------------------------------------*/
/* Exported macro ----------------------------------------------------------------*/
/* Exported functions ----------------------------------------------------------- */
/**
* @brief Brief description of function
*/
/* Exported Object types ---------------------------------------------------------*/

namespace module
{

  extern void init(void);
}  // namespace module

/* Exported Object constants -----------------------------------------------------*/
/* Exported Object macro ---------------------------------------------------------*/
/* Exported Object functions -----------------------------------------------------*/



#endif /* _MODULE_H_ */

/*-------------------------------END OF FILE--------------------------------------*/
