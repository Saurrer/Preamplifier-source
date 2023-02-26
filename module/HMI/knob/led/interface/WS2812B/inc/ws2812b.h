/** @file ws2812b.h
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Feb 25, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of ws2812b.h.
*
* @page ws2812b.h
* @details Detail description of ws2812b.h.
*
*/

/* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef _WS2812B_H_
#define _WS2812B_H_

/* Includes ----------------------------------------------------------------------*/

/* Exported define ---------------------------------------------------------------*/
/* Exported types ----------------------------------------------------------------*/
/* Exported constants ------------------------------------------------------------*/
/* Exported macro ----------------------------------------------------------------*/
/* Exported functions ----------------------------------------------------------- */
/**
* @brief Brief description of function
*/

/* Exported Object types ---------------------------------------------------------*/
class WS2812B
{

public:
  void Init();
  void send(uint32_t grb_data);
  void reset();

private:
  static int8_t init_flag ;					 	/**< Line description of somevariable */
  void resetBuffer();
  void AddDataToBuffer(volatile uint8_t (*buffer)[8], uint32_t GRB_data);

  void DMA_mem_conf(DMA_Channel_TypeDef * pDMA_Channel);		/**< Line description of somevariable */
  void DMA_peripheral_conf(DMA_Channel_TypeDef * pDMA_Channel);	 	/**< Line description of somevariable */
};
/* Exported Object constants -----------------------------------------------------*/
/* Exported Object macro ---------------------------------------------------------*/
/* Exported Object functions -----------------------------------------------------*/


#endif /* _WS2812B_H_ */

/*-------------------------------END OF FILE--------------------------------------*/
