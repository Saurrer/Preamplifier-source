/** @file knob.h
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Feb 21, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of knob.h.
*
* @page knob.h
* @details Detail description of knob.h.
*
*/

/* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef _KNOB_H_
#define _KNOB_H_

/* Includes ----------------------------------------------------------------------*/

#include "../button/inc/button.h"

/* Exported define ---------------------------------------------------------------*/
#define ENCODER_PORT_A		GPIOA
#define ENCODER_PIN_A		PA0

#define ENCODER_PORT_B		GPIOA
#define ENCODER_PIN_B		PA1

#define KNOB_BUTTON_PORT	BUTTON_PORT
#define KNOB_BUTTON_PIN		BUTTON_PIN


/* Exported types ----------------------------------------------------------------*/

namespace HMI
{

  class KNOB
  {

  public:
    BUTTON button;

    enum : int8_t
    { NO_MOVE	= 0, RIGHT = -1, LEFT = 1, };

    void init(TIM_TypeDef * __restrict__ pu32TIM);	/**<  */
    int8_t readDirection(void);

  private:
    volatile uint32_t * position;			/**<  */

    int8_t direction;					/**<  */

    uint8_t flag_context;				/**<  */
  };

}  // namespace HMI

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



#endif /* _KNOB_H_ */

/*-------------------------------END OF FILE--------------------------------------*/
