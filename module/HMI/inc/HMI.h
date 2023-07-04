/** @file HMI.h
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Feb 21, 2023
* @version 	1.0.0
* @copyright 	© 2022. All Rights Reserved.
*
* @brief brief description of HMI.h.
*
* @page HMI.h
* @details Detail description of HMI.h.
*
*/

/* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef _HMI_H_
#define _HMI_H_

/* Includes ----------------------------------------------------------------------*/

#include "../knob/inc/knob.h"
#include "../knob/led/inc/led.h"

#include "../menu/inc/menu.h"
#include "../menu/lcd/inc/lcd.h"

/* Exported define ---------------------------------------------------------------*/
#define HMI_CURSOR_OK		(0U)
#define HMI_CURSOR_FAIL		(1U)

/* Exported types ----------------------------------------------------------------*/

namespace HMI
{

  extern KNOB * pKnob;
  extern LED * pLed;

  extern MENU * pMenu;
  extern LCD * pLcd;

  class CURSOR
  {

  public:

    enum
    {
      LCD_ROW_0		= 0,
      LCD_ROW_1		= 1,
    };

    typedef enum: int8_t
    {
      CURSOR_UNDERFLOW	= -1,
      CURSOR_IN_SCOPE	= 0,
      CURSOR_OVERFLOW	= 1,
    } cursor_status_t;

    void init(int8_t min, int8_t max);

    int8_t get();
    int8_t set(int8_t val);

    int8_t getStatus();

    CURSOR& operator++();
    CURSOR& operator--();

  private:
    int8_t min;
    int8_t max;
    int8_t current_position;
    cursor_status_t status;

  };

  extern CURSOR * pCursor;

  extern void init();
  extern void scrollMenu(void);
  extern void jumpSubMenu(void);

} // namespace HMI

/* Exported constants ------------------------------------------------------------*/
/* Exported macro ----------------------------------------------------------------*/
/* Exported functions ----------------------------------------------------------- */
/**
* @brief Brief description of function
*/

/* Exported Object types ---------------------------------------------------------*/
/* Exported Object constants -----------------------------------------------------*/
/* Exported Object macro ---------------------------------------------------------*/
/* Exported Object functions -----------------------------------------------------*/



#endif /* _HMI_H_ */

/*-------------------------------END OF FILE--------------------------------------*/
