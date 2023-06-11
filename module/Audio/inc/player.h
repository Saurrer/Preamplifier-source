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
#include "playlist.h"

#include "parser_wav.h"
#include <Utils/circular_buffer/inc/circular_buffer.h>
/* Exported define ---------------------------------------------------------------*/
#define AUDIO_PWM_PORT			GPIOA
#define AUDIO_PWM_PIN			PA8

#define AUDIO_TIMER_1			TIM1
#define AUDIO_TIMER_2			TIM17

#define MUSIC_PLAYER_BUFFER_SIZE	(2*512U)

/* Exported types ----------------------------------------------------------------*/

/* Exported constants ------------------------------------------------------------*/
/* Exported macro ----------------------------------------------------------------*/
/* Exported functions ----------------------------------------------------------- */

/**
* @brief Brief description of function
*/



/* Exported Object types ---------------------------------------------------------*/
class MUSIC_PLAYER
{

public:
  typedef enum : uint8_t
  {
    BUFFER_0	= 0,
    BUFFER_1	= 1,

  } buffer_index;

  PLAYLIST playlist;
  CIRCULAR_BUFFER * current_buffer;	/**< pointer to currently in use buffer */

  volatile uint8_t * pdata;
  uint32_t file_size;
  volatile uint32_t file_index;

  void init(void);

  uint8_t setPointer2AudioData(void * pointer2data);
  void setFileSize(uint32_t val);
  void resetFileSize();

  void setFileIndex(uint32_t val);
  void resetFileIndex();
  //int8_t openFile(const char * file_name);
  void changeBuffer(const buffer_index buffer_index);

  void playSample();
  void enableMusic();
  void disableMusic();

  //int8_t parseHeaderWAV(const uint8_t * pData);
  int8_t parseHeaderWAV();

private:
  static WAV_H header;

  static CIRCULAR_BUFFER * buff_0;
  static CIRCULAR_BUFFER * buff_1;
};

extern MUSIC_PLAYER * pPlayer;
extern "C" void TIM15_IRQHandler(void);
/* Exported Object constants -----------------------------------------------------*/
/* Exported Object macro ---------------------------------------------------------*/
/* Exported Object functions -----------------------------------------------------*/



#endif /* _AUDIO_H_ */

/*-------------------------------END OF FILE--------------------------------------*/
