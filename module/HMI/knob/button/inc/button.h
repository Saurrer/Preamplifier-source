/** @file button.h
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Feb 22, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of button.h.
*
* @page button.h
* @details Detail description of button.h.
*
*/

/* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef _BUTTON_H_
#define _BUTTON_H_

/* Includes ----------------------------------------------------------------------*/

/* Exported define ---------------------------------------------------------------*/

#define BUTTON_PORT		GPIOA
#define BUTTON_PIN		PA3
/* Exported types ----------------------------------------------------------------*/
class BUTTON //switch
{

public:

  enum : uint8_t
  {
    BUTTON_OFF 			= 0,
    BUTTON_ON			= 1,
    BUTTON_SINGLE_PRESS 	= 2,
    BUTTON_DOUBLE_PRESS 	= 3,
    BUTTON_LONG_PRESS		= 4,
    BUTTON_NOT_INITIALIZED	= 255,
  };

  BUTTON(GPIO_TypeDef * const __restrict button_port, GpioPin button_pin);
  uint8_t getStatus(void);
  void read(void);

private:
  uint8_t status;		/**< Line description of somevariable */
  uint8_t keylock {0};		/**< useb by read function */

};

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



#endif /* _BUTTON_H_ */

/*-------------------------------END OF FILE--------------------------------------*/
