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
* @brief brief description of encoder.h.
*
* @page encoder.h
* @details Detail description of encoder.h.
*
*/

/* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef _KNOB_H_
#define _KNOB_H_

/* Includes ----------------------------------------------------------------------*/

/* Exported define ---------------------------------------------------------------*/
#define ENCODER_PORT_A		GPIOA
#define ENCODER_PIN_A		PA0

#define ENCODER_PORT_B		GPIOA
#define ENCODER_PIN_B		PA1

/* Exported types ----------------------------------------------------------------*/

namespace HMI
{

  class KNOB
  {

  public:
    void init(TIM_TypeDef * __restrict__ pu32TIM);

  private:
    volatile uint32_t * position;

    enum direction_t : int8_t
    {
      LEFT	= 1,
      NO_MOVE	= 0,
      RIGHT 	= -1,
    };

    direction_t dir;

    uint8_t flag_context;
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
