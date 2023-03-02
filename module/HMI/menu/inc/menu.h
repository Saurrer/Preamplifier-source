/** @file menu.h
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Mar 2, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of menu.h.
*
* @page menu.h
* @details Detail description of menu.h.
*
*/

/* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef _MENU_H_
#define _MENU_H_

/* Includes ----------------------------------------------------------------------*/
#include "node.h"
/* Exported define ---------------------------------------------------------------*/
#define MENU_MAIN_0		"menu_0"
#define MENU_MAIN_1		"menu_1"
#define MENU_MAIN_2		"menu_2"
/* Exported types ----------------------------------------------------------------*/
/* Exported constants ------------------------------------------------------------*/
/* Exported macro ----------------------------------------------------------------*/
/* Exported functions ----------------------------------------------------------- */
/**
* @brief Brief description of function
*/

/* Exported Object types ---------------------------------------------------------*/
namespace HMI
{

  class MENU
  {

  public:
    NODE * pCurrentNode;

    MENU();

    int8_t gotoNext(void);
    int8_t gotoPrevious(void);
    int8_t gotoParent(void);
    int8_t gotoChild(void);

    int8_t exeFunction(void);

  private:
    NODE menu_0 = {.Name = MENU_MAIN_0, .pNext = &menu_1, .pPrevious = &menu_2, .pParent = NULL, .pChild = &sub_menu_0_1, .function = NULL};
    //bez sensu robic node dla kazdego utworu - ToDo - trzeba sie zastanowic jak to rozwiazac
        NODE sub_menu_0_1 = {.Name = "submenu_0_1",
  			   .pNext = &sub_menu_0_2, .pPrevious = &sub_menu_0_3, .pParent = &menu_0, .pChild = NULL, .function = NULL};
        NODE sub_menu_0_2 = {.Name = "submenu_0_2",
  			   .pNext = &sub_menu_0_3, .pPrevious = &sub_menu_0_1, .pParent = &menu_0, .pChild = NULL, .function = NULL};
        NODE sub_menu_0_3 = {.Name = "submenu_0_3",
  			   .pNext = &sub_menu_0_1, .pPrevious = &sub_menu_0_2, .pParent = &menu_0, .pChild = NULL, .function = NULL};


    NODE menu_1 = {.Name = (const char *) MENU_MAIN_1, .pNext = &menu_2, &menu_0, NULL, &sub_menu_1_1, .function = NULL};
        NODE sub_menu_1_1 = {.Name = "submenu_1_1",
  			   .pNext = &sub_menu_1_2, .pPrevious = &sub_menu_1_8, .pParent = &menu_1, .pChild = NULL, .function = NULL};
        NODE sub_menu_1_2 = {.Name = "submenu_1_2",
  			   .pNext = &sub_menu_1_3, .pPrevious = &sub_menu_1_1, .pParent = &menu_1, .pChild = NULL, .function = &changeVolume};
        NODE sub_menu_1_3 = {.Name = "submenu_1_3",
  			   .pNext = &sub_menu_1_4, .pPrevious = &sub_menu_1_2, .pParent = &menu_1, .pChild = NULL, .function = &changeBass};
        NODE sub_menu_1_4 = {.Name = "submenu_1_4",
  			   .pNext = &sub_menu_1_5, .pPrevious = &sub_menu_1_3, .pParent = &menu_1, .pChild = NULL, .function = &changeTreble};
        NODE sub_menu_1_5 = {.Name = "submenu_1_5",
  			   .pNext = &sub_menu_1_6, .pPrevious = &sub_menu_1_4, .pParent = &menu_1, .pChild = NULL, .function = &changeFader_FR};
        NODE sub_menu_1_6 = {.Name = "submenu_1_6",
  			   .pNext = &sub_menu_1_7, .pPrevious = &sub_menu_1_5, .pParent = &menu_1, .pChild = NULL, .function = &changeFader_FL};
        NODE sub_menu_1_7 = {.Name = "submenu_1_7",
  			   .pNext = &sub_menu_1_8, .pPrevious = &sub_menu_1_6, .pParent = &menu_1, .pChild = NULL, .function = &changeFader_RR};
        NODE sub_menu_1_8 = {.Name = "submenu_1_8",
  			   .pNext = &sub_menu_1_1, .pPrevious = &sub_menu_1_7, .pParent = &menu_1, .pChild = NULL, .function = &changeFader_RL};


    NODE menu_2 = {.Name = (const char *) MENU_MAIN_2, .pNext = &menu_0, &menu_1, NULL, &sub_menu_2_1, .function = NULL};
        NODE sub_menu_2_1 = {.Name = "submenu_2_1",
  			   .pNext = &sub_menu_2_2, .pPrevious = &sub_menu_2_2, .pParent = &menu_2, .pChild = NULL, .function = NULL};
        NODE sub_menu_2_2 = {.Name = "submenu_2_2",
  			   .pNext = &sub_menu_2_1, .pPrevious = &sub_menu_2_1, .pParent = &menu_2, .pChild = NULL, .function = NULL};


  };

}  // namespace HMI

/* Exported Object constants -----------------------------------------------------*/
/* Exported Object macro ---------------------------------------------------------*/
/* Exported Object functions -----------------------------------------------------*/



#endif /* _MENU_H_ */

/*-------------------------------END OF FILE--------------------------------------*/
