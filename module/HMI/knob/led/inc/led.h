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

#include <colour/inc/colour.h>
#include "../interface/WS2812B/inc/ws2812b.h"
/* Exported define ---------------------------------------------------------------*/
#define LED_COUNT								(6U)
#define LED_TIMER_1								TIM15
#define LED_TIMER_2								TIM3
#define LED_SOFT_DELAY								(250U)

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
    { red = 0, green = 1, blue = 2 , all = 3};

    colour::RGB rgb;
    colour::HSV hsv;

    LED();
    void setColour(LED::color col, RGB_DATATYPE val);
    void setColour(colour::RGB colour_name);

    //hsv
    void setHue(uint16_t data);
    void setSaturation(uint8_t data);
    void setValue(uint8_t data);

    void reset(LED::color col);
    void send();

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
