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

    static NODE menu_0;
        static NODE sub_menu_0_1;
        static NODE sub_menu_0_2;
        static NODE sub_menu_0_3;

    static NODE menu_1;
	static NODE sub_menu_1_1;
        static NODE sub_menu_1_2;
        static NODE sub_menu_1_3;
        static NODE sub_menu_1_4;
        static NODE sub_menu_1_5;
        static NODE sub_menu_1_6;
        static NODE sub_menu_1_7;
        static NODE sub_menu_1_8;

    static NODE menu_2;
	static NODE sub_menu_2_1;
        static NODE sub_menu_2_2;

  };

}  // namespace HMI

/* Exported Object constants -----------------------------------------------------*/
/* Exported Object macro ---------------------------------------------------------*/
/* Exported Object functions -----------------------------------------------------*/



#endif /* _MENU_H_ */

/*-------------------------------END OF FILE--------------------------------------*/
