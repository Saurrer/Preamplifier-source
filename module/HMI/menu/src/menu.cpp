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

#include "../../../../project_config.h"		/**< user config file */
#include "../../../preamplifier/inc/preamp.h"
#include "../inc/functions.h"

/* Private typedef ---------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------*/
#define NULL 				(0)
/* Private macro -----------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------*/

NODE HMI::MENU::menu_0 = { .Name = MENU_0_NAME,
			   .pNext = &menu_1, .pPrevious = &menu_2, .pParent = NULL, .pChild = &sub_menu_0_1, .function = NULL};
    NODE HMI::MENU::sub_menu_0_1 = { .Name = SUB_MENU_0_1_NAME,
				     .pNext = &sub_menu_0_2, .pPrevious = &sub_menu_0_3, .pParent = &menu_0, .pChild = NULL, .function = NULL};
    NODE HMI::MENU::sub_menu_0_2 = { .Name = SUB_MENU_0_2_NAME,
				     .pNext = &sub_menu_0_3, .pPrevious = &sub_menu_0_1, .pParent = &menu_0, .pChild = NULL, .function = NULL};
    NODE HMI::MENU::sub_menu_0_3 = { .Name = SUB_MENU_0_3_NAME,
				     .pNext = &sub_menu_0_1, .pPrevious = &sub_menu_0_2, .pParent = &menu_0, .pChild = NULL, .function = NULL};

NODE HMI::MENU::menu_1 = { .Name = MENU_1_NAME,
			   .pNext = &menu_2, &menu_0, NULL, &sub_menu_1_1, .function = NULL};
    NODE HMI::MENU::sub_menu_1_1 = { .Name = SUB_MENU_1_1_NAME,
				     .pNext = &sub_menu_1_2, .pPrevious = &sub_menu_1_8, .pParent = &menu_1, .pChild = NULL, .function = NULL};
    NODE HMI::MENU::sub_menu_1_2 = { .Name = SUB_MENU_1_2_NAME,
				     .pNext = &sub_menu_1_3, .pPrevious = &sub_menu_1_1, .pParent = &menu_1, .pChild = NULL, .function = &changeBass};
    NODE HMI::MENU::sub_menu_1_3 = { .Name = SUB_MENU_1_3_NAME,
				     .pNext = &sub_menu_1_4, .pPrevious = &sub_menu_1_2, .pParent = &menu_1, .pChild = NULL, .function = &changeTreble};
    NODE HMI::MENU::sub_menu_1_4 = { .Name = SUB_MENU_1_4_NAME,
				     .pNext = &sub_menu_1_5, .pPrevious = &sub_menu_1_3, .pParent = &menu_1, .pChild = NULL, .function = &changeVolume};
    NODE HMI::MENU::sub_menu_1_5 = { .Name = SUB_MENU_1_5_NAME,
				     .pNext = &sub_menu_1_6, .pPrevious = &sub_menu_1_4, .pParent = &menu_1, .pChild = NULL, .function = &changeFader_LF};
    NODE HMI::MENU::sub_menu_1_6 = { .Name = SUB_MENU_1_6_NAME,
				      .pNext = &sub_menu_1_7, .pPrevious = &sub_menu_1_5, .pParent = &menu_1, .pChild = NULL, .function = &changeFader_RF};
    NODE HMI::MENU::sub_menu_1_7 = { .Name = SUB_MENU_1_7_NAME,
				      .pNext = &sub_menu_1_8, .pPrevious = &sub_menu_1_6, .pParent = &menu_1, .pChild = NULL, .function = &changeFader_RR};
    NODE HMI::MENU::sub_menu_1_8 = { .Name = SUB_MENU_1_8_NAME,
				     .pNext = &sub_menu_1_1, .pPrevious = &sub_menu_1_7, .pParent = &menu_1, .pChild = NULL, .function = &changeFader_LF};

NODE HMI::MENU::menu_2 = {.Name = MENU_2_NAME, .pNext = &menu_0, &menu_1, NULL, &sub_menu_2_1, .function = NULL};
    NODE HMI::MENU::sub_menu_2_1 = { .Name = MENU_2_NAME,
				     .pNext = &sub_menu_2_2, .pPrevious = &sub_menu_2_2, .pParent = &menu_2, .pChild = NULL, .function = NULL};
    NODE HMI::MENU::sub_menu_2_2 = { .Name = SUB_MENU_2_1_NAME,
				     .pNext = &sub_menu_2_1, .pPrevious = &sub_menu_2_1, .pParent = &menu_2, .pChild = NULL, .function = NULL};

/* Private function prototypes ---------------------------------------------------*/
/*
  Function:
  Input Data:
  Action:
*/

/* Private functions -------------------------------------------------------------*/

/**
 * @fn HMI::MENU::MENU(void)
 *
 * @details
 *
 *
 */
HMI::MENU::MENU(void)
{
  pCurrentNode = &menu_0;
}


/**
 * @fn int8_t HMI::MENU::gotoNext(void)
 *
 * @details
 *
 * @return
 */
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

/**
 * @fn int8_t HMI::MENU::gotoPrevious(void)
 *
 * @details
 *
 * @return
 */
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

/**
 * @fn int8_t HMI::MENU::gotoParent(void)
 *
 * @details
 *
 * @return
 */
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

/**
 * @fn int8_t HMI::MENU::gotoChild(void)
 *
 * @details
 *
 * @return
 */
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

/**
 * @fn int8_t HMI::MENU::exeFunction(void)
 *
 * @details
 *
 * @return
 */
int8_t
HMI::MENU::exeFunction(void)
{
  if(pCurrentNode->function == NULL) { return 0; }
  else { return 1; }
}

/*-------------------------------END OF FILE--------------------------------------*/
