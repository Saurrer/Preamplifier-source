/** @file PREAMPLIFIER.cpp
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Mar 6, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of PREAMPLIFIER.cpp.
*
* @page PREAMPLIFIER.cpp
* @details Detail description of PREAMPLIFIER.cpp.
*
*/
/* Includes ----------------------------------------------------------------------*/

#include "../inc/preamp.h"
/* Private typedef ---------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------*/
#define PREAMPLIFIER_VOLUME_DEFAULT_VALUE			(LMC1992_VOLUME_MID)
#define PREAMPLIFIER_FADER_DEFAULT_VALUE			(LMC1992_FADER_MID)
#define PREAMPLIFIER_TONE_DEFAULT_VALUE				(LMC1992_TONE_FLAT)

/* Private macro -----------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------*/
//input_t preamp::INPUT::source = {LMC1992N_INPUT_SELECT_ADDRESS, LMC1992N_INPUT_SELECT_MIN, LMC1992N_INPUT_SELECT_MAX, INPUT_OPEN};

namespace preamp
{

  char * FunctionNameTable[LMC1992N_FUNCTION_COUNT] =
  {
      "Input",		//0
      "Bass",		//1
      "Treble",		//2
      "Volume",		//3
      "Fader RF",	//4
      "Fader LF",	//5
      "Fader RR",	//6
      "Fader LR",	//7
  };

  //input_t INPUT::source {LMC1992N_INPUT_SELECT_ADDRESS, LMC1992N_INPUT_SELECT_MIN, LMC1992N_INPUT_SELECT_MAX, INPUT_OPEN};

  INPUT * pSource;

}  // namespace Preamplifier

/* Private function prototypes ---------------------------------------------------*/
/*
  Function:
  Input Data:
  Action:
*/

/* Private functions -------------------------------------------------------------*/
void
preamp::init(void)
{
  pSource = new(INPUT);

  /* init LMC1992N configuration */
  pSource->changeSource(INPUT::minijack);
  pSource->fd_left_rear.setValue(LMC1992N_FADER_MAX);
  pSource->fd_right_rear.setValue(LMC1992N_FADER_MAX);
  pSource->fd_left_front.setValue(LMC1992N_FADER_MAX);
  pSource->fd_right_front.setValue(LMC1992N_FADER_MAX);

  pSource->volume.setValue(LMC1992N_VOLUME_MAX);

  pSource->treble.setValue(LMC1992N_TONE_FLAT);
  pSource->bass.setValue(LMC1992N_TONE_FLAT);
}

preamp::INPUT::INPUT()
{

}

int8_t
preamp::INPUT::getSource() { return source.getValue(); }

void
preamp::INPUT::changeSource(int8_t val) { source.setValue(val); }
/*-------------------------------END OF FILE--------------------------------------*/
