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
#include "../../../inc/led.h"
#include <colour/inc/colour.h>
/* Exported define ---------------------------------------------------------------*/
#define WS2812B_LED_COUNT							(LED_COUNT)
#define WS2812B_FRAME_LENGTH							(8U)
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
  void build(colour::RGB * rgb);
  void send();
  void reset();

private:
  void resetFrameBuffer();
  void updateFrameBufferWithData(volatile uint8_t (*buffer)[WS2812B_FRAME_LENGTH], uint32_t GRB_data);

  void DMA_mem_conf(DMA_Channel_TypeDef * pDMA_Channel);		/**< Line description of somevariable */
  void DMA_peripheral_conf(DMA_Channel_TypeDef * pDMA_Channel);	 	/**< Line description of somevariable */
};
/* Exported Object constants -----------------------------------------------------*/
/* Exported Object macro ---------------------------------------------------------*/
/* Exported Object functions -----------------------------------------------------*/


#endif /* _WS2812B_H_ */

/*-------------------------------END OF FILE--------------------------------------*/
