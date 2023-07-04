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

#include "../../../inc/led.h"	/**< export LED_COUNT val */

#include "../inc/ws2812b.h"
#include <STM32/dma/inc/dma.h>
#include <STM32/uart/inc/uart.h>
#include <Utils/delay/inc/delay.h>

/* Private typedef ---------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------*/
#define MASK_255								0xff
#define MASK_1									0x01

#define WS2812B_FRAME_MSB_Pos							(0U)
#define WS2812B_FRAME_MID_Pos							(3U)
#define WS2812B_FRAME_LSB_Pos							(6U)

/* Private macro -----------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------*/

volatile uint8_t led_table[WS2812B_LED_COUNT][WS2812B_FRAME_LENGTH];
uint8_t WS2812B_UART_BUFFER_DEFAULT_VALUE = 0x92;				//default buffer value for inverted data transfer
/* Private function prototypes ---------------------------------------------------*/
/*
  Function:
  Input Data:
  Action:
*/

static void DMA_memory_conf(DMA_Channel_TypeDef * pDMA_Channel);	/**< configration for DMI source/destination */
static void DMA_peripheral_conf(DMA_Channel_TypeDef * pDMA_Channel);	/**< configration for DMI source/destination */
/* Private functions -------------------------------------------------------------*/
void
DMA_peripheral_conf(DMA_Channel_TypeDef * pDMA_Channel)
{
  /*
   * DMA2_Channel1
   */
  DMA_select_channel(DMA2, CHANNEL_1, 0b1001);
  DMA_set_data_transfer_dir(pDMA_Channel, DMA_DATA_TRANSFER_M2P);
  DMA_set_number_of_data_to_transfer(pDMA_Channel, (WS2812B_LED_COUNT * WS2812B_FRAME_LENGTH));

  DMA_set_memory_configuration(pDMA_Channel, (uint32_t*) led_table, 0, 1);		/**< source */
  DMA_set_peripheral_configuration(pDMA_Channel, (uint32_t*) &USART2->TDR, 0, 0);	/**< destination */

  DMA_enable_Tx_complete_interrupt(pDMA_Channel);

  __DSB();
  __ISB();
}

void
DMA_memory_conf(DMA_Channel_TypeDef * pDMA_Channel)
{
  /*
   * DMA1_Channel7
   */
  //DMA_select_channel(DMA2_Channel1, CHANNEL_1, 0b1001);
  DMA_set_memory2memory_mode(pDMA_Channel);								/**< M2M */
  DMA_set_number_of_data_to_transfer(pDMA_Channel, (WS2812B_LED_COUNT * WS2812B_FRAME_LENGTH));

  DMA_set_memory_configuration(pDMA_Channel, (uint32_t*) led_table, 0, 1);				/**< source */
  DMA_set_peripheral_configuration(pDMA_Channel, (uint32_t*) &WS2812B_UART_BUFFER_DEFAULT_VALUE, 0, 0);	/**< destination */

  DMA_enable_Tx_complete_interrupt(pDMA_Channel);

  __DSB();
  __ISB();
}

void
WS2812B::Init(void)
{

  DMA_peripheral_conf(DMA2_Channel1);		/**< Init dma for uart transmission */
  DMA_memory_conf(DMA1_Channel7);			/**< init dma for M2M transfer */

  __NVIC_EnableIRQ(DMA1_Ch2_3_DMA2_Ch1_2_IRQn);
  __NVIC_EnableIRQ(DMA1_Ch4_7_DMA2_Ch3_5_IRQn);

  resetFrameBuffer();

  UART_Init(USART2);
}

void
WS2812B::resetFrameBuffer(void)
{
  DMA1_Channel7->CCR |= DMA_CCR_EN;		/**< reset buffer to default value */
  while(DMA1->ISR & DMA_ISR_TCIF7);		/**< wait till transfer is finished */
}

void
WS2812B::updateFrameBufferWithData(volatile uint8_t (*buffer)[WS2812B_FRAME_LENGTH], uint32_t GRB_data)
{
  uint8_t i, j, k;
  uint32_t temp_grb_data = (~GRB_data & 0x00ffffff);	/**< negative representation of GRB data - transfered data are inverted */

  for(i = 0; i < WS2812B_LED_COUNT; i++)		/**< WS2812B_LED_COUNT - ilosc ledow */
    {
      for(j = 0, k = 24 - 1; j < WS2812B_FRAME_LENGTH; j++, k-=3)
        {
	  buffer[i][j] |= (uint8_t) ( ((temp_grb_data >> k) & MASK_1)       << WS2812B_FRAME_MSB_Pos);	// G7, G4, G1, R6, R3, R0, B5, B2
	  buffer[i][j] |= (uint8_t) ( ((temp_grb_data >> (k - 1)) & MASK_1) << WS2812B_FRAME_MID_Pos);	// G6, G3, G0, R5, R2, G7, B4, B1
	  buffer[i][j] |= (uint8_t) ( ((temp_grb_data >> (k - 2)) & MASK_1) << WS2812B_FRAME_LSB_Pos);	// G5, G2, R7, R4, R1, B6, B3, B0
        }
    }
}

void WS2812B::build(colour::RGB * rgb)
{
  uint32_t grb_data;

  grb_data = (uint32_t) (rgb->green << 16U);
  grb_data |= (uint32_t) (rgb->red  << 8U);
  grb_data |= (uint32_t) (rgb->blue << 0U);

  resetFrameBuffer();
  updateFrameBufferWithData(led_table, grb_data);
}

void
WS2812B::send()
{
  DMA2_Channel1->CCR |= DMA_CCR_EN;
  while(DMA2->ISR & DMA_ISR_TCIF1);		/**< wait till transfer is finished */
}

void
WS2812B::reset() { delay_us(50); }


extern "C" void DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler(void)
{
  if(DMA2->ISR & DMA_ISR_TCIF1)			/**< send WS2812B data */
    {
      DMA2->IFCR |= DMA_IFCR_CTCIF1;		/**< clear flag */

      USART2->ICR |= USART_ICR_TCCF;

      DMA2_Channel1->CCR &= ~(DMA_CCR_EN);
      DMA_set_number_of_data_to_transfer(DMA2_Channel1, (WS2812B_LED_COUNT * WS2812B_FRAME_LENGTH));

    }
}

extern "C" void DMA1_Ch4_7_DMA2_Ch3_5_IRQHandler(void)
{
  if(DMA1->ISR & DMA_ISR_TCIF7)
    {
      DMA1->IFCR |= DMA_IFCR_CTCIF7;		/**< clear flag */

      DMA1_Channel7->CCR &= ~(DMA_CCR_EN);
      DMA_set_number_of_data_to_transfer(DMA1_Channel7, (WS2812B_LED_COUNT * WS2812B_FRAME_LENGTH));
    }
}

/*-------------------------------END OF FILE--------------------------------------*/
