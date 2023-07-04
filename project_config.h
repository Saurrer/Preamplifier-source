/** @file project_config.h
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Feb 28, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of project_config.h.
*
* @page config.h
* @details Detail description of project_config.h.
*
*/

/* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef _PROJECT_CONFIG_H_
#define _PROJECT_CONFIG_H_

/* Exported define ---------------------------------------------------------------*/
#define CPU_FREQUENCY				(48000000U)
#define PERIPHERAL_FREQUENCY			(24000000U)

/* MENU 0 names */
#define MENU_0_NAME				"Music"
#define SUB_MENU_0_1_NAME			"submenu_0_1"
#define SUB_MENU_0_2_NAME			"submenu_0_2"
#define SUB_MENU_0_3_NAME			"submenu_0_3"

/* MENU 1 names */
#define MENU_1_NAME				"Preamplifier"
#define SUB_MENU_1_1_NAME			"Input"
#define SUB_MENU_1_2_NAME			"Bass"
#define SUB_MENU_1_3_NAME			"Treble"
#define SUB_MENU_1_4_NAME			"Volume"
#define SUB_MENU_1_5_NAME			"Fader RF"
#define SUB_MENU_1_6_NAME			"Fader LF"
#define SUB_MENU_1_7_NAME			"Fader RR"
#define SUB_MENU_1_8_NAME			"Fader LR"

/* MENU 2 names */
#define MENU_2_NAME				"Settings"
#define SUB_MENU_2_1_NAME			"Brightness"
#define SUB_MENU_2_2_NAME			"submenu_2_2"

#define LCD_SIGN_FILL				0xff
#define LCD_SIGN_VOID				0x11
#define LCD_CURSOR_SIGN 			">"
#define LCD_SPACE_SIGN 				" "
#define LCD_SIGN_SUBMENU_PRESENT		0x3E
#define LCD_SIGN_FUNCTION_PRESENT		0xE0

#endif /* _PROJECT_CONFIG_H_ */

/*-------------------------------END OF FILE--------------------------------------*/
