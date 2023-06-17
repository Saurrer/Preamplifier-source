/** @file PREAMPLIFIER.h
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Mar 6, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of PREAMPLIFIER.h.
*
* @page PREAMPLIFIER.h
* @details Detail description of PREAMPLIFIER.h.
*
*/

/* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef _PREAMP_H_
#define _PREAMP_H_

/* Includes ----------------------------------------------------------------------*/
#include "../LMC1992N/inc/lmc1992n.h"
/* Exported define ---------------------------------------------------------------*/
/* Exported types ----------------------------------------------------------------*/
namespace preamp
{


  class INPUT
  {

  public:
    enum
    { INPUT_OPEN = 0, RCA_1, RCA_2, minijack, microSD };

    INPUT();

    int8_t getSource();
    void changeSource(int8_t val);

    fader_t fd_left_rear   {LMC1992N_LEFT_REAR_FADER_ADDRESS, LMC1992N_FADER_MIN, LMC1992N_FADER_MAX, LMC1992N_FADER_MAX};
    fader_t fd_right_rear  {LMC1992N_RIGHT_REAR_FADER_ADDRES, LMC1992N_FADER_MIN, LMC1992N_FADER_MAX, LMC1992N_FADER_MAX};
    fader_t fd_left_front  {LMC1992N_LEFT_FRONT_FADER_ADDRESS, LMC1992N_FADER_MIN, LMC1992N_FADER_MAX, LMC1992N_FADER_MAX};
    fader_t fd_right_front {LMC1992N_RIGHT_FRONT_FADER_ADDRESS, LMC1992N_FADER_MIN, LMC1992N_FADER_MAX, LMC1992N_FADER_MAX};

    volume_t volume 	   {LMC1992N_VOLUME_ADDRESS, LMC1992N_VOLUME_MIN, LMC1992N_VOLUME_MAX, LMC1992N_VOLUME_MAX};

    tone_t treble	   {LMC1992N_TREBLE_ADDRESS, LMC1992N_TONE_MIN, LMC1992N_TONE_MAX, LMC1992N_TONE_FLAT};
    tone_t bass		   {LMC1992N_BASS_ADDRESS, LMC1992N_TONE_MIN, LMC1992N_TONE_MAX, LMC1992N_TONE_FLAT};

    input_t source	   {LMC1992N_INPUT_SELECT_ADDRESS, LMC1992N_INPUT_SELECT_MIN, LMC1992N_INPUT_SELECT_MAX, INPUT_OPEN};

  private:
//    input_t source	   {LMC1992N_INPUT_SELECT_ADDRESS, LMC1992N_INPUT_SELECT_MIN, LMC1992N_INPUT_SELECT_MAX, INPUT_OPEN};
  };

  enum
  {
    LMC1992_INPUT 	= 0,
    LMC1992_BASS 	= 1,
    LMC1992_TREBLE 	= 2,
    LMC1992_VOLUME 	= 3,
    LMC1992_FADER_RF 	= 4,
    LMC1992_FADER_LF 	= 5,
    LMC1992_FADER_RR 	= 6,
    LMC1992_FADER_LR 	= 7
  };

  extern char * FunctionNameTable[LMC1992N_FUNCTION_COUNT];

  //extern char* FunctionNameTable[];
  extern void init(void);
  extern INPUT * pSource;

}  // namespace Preamplifier


/* Exported constants ------------------------------------------------------------*/
/* Exported macro ----------------------------------------------------------------*/
/* Exported functions ----------------------------------------------------------- */
/**
* @brief Brief description of function
*/

/* Exported Object types ---------------------------------------------------------*/
/* Exported Object constants -----------------------------------------------------*/
/* Exported Object macro ---------------------------------------------------------*/
/* Exported Object functions -----------------------------------------------------*/

#endif /* _PREAMP_H_ */

/*-------------------------------END OF FILE--------------------------------------*/
