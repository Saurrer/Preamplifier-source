/** @file lcd.h
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Mar 2, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of lcd.h.
*
* @page lcd.h
* @details Detail description of lcd.h.
*
*/

/* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef _LCD_H_
#define _LCD_H_

/* Includes ----------------------------------------------------------------------*/
#include "../interface/HD44780/inc/HD44780.h"
#include "brightness.h"
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

  class LCD
  {

  public:

    uint8_t pointer_x, pointer_y;

    void init();

    void locate(uint8_t row, uint8_t column);
    uint8_t print(const char *s);			/**< write string to buffer */
    uint8_t print(char c);				/**< write character to buffer */

    void clearBuffer();					/**< fill buffer with space sign */
    void refreshDisplay();				/**< compare buffer with lcd data */

    BRIGHTNESS bright;
  private:
    static uint8_t init_flag;

    static char buffer_lcd_new[LCD_ROWS][LCD_COLUMNS];	/**<  */
    static char buffer_lcd_old[LCD_ROWS][LCD_COLUMNS];	/**< buffer representing currently data on lcd screen */

    void send_char(char c);
    static HD44780 interface;				/**< HD44780 communication interface */
  };

}  // namespace HMI

/* Exported Object constants -----------------------------------------------------*/
/* Exported Object macro ---------------------------------------------------------*/
/* Exported Object functions -----------------------------------------------------*/



#endif /* _LCD_H_ */

/*-------------------------------END OF FILE--------------------------------------*/
