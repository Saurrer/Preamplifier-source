/** @file lcd.cpp
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Mar 2, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of lcd.cpp.
*
* @page lcd.cpp
* @details Detail description of lcd.cpp.
*
*/
/* Includes ----------------------------------------------------------------------*/
#include <stdint.h>

#include "../inc/lcd.h"
#include <Utils/delay/inc/delay.h>
/* Private typedef ---------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------*/
#define LCD_FIRST_TIME_INIT_INTERFACE		(0U)

/* Private macro -----------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------*/
uint8_t HMI::LCD::init_flag {0};

char HMI::LCD::buffer_lcd_new[LCD_ROWS][LCD_COLUMNS];
char HMI::LCD::buffer_lcd_old[LCD_ROWS][LCD_COLUMNS];	/**< buffer representing currently data on lcd screen */

HD44780 HMI::LCD::interface;				/**< HD44780 communication interface */

/* Private function prototypes ---------------------------------------------------*/
/*
  Function:
  Input Data:
  Action:
*/

/* Private functions -------------------------------------------------------------*/

/**
 * @fn void HMI::LCD::init(void)
 *
 * @details
 *
 */
void HMI::LCD::init(void)
{
  if(init_flag == LCD_FIRST_TIME_INIT_INTERFACE)
    {
      interface.init();
      interface.cls();

      bright.init();

      init_flag = 1;
    }

  clearBuffer();

  locate(0, 1);
  print("Init");
  locate(1, 1);
  print("Preamplifier");

  refreshDisplay();

  delay_ms(10000);
}

/**
 * @fn void HMI::LCD::locate(uint8_t x, uint8_t y)
 *
 * @details
 *
 * @param[in] x operand 1
 * @param[in] y operand 2
 *
 */
void HMI::LCD::locate(uint8_t x, uint8_t y)
{
  pointer_x = x;
  pointer_y = y;
}

/**
 * @fn void HMI::LCD::clear_buffer(void)
 *
 * @details
 *
 */
void HMI::LCD::clearBuffer(void)
{
  uint8_t i, j;

  for(i = 0; i < LCD_ROWS; i++)
    {
      for(j = 0; j < LCD_COLUMNS; j++)
	{
	  buffer_lcd_new[i][j] = ' ';
	}
    }

  pointer_x = pointer_y = 0;
}

/**
 * @fn void HMI::LCD::print(const char *s)
 *
 * @details
 *
 * @param[in] x operand 1
 *
 */
void HMI::LCD::print(const char * s)
{
  while(*s)
    {
      send_char(*s++);
    }
}

/**
 * @fn void HMI::LCD::print(uint8_t data)
 *
 * @details
 *
 * @param[in] x operand 1
 *
 */
void HMI::LCD::print(char c)
{
  while(c)
    {
      send_char(c);
    }
}

/**
 * @fn void HMI::LCD::clear_buffer(void)
 *
 * @details
 *
 */
void HMI::LCD::refreshDisplay(void)
{
  static uint8_t locate_flag = 0;
  uint8_t i, j;

  for(i = 0; i < LCD_ROWS; i++)
    {
      interface.locate(i,0);

      for(j = 0; j < LCD_COLUMNS; j++)
	{
	  if(buffer_lcd_new[i][j] != buffer_lcd_old[i][j])	/**< found diff between new_buffer and buffer representing lcd screen */
	    {
	      if(!locate_flag) { interface.locate(i, j); }	/**< navigate cursor at difference */

	      interface.send_data(buffer_lcd_new[i][j]);	/**< send new data to lcd screen */
	      buffer_lcd_old[i][j] = buffer_lcd_new[i][j];	/**< update lcd buffer */

	      locate_flag = 1;
	    }
	  else	/**< no diff found between new_buffer and buffer representing lcd screen */
	    {
	      locate_flag = 0;
	    }
	}
    }

}

/**
 * @fn void HMI::LCD::send_char(char c)
 *
 * @details
 *
 * @param[in] x operand 1
 *
 */
void HMI::LCD::send_char(char c)
{
  if((pointer_x < LCD_ROWS) && (pointer_y < LCD_COLUMNS) )
    {
      buffer_lcd_new[pointer_x][pointer_y] = c;
      pointer_y++;

      if(pointer_y == LCD_COLUMNS)
	{
	  pointer_y = 0;
	  pointer_x++;

	  if(pointer_x == LCD_ROWS) { pointer_x = 0; }
	}
    }
}

/*-------------------------------END OF FILE--------------------------------------*/
