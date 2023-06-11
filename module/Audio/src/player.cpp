/** @file player.cpp
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Mar 12, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of player.cpp.
*
* @page player.cpp
* @details Detail description of player.cpp.
*
*/
/* Includes ----------------------------------------------------------------------*/
#include <stdint.h>

#include <cmsis_gcc.h>
#include <stm32f091xc.h>
#include <core_cm0.h>

#include "../inc/player.h"
#include <stm32/gpio/inc/gpio.h>
#include <STM32/timer/inc/timer.h>

/* Private typedef ---------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------*/
#define MUSIC_PLAYER_STATUS_OK		(0)
#define MUSIC_PLAYER_STATUS_FAIL	(1)
#define NULL				(0)
/* Private macro -----------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------*/
extern uint8_t _binary_XAmbassadors_RenegadesIntro_8kHz8PWMu_raw_start[];
extern uint8_t _binary_XAmbassadors_RenegadesIntro_8kHz8PWMu_raw_end[];

//extern uint16_t _binary_XAmbassadors_RenegadesIntro_8kHz16PWMu_raw_start[];
//extern uint16_t _binary_XAmbassadors_RenegadesIntro_8kHz16PWMu_raw_end[];

WAV_H MUSIC_PLAYER::header;
//CIRCULAR_BUFFER * MUSIC_PLAYER::current_buffer;

uint8_t buffer_0[1024];
uint8_t buffer_1[1024];

CIRCULAR_BUFFER * MUSIC_PLAYER::buff_0;
CIRCULAR_BUFFER * MUSIC_PLAYER::buff_1;

/* probka audio */
uint8_t * pAudioSample = _binary_XAmbassadors_RenegadesIntro_8kHz8PWMu_raw_start;
//uint16_t * pAudioSample = _binary_XAmbassadors_RenegadesIntro_8kHz16PWMu_raw_start;

/* Private function prototypes ---------------------------------------------------*/
/*
  Function:
  Input Data:
  Action:
*/
MUSIC_PLAYER * pPlayer = new(MUSIC_PLAYER);

/* Private functions -------------------------------------------------------------*/
void
MUSIC_PLAYER::init(void)
{
  /*
   * init player's internal buffers
   */
  buff_0 = new(CIRCULAR_BUFFER);
  buff_1 = new(CIRCULAR_BUFFER);

  buff_0->init(buffer_0, 1024);
  buff_1->init(buffer_1, 1024);

  /*
   * assign buff_0 to current pointer
   */
  current_buffer = buff_0;

  GpioPinConfig(AUDIO_PWM_PORT, AUDIO_PWM_PIN, gpio_AF2_PP_HS);

  TIM_setAutoReloadReg(AUDIO_TIMER_2, 6000);		/**< 8kHz - per every 125us change data in PWM compare register */
  AUDIO_TIMER_2->DIER |= TIM_DIER_UIE;			/**< enable interrupt */

  /* timer default config - output */
  AUDIO_TIMER_1->CR1 |= (3U << TIM_CR1_CMS_Pos);	/* center aligned mode */

  /*
   * PWM mode 1 - In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1 else inactive.
   * In downcounting, channel 1 is inactive (OC1REF=‘0’) as long as TIMx_CNT>TIMx_CCR1 else active (OC1REF=’1’).
   *
   */
  AUDIO_TIMER_1->CCMR1 |= (6U << TIM_CCMR1_OC1M_Pos) |	/**< PWM mode 1 */
			  (1U << TIM_CCMR1_OC1PE_Pos);	/**< preload enable - new value is loaded to register at each update event */

  /* polarity & channel enable */
  AUDIO_TIMER_1->CCER |= TIM_CCER_CC1E;
  TIM_setAutoReloadReg(AUDIO_TIMER_1, UINT8_MAX);	/**< 185 0000 Hz | ~5.4us */

  file_size = 0;
  file_index = 0;

  //file_size = (_binary_XAmbassadors_RenegadesIntro_8kHz8PWMu_raw_end - _binary_XAmbassadors_RenegadesIntro_8kHz8PWMu_raw_start)/(sizeof(uint8_t));
  //sample_size = (_binary_XAmbassadors_RenegadesIntro_8kHz16PWMu_raw_end - _binary_XAmbassadors_RenegadesIntro_8kHz16PWMu_raw_start)/(sizeof(uint16_t));

  AUDIO_TIMER_1->BDTR |= TIM_BDTR_MOE;

  //TIM_Enable(AUDIO_TIMER_1);
  //TIM_Enable(AUDIO_TIMER_2);

  /* Global Interrupt */
  //__NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
  __NVIC_EnableIRQ(TIM15_IRQn);			/**< playMusic */

}

void
MUSIC_PLAYER::setFileSize(uint32_t val)
{
  file_size = val;
  //sample_size = (_binary_XAmbassadors_RenegadesIntro_8kHz8PWMu_raw_end - _binary_XAmbassadors_RenegadesIntro_8kHz8PWMu_raw_start)/(sizeof(uint8_t));
  //sample_size = (_binary_XAmbassadors_RenegadesIntro_8kHz16PWMu_raw_end - _binary_XAmbassadors_RenegadesIntro_8kHz16PWMu_raw_start)/(sizeof(uint16_t));
}

void
MUSIC_PLAYER::resetFileSize()
{
  file_size = 0;
}

void
MUSIC_PLAYER::setFileIndex(uint32_t val)
{
  file_index = val;
}

void
MUSIC_PLAYER::resetFileIndex()
{
  file_index = 0;
}

uint8_t
MUSIC_PLAYER::setPointer2AudioData(void * pointer2data)
{
  if(pointer2data)
    {
      pdata = (uint8_t *) pointer2data;
      return 0;
    }
  else { return 1; }
}

/*
int8_t
MUSIC_PLAYER::parseHeaderWAV(const uint8_t * pData)
{
  int i;

  if(pData == NULL) { return MUSIC_PLAYER_STATUS_FAIL; }

  for(i = 0; i < WAV_HEADER_SIZE; i++)
    {
      header.reg[i] = pData[i];
    }

  return MUSIC_PLAYER_STATUS_OK;
}
*/

int8_t
MUSIC_PLAYER::parseHeaderWAV()
{
  int i;

  if(current_buffer == NULL) { return MUSIC_PLAYER_STATUS_FAIL; }

  for(i = 0; i < WAV_HEADER_SIZE; i++)
    {
      current_buffer->get(header.reg + i);
    }

  return MUSIC_PLAYER_STATUS_OK;
}

void
MUSIC_PLAYER::changeBuffer(const buffer_index index)
{
  static buffer_index prev_index = BUFFER_0;

  /*
   * if given index is same as previous ignore change
   */
  if(index == prev_index) { return; }

  (index == BUFFER_1) ? (current_buffer = buff_1) :
			(current_buffer = buff_0) ;
}

void
MUSIC_PLAYER::playSample()
{
  resetFileIndex();
  pdata = _binary_XAmbassadors_RenegadesIntro_8kHz8PWMu_raw_start;
  file_size = (_binary_XAmbassadors_RenegadesIntro_8kHz8PWMu_raw_end - _binary_XAmbassadors_RenegadesIntro_8kHz8PWMu_raw_start)/(sizeof(uint8_t));

  TIM_Enable(AUDIO_TIMER_1);
  TIM_Enable(AUDIO_TIMER_2);
}

void
MUSIC_PLAYER::enableMusic(void)
{
  TIM_Enable(AUDIO_TIMER_1);
  TIM_Enable(AUDIO_TIMER_2);
}

void
MUSIC_PLAYER::disableMusic(void)
{
  TIM_Disable(AUDIO_TIMER_1);
  TIM_Disable(AUDIO_TIMER_2);
}


extern "C" void TIM15_IRQHandler(void)
{
  if(AUDIO_TIMER_2->SR & TIM_SR_UIF)
    {
      AUDIO_TIMER_2->SR &= ~TIM_SR_UIF;	/**< reset flag */

      AUDIO_TIMER_1->CCR1 = *(pPlayer->pdata + pPlayer->file_index++);
      pPlayer->file_size--;

      if(pPlayer->file_size == 0)
	{
	  pPlayer->disableMusic();
	}
    }
}

/*-------------------------------END OF FILE--------------------------------------*/
