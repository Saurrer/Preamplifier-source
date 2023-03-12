/** @file audio.cpp
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Mar 12, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of audio.cpp.
*
* @page audio.cpp
* @details Detail description of audio.cpp.
*
*/
/* Includes ----------------------------------------------------------------------*/
#include <stdint.h>

#include <cmsis_gcc.h>
#include <stm32f091xc.h>

#include "../inc/audio.h"
#include <stm32/gpio/inc/gpio.h>
#include <STM32/timer/inc/timer.h>
/* Private typedef ---------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------*/

/* Private macro -----------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------*/
/* probka audio */

uint8_t * pAudioSample = _binary_XAmbassadors_RenegadesIntro_8kHz8PWMu_raw_start;

/* Private function prototypes ---------------------------------------------------*/
/*
  Function:
  Input Data:
  Action:
*/
AUDIO * pAudio = new(AUDIO);

/* Private functions -------------------------------------------------------------*/
void AUDIO::init(void)
{
  GpioPinConfig(AUDIO_PWM_PORT, AUDIO_PWM_PIN, gpio_AF2_PP_HS);

  /*
   * f_in = 48 MHz
   * TIM 1 - slave
   * TIM15 - master (prescaler)
   */

  /* master timer configuration */
  AUDIO_TIMER_2->CR2 |= (2UL << TIM_CR2_MMS_Pos); 	/**< The update event is selected as trigger output (TRGO) */
  AUDIO_TIMER_2->DIER |= TIM_DIER_UIE;			/**< enable interrupt */
  TIM_setAutoReloadReg(AUDIO_TIMER_2, 24);		/**< get 2MHz on AUDIO_TIMER_1 input */
  //AUDIO_TIMER_2->SMCR |= (1U << TIM_SMCR_MSM_Pos) | 	/**< sync timers on signle ext event */

  /* master timer configuration */
  AUDIO_TIMER_1->SMCR |=  (0U << TIM_SMCR_TS_Pos)  |	/**< Master - ITR0 - TIM15 */
			  (1U << TIM_SMCR_MSM_Pos) |
			  (7U << TIM_SMCR_SMS_Pos) ;	/**< External Clock Mode 1 */

  /* timer default config - output */
  /*
   * PWM mode 1 - In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1 else inactive.
   * In downcounting, channel 1 is inactive (OC1REF=‘0’) as long as TIMx_CNT>TIMx_CCR1 else active (OC1REF=’1’).
   *
   */
  AUDIO_TIMER_1->CCMR1 |= (6U << TIM_CCMR1_OC1M_Pos) ;
			  //(1U << TIM_CCMR1_OC1PE_Pos);	/**< PWM mode 1 -  */

  /* polarity & channel enable */
  AUDIO_TIMER_1->CCER |= TIM_CCER_CC1E;

  AUDIO_TIMER_1->DIER |= TIM_DIER_UIE|			/**< enable interrupt */
			 TIM_DIER_CC1IE;
  TIM_setAutoReloadReg(AUDIO_TIMER_1, 250);		/**< 8 0000 Hz | 125 us at output */

  AUDIO_TIMER_1->BDTR |= TIM_BDTR_MOE;

  sample_size = (_binary_XAmbassadors_RenegadesIntro_8kHz8PWMu_raw_end - _binary_XAmbassadors_RenegadesIntro_8kHz8PWMu_raw_start)/(sizeof(uint8_t));
  index = 0;

  TIM_Enable(AUDIO_TIMER_1);
  TIM_Enable(AUDIO_TIMER_2);

  /* Global Interrupt */
  __NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);

}

void AUDIO::setSampleSize()
{
  sample_size = (_binary_XAmbassadors_RenegadesIntro_8kHz8PWMu_raw_end - _binary_XAmbassadors_RenegadesIntro_8kHz8PWMu_raw_start)/(sizeof(uint8_t));
}

void AUDIO::resetIndex()
{
  index = 0;
}

extern "C" void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{
  if(AUDIO_TIMER_1->SR & TIM_SR_UIF)
    {
      AUDIO_TIMER_1->SR &= ~TIM_SR_UIF;	/**< reset flag */

      AUDIO_TIMER_1->CCR1 = *(pAudioSample + pAudio->index++);
      pAudio->sample_size--;

      if(pAudio->sample_size == 0)
	{
	  TIM_Disable(AUDIO_TIMER_1);
	  TIM_Disable(AUDIO_TIMER_2);
	}
    }
}

/*-------------------------------END OF FILE--------------------------------------*/
