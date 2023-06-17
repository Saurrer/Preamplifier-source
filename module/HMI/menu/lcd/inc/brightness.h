/** @file brightness.h
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Mar 18, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of brightness.h.
*
* @page brightness.h
* @details Detail description of brightness.h.
*
*/

/* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef _INC_BRIGHTNESS_H_
#define _INC_BRIGHTNESS_H_

/* Includes ----------------------------------------------------------------------*/

/* Exported define ---------------------------------------------------------------*/
#define LCD_BRIGHTNESS_PORT				GPIOB
#define LCD_BRIGHTNESS_PIN				PB1

#define LCD_BRIGHTNESS_TIMER				TIM14
#define LCD_BRIGHTNESS_RESOLUTION			UINT8_MAX

#define LCD_BRIGHTNESS_ENABLE				(6U)	/**< PWM mode 1 */
#define LCD_BRIGHTNESS_DISABLE				(4U)

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

  class BRIGHTNESS
  {

  public:

    void init(void);

    void enable();
    void disable();

    BRIGHTNESS& operator++();
    BRIGHTNESS& operator--();

    void setBrightness(uint8_t val);

  private:
    int16_t value;
    static uint8_t init_flag;

  };

}  // namespace HMI

/* Exported Object constants -----------------------------------------------------*/
/* Exported Object macro ---------------------------------------------------------*/
/* Exported Object functions -----------------------------------------------------*/



#endif /* _INC_BRIGHTNESS_H_ */

/*-------------------------------END OF FILE--------------------------------------*/
