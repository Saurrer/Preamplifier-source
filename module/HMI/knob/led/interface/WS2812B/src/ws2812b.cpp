/** @file ws2812b.cpp
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Feb 25, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of ws2812b.cpp.
*
* @page ws2812b.cpp
* @details Detail description of ws2812b.cpp.
*
*/
/* Includes ----------------------------------------------------------------------*/

#include <stdint.h>

#include <cmsis_gcc.h>
#include <stm32f091xc.h>

#include "../inc/ws2812b.h"
#include <STM32/dma/inc/dma.h>
#include <STM32/uart/inc/uart.h>
#include <Utils/delay/inc/delay.h>

/* Private typedef ---------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------*/
#define MASK_255								0xff
#define MASK_1									0x01

#define WS2812B_MSB_Pos								(0U)
#define WS2812B_MID_Pos								(3U)
#define WS2812B_LSB_Pos								(6U)

#define WS2812B_LED_COUNT							(5U)
/* Private macro -----------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------*/

volatile uint8_t led_table[WS2812B_LED_COUNT][8];
uint8_t WS2812B_UART_BUFFER_DEFAULT_VALUE = 0x92;
/* Private function prototypes ---------------------------------------------------*/
/*
  Function:
  Input Data:
  Action:
*/

/* Private functions -------------------------------------------------------------*/
void
WS2812B::DMA_peripheral_conf(DMA_Channel_TypeDef * pDMA_Channel)
{
  /*
   * DMA2_Channel1
   */
  DMA_select_channel(DMA2, CHANNEL_1, 0b1001);
  DMA_set_data_transfer_dir(pDMA_Channel, DMA_DATA_TRANSFER_M2P);
  DMA_set_number_of_data_to_transfer(pDMA_Channel, (WS2812B_LED_COUNT * 8));

  DMA_set_memory_configuration(pDMA_Channel, (uint32_t*) led_table, 0, 1);
  DMA_set_peripheral_configuration(pDMA_Channel, (uint32_t*) &USART2->TDR, 0, 0);

  __DSB();
  __ISB();
}

void
WS2812B::DMA_mem_conf(DMA_Channel_TypeDef * pDMA_Channel)
{
  /*
   * DMA1_Channel7
   */
  //DMA_select_channel(DMA2_Channel1, CHANNEL_1, 0b1001);
  DMA_set_memory2memory_mode(pDMA_Channel);
  DMA_set_number_of_data_to_transfer(pDMA_Channel, (WS2812B_LED_COUNT * 8));

  DMA_set_memory_configuration(pDMA_Channel, (uint32_t*) led_table, 0, 1);				/**< source */
  DMA_set_peripheral_configuration(pDMA_Channel, (uint32_t*) &WS2812B_UART_BUFFER_DEFAULT_VALUE, 0, 0);	/**< destination */

  __DSB();
  __ISB();
}

void
WS2812B::Init(void)
{

  DMA_peripheral_conf(DMA2_Channel1);
  DMA_mem_conf(DMA1_Channel7);

  resetBuffer();

  UART_Init(USART2);

}

void
WS2812B::resetBuffer(void)
{
  DMA1_Channel7->CCR |= DMA_CCR_EN;		/**< reset buffer to default value */
  while(!(DMA1->ISR & DMA_ISR_TCIF7));		/**< wait till transfer is finished */

  DMA1->IFCR |= DMA_IFCR_CTCIF7;		/**< clear flag */

  DMA1_Channel7->CCR &= ~(DMA_CCR_EN);
  DMA_set_number_of_data_to_transfer(DMA1_Channel7, (WS2812B_LED_COUNT * 8));

  //while(DMA1_Channel7->CCR & DMA_CCR_EN);	/**< IMPORTANT: after successful transfer bit DMA_EN stay 1. */
}

void
WS2812B::AddDataToBuffer(volatile uint8_t (*buffer)[8], uint32_t GRB_data)
{
  uint8_t i, j, k;
  uint32_t temp_grb_data = (~GRB_data & 0x00ffffff);

  for(i = 0; i < WS2812B_LED_COUNT; i++)	/**< WS2812B_LED_COUNT - ilosc ledow */
    {
      for(j = 0, k = 24 - 1; j < 8; j++, k-=3)
        {
          buffer[i][j] |= (uint8_t) ( ((temp_grb_data >> (k - 2)) & MASK_1) << 6);
          buffer[i][j] |= (uint8_t) ( ((temp_grb_data >> (k - 1)) & MASK_1) << 3);
          buffer[i][j] |= (uint8_t) ( ((temp_grb_data >> k) & MASK_1) << 0);
        }
    }
}

void
WS2812B::send(uint32_t grb_data)
{
  AddDataToBuffer(led_table, grb_data);

  DMA2_Channel1->CCR |= DMA_CCR_EN;
  while(!(DMA2->ISR & DMA_ISR_TCIF1));		/**< wait till transfer is finished */

  DMA2->IFCR |= DMA_IFCR_CTCIF1;		/**< clear flag */
  DMA2_Channel1->CCR &= ~(DMA_CCR_EN);
  DMA_set_number_of_data_to_transfer(DMA2_Channel1, (WS2812B_LED_COUNT * 8));

  //while(DMA2_Channel1->CCR & DMA_CCR_EN);	/**< IMPORTANT: after successful transfer bit DMA_EN stay 1. */
}

void
WS2812B::reset() { delay_us(50); }

/*-------------------------------END OF FILE--------------------------------------*/
