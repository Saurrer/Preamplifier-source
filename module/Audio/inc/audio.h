/** @file audio.h
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Mar 12, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of audio.h.
*
* @page audio.h
* @details Detail description of audio.h.
*
*/

/* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef _AUDIO_H_
#define _AUDIO_H_

/* Includes ----------------------------------------------------------------------*/

/* Exported define ---------------------------------------------------------------*/
#define AUDIO_PWM_PORT		GPIOA
#define AUDIO_PWM_PIN		PA8

#define AUDIO_TIMER_1		TIM1
#define AUDIO_TIMER_2		TIM15

/* Exported types ----------------------------------------------------------------*/
extern uint8_t _binary_XAmbassadors_RenegadesIntro_8kHz8PWMu_raw_start[];
extern uint8_t _binary_XAmbassadors_RenegadesIntro_8kHz8PWMu_raw_end[];

//extern uint16_t _binary_XAmbassadors_RenegadesIntro_8kHz16PWMu_raw_start[];
//extern uint16_t _binary_XAmbassadors_RenegadesIntro_8kHz16PWMu_raw_end[];

/* Exported constants ------------------------------------------------------------*/
/* Exported macro ----------------------------------------------------------------*/
/* Exported functions ----------------------------------------------------------- */

/**
* @brief Brief description of function
*/



/* Exported Object types ---------------------------------------------------------*/
class AUDIO
{

public:

  void init(void);

  void setSampleSize();
  void resetIndex();
  uint32_t sample_size;
  volatile uint32_t index;

private:
};

extern AUDIO * pAudio;

/* Exported Object constants -----------------------------------------------------*/
/* Exported Object macro ---------------------------------------------------------*/
/* Exported Object functions -----------------------------------------------------*/



#endif /* _AUDIO_H_ */

/*-------------------------------END OF FILE--------------------------------------*/
