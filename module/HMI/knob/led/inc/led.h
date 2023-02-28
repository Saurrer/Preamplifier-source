/** @file led.h
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Feb 28, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of led.h.
*
* @page led.h
* @details Detail description of led.h.
*
*/

/* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef _LED_H_
#define _LED_H_

/* Includes ----------------------------------------------------------------------*/

#include "../colour/inc/colour.h"
#include "../interface/WS2812B/inc/ws2812b.h"
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

  class LED
  {

  public:

    enum class color : uint8_t
    { red	= 0, green = 1, blue = 2 };

    colour::RGB rgb;

    LED();
    void setColour(LED::color col, RGB_DATATYPE val);
    void reset(LED::color col);

  private:
    static int8_t init_flag;
    void reset_init_flag() { init_flag = 0; }

    static WS2812B interface;

  };

}  // namespace HMI

/* Exported Object constants -----------------------------------------------------*/
/* Exported Object macro ---------------------------------------------------------*/
/* Exported Object functions -----------------------------------------------------*/



#endif /* _LED_H_ */

/*-------------------------------END OF FILE--------------------------------------*/
