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

#include "../inc/player.h"
#include <stm32/gpio/inc/gpio.h>
#include <STM32/timer/inc/timer.h>
/* Private typedef ---------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------*/
#define TIM15_IRQHandler playMusic	/**< alias to timer interrupt function */
/* Private macro -----------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------*/
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

  TIM_Enable(AUDIO_TIMER_1);
  TIM_Enable(AUDIO_TIMER_2);

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


extern "C" void playMusic(void)
{
  if(AUDIO_TIMER_2->SR & TIM_SR_UIF)
    {
      AUDIO_TIMER_2->SR &= ~TIM_SR_UIF;	/**< reset flag */

      AUDIO_TIMER_1->CCR1 = *(pPlayer->pdata + pPlayer->file_index++);
      pPlayer->file_size--;

      if(pPlayer->file_size == 0)
	{
	  TIM_Disable(AUDIO_TIMER_1);
	  TIM_Disable(AUDIO_TIMER_2);
	}
    }
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

/*-------------------------------END OF FILE--------------------------------------*/
