/** @file functions.h
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Mar 9, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of functions.h.
*
* @page functions.h
* @details Detail description of functions.h.
*
*/

/* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

/* Includes ----------------------------------------------------------------------*/
/* Exported define ---------------------------------------------------------------*/
/* Exported types ----------------------------------------------------------------*/

/* Exported constants ------------------------------------------------------------*/
/* Exported macro ----------------------------------------------------------------*/
/* Exported functions ----------------------------------------------------------- */
/**
* @brief Brief description of function
*/
namespace HMI
{
  extern void changeFader_LR(void);
  extern void changeFader_RR(void);
  extern void changeFader_LF(void);
  extern void changeFader_RF(void);
  extern void changeVolume(void);
  extern void changeTreble(void);
  extern void changeBass(void);

}  // namespace HMI

/* Exported Object types ---------------------------------------------------------*/
/* Exported Object constants -----------------------------------------------------*/
/* Exported Object macro ---------------------------------------------------------*/
/* Exported Object functions -----------------------------------------------------*/



#endif /* _FUNCTIONS_H_ */

/*-------------------------------END OF FILE--------------------------------------*/
