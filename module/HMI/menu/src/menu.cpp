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
#define NULL 				(0)
/* Private macro -----------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------*/
NODE HMI::MENU::menu_0 = { .Name = MENU_MAIN_0,
			   .pNext = &menu_1, .pPrevious = &menu_2, .pParent = NULL, .pChild = &sub_menu_0_1, .function = NULL};
    NODE HMI::MENU::sub_menu_0_1 = { .Name = "submenu_0_1",
				     .pNext = &sub_menu_0_2, .pPrevious = &sub_menu_0_3, .pParent = &menu_0, .pChild = NULL, .function = NULL};
    NODE HMI::MENU::sub_menu_0_2 = { .Name = "submenu_0_2",
				     .pNext = &sub_menu_0_3, .pPrevious = &sub_menu_0_1, .pParent = &menu_0, .pChild = NULL, .function = NULL};
    NODE HMI::MENU::sub_menu_0_3 = { .Name = "submenu_0_3",
				     .pNext = &sub_menu_0_1, .pPrevious = &sub_menu_0_2, .pParent = &menu_0, .pChild = NULL, .function = NULL};

NODE HMI::MENU::menu_1 = { .Name = MENU_MAIN_1,
			   .pNext = &menu_2, &menu_0, NULL, &sub_menu_1_1, .function = NULL};
    NODE HMI::MENU::sub_menu_1_1 = { .Name = "submenu_1_1",
				     .pNext = &sub_menu_1_2, .pPrevious = &sub_menu_1_8, .pParent = &menu_1, .pChild = NULL, .function = NULL};
    NODE HMI::MENU::sub_menu_1_2 = { .Name = "submenu_1_2",
				     .pNext = &sub_menu_1_3, .pPrevious = &sub_menu_1_1, .pParent = &menu_1, .pChild = NULL, .function = NULL};
    NODE HMI::MENU::sub_menu_1_3 = { .Name = "submenu_1_3",
				     .pNext = &sub_menu_1_4, .pPrevious = &sub_menu_1_2, .pParent = &menu_1, .pChild = NULL, .function = NULL};
    NODE HMI::MENU::sub_menu_1_4 = { .Name = "submenu_1_4",
				     .pNext = &sub_menu_1_5, .pPrevious = &sub_menu_1_3, .pParent = &menu_1, .pChild = NULL, .function = NULL};
    NODE HMI::MENU::sub_menu_1_5 = { .Name = "submenu_1_5",
				     .pNext = &sub_menu_1_6, .pPrevious = &sub_menu_1_4, .pParent = &menu_1, .pChild = NULL, .function = NULL};
    NODE HMI::MENU::sub_menu_1_6 = { .Name = "submenu_1_6",
				      .pNext = &sub_menu_1_7, .pPrevious = &sub_menu_1_5, .pParent = &menu_1, .pChild = NULL, .function = NULL};
    NODE HMI::MENU::sub_menu_1_7 = { .Name = "submenu_1_7",
				      .pNext = &sub_menu_1_8, .pPrevious = &sub_menu_1_6, .pParent = &menu_1, .pChild = NULL, .function = NULL};
    NODE HMI::MENU::sub_menu_1_8 = { .Name = "submenu_1_8",
				     .pNext = &sub_menu_1_1, .pPrevious = &sub_menu_1_7, .pParent = &menu_1, .pChild = NULL, .function = NULL};

NODE HMI::MENU::menu_2 = {.Name = MENU_MAIN_2, .pNext = &menu_0, &menu_1, NULL, &sub_menu_2_1, .function = NULL};
    NODE HMI::MENU::sub_menu_2_1 = { .Name = "submenu_2_1",
				     .pNext = &sub_menu_2_2, .pPrevious = &sub_menu_2_2, .pParent = &menu_2, .pChild = NULL, .function = NULL};
    NODE HMI::MENU::sub_menu_2_2 = { .Name = "submenu_2_2",
				     .pNext = &sub_menu_2_1, .pPrevious = &sub_menu_2_1, .pParent = &menu_2, .pChild = NULL, .function = NULL};

/* Private function prototypes ---------------------------------------------------*/
/*
  Function:
  Input Data:
  Action:
*/

/* Private functions -------------------------------------------------------------*/

HMI::MENU::MENU(void)
{
  pCurrentNode = &menu_0;
}

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
