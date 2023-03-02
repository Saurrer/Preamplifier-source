/** @file menu.cpp
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Mar 2, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of menu.cpp.
*
* @page menu.cpp
* @details Detail description of menu.cpp.
*
*/
/* Includes ----------------------------------------------------------------------*/
#include <stdint.h>

#include "../inc/menu.h"
/* Private typedef ---------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------*/
#define NULL 	((void *)0)
/* Private macro -----------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------*/
/* Private function prototypes ---------------------------------------------------*/
/*
  Function:
  Input Data:
  Action:
*/

/* Private functions -------------------------------------------------------------*/
int8_t
HMI::MENU::gotoNext(void)
{
  if(pCurrentNode->pNext == NULL) { return 0; }
  else
    {
      pCurrentNode = pCurrentNode->pNext;
      return 1;
    }
}

int8_t
HMI::MENU::gotoPrevious(void)
{
  if(pCurrentNode->pPrevious == NULL) { return 0; }
  else
    {
      pCurrentNode = pCurrentNode->pPrevious;
      return 1;
    }
}

int8_t
HMI::MENU::gotoParent(void)
{
  if(pCurrentNode->pParent == NULL) { return 0; }
  else
    {
      pCurrentNode = pCurrentNode->pParent;
      return 1;
    }
}

int8_t
HMI::MENU::gotoChild(void)
{
  if(pCurrentNode->pChild == NULL) { return 0; }
  else
    {
      pCurrentNode = pCurrentNode->pChild;
      return 1;
    }
}

int8_t
HMI::MENU::exeFunction(void)
{
  if(pCurrentNode->function == NULL) { return 0; }
  else { return 1; }
}

/*-------------------------------END OF FILE--------------------------------------*/
