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
#define NULL 				(0U)
#define MENU_FAIL			(0U)
#define MENU_OK				(1U)
/* Private macro -----------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------*/

HMI::NODE HMI::MENU::menu_0;
  HMI::NODE HMI::MENU::sub_menu_0_1;
  HMI::NODE HMI::MENU::sub_menu_0_2;
  HMI::NODE HMI::MENU::sub_menu_0_3;

HMI::NODE HMI::MENU::menu_1;
  HMI::NODE HMI::MENU::sub_menu_1_1;
  HMI::NODE HMI::MENU::sub_menu_1_2;
  HMI::NODE HMI::MENU::sub_menu_1_3;
  HMI::NODE HMI::MENU::sub_menu_1_4;
  HMI::NODE HMI::MENU::sub_menu_1_5;
  HMI::NODE HMI::MENU::sub_menu_1_6;
  HMI::NODE HMI::MENU::sub_menu_1_7;
  HMI::NODE HMI::MENU::sub_menu_1_8;

HMI::NODE HMI::MENU::menu_2;
  HMI::NODE HMI::MENU::sub_menu_2_1;
  HMI::NODE HMI::MENU::sub_menu_2_2;

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
  /*
   * pattern:
   *   init(char * name,
   *   	    NODE * next_address, NODE * prev_address, NODE * parent_address, NODE * child_address,
   *   	    void (*function_address)(void));
   */

  menu_0.init(MENU_0_NAME, &menu_1, &menu_2, NULL, &sub_menu_0_1, NULL, colour::colour_name::red);
  	sub_menu_0_1.init(SUB_MENU_0_1_NAME, &sub_menu_0_2, &sub_menu_0_3, &menu_0, NULL, NULL, NULL);
  	sub_menu_0_2.init(SUB_MENU_0_2_NAME, &sub_menu_0_3, &sub_menu_0_1, &menu_0, NULL, NULL, NULL);
  	sub_menu_0_3.init(SUB_MENU_0_3_NAME, &sub_menu_0_1, &sub_menu_0_2, &menu_0, NULL, NULL, NULL);

  menu_1.init(MENU_1_NAME, &menu_2, &menu_0, NULL, &sub_menu_1_1, NULL, colour::colour_name::blue);
  	sub_menu_1_1.init(SUB_MENU_1_1_NAME, &sub_menu_1_2, &sub_menu_1_8, &menu_1, NULL, &changeInput,    colour::colour_name::navy);
  	sub_menu_1_2.init(SUB_MENU_1_2_NAME, &sub_menu_1_3, &sub_menu_1_1, &menu_1, NULL, &changeBass, 	   colour::colour_name::navy);
  	sub_menu_1_3.init(SUB_MENU_1_3_NAME, &sub_menu_1_4, &sub_menu_1_2, &menu_1, NULL, &changeTreble,   colour::colour_name::navy);
  	sub_menu_1_4.init(SUB_MENU_1_4_NAME, &sub_menu_1_5, &sub_menu_1_3, &menu_1, NULL, &changeVolume,   colour::colour_name::navy);
  	sub_menu_1_5.init(SUB_MENU_1_5_NAME, &sub_menu_1_6, &sub_menu_1_4, &menu_1, NULL, &changeFader_RF, colour::colour_name::navy);
  	sub_menu_1_6.init(SUB_MENU_1_6_NAME, &sub_menu_1_7, &sub_menu_1_5, &menu_1, NULL, &changeFader_LF, colour::colour_name::navy);
  	sub_menu_1_7.init(SUB_MENU_1_7_NAME, &sub_menu_1_8, &sub_menu_1_6, &menu_1, NULL, &changeFader_RR, colour::colour_name::navy);
  	sub_menu_1_8.init(SUB_MENU_1_8_NAME, &sub_menu_1_1, &sub_menu_1_7, &menu_1, NULL, &changeFader_LR, colour::colour_name::navy);

  menu_2.init(MENU_2_NAME, &menu_0, &menu_1, NULL, &sub_menu_2_1, NULL, colour::colour_name::green);
  	sub_menu_2_1.init(SUB_MENU_2_1_NAME, &sub_menu_2_2, &sub_menu_2_2, &menu_2, NULL, &changeLCDBrightness, colour::colour_name::green_yellow);
  	sub_menu_2_2.init(SUB_MENU_2_2_NAME, &sub_menu_2_1, &sub_menu_2_1, &menu_2, NULL, NULL, NULL);

  create_menu_playlist(pPlayer);

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
  if(pCurrentNode->pNext == NULL) { return MENU_FAIL; }
  else
    {
      pCurrentNode = pCurrentNode->pNext;
      return MENU_OK;
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
  if(pCurrentNode->pPrevious == NULL) { return MENU_FAIL; }
  else
    {
      pCurrentNode = pCurrentNode->pPrevious;
      return MENU_OK;
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
  if(pCurrentNode->pParent == NULL) { return MENU_FAIL; }
  else
    {
      pCurrentNode = pCurrentNode->pParent;
      return MENU_OK;
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
  if(pCurrentNode->pChild == NULL) { return MENU_FAIL; }
  else
    {
      pCurrentNode = pCurrentNode->pChild;
      return MENU_OK;
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
  if(pCurrentNode->function == NULL) { return MENU_FAIL; }
  else
    {
      pCurrentNode->function();
      return MENU_OK;
    }
}

/**
 * @fn int8_t create_menu_playlist(uint8_t cnt)
 *
 * @details
 *
 * @return
 */

int8_t
HMI::MENU::create_menu_playlist(MUSIC_PLAYER * music_player)
{
  uint8_t i;
  NODE * new_submenu;
  NODE * last_submenu;

  if(music_player->playlist.count > PLAYLIST_CONFIG_MAX_FILES_COUNT) { return MENU_FAIL; }

  for(i = 0; i < music_player->playlist.count; i++)
    {
      new_submenu = new(NODE);
      new_submenu->pName = music_player->playlist.file_name_list[i];

      if(i == 0)
	{
	  new_submenu->pNext = new_submenu;
	  new_submenu->pParent = &menu_0;
	  menu_0.pChild = new_submenu;

	}
      else
	{
	  last_submenu->pNext = new_submenu;
	  new_submenu->pPrevious = last_submenu;
	}

      last_submenu = new_submenu;
    }

  return MENU_OK;
}


/*-------------------------------END OF FILE--------------------------------------*/
