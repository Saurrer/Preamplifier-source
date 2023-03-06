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

#include "../inc/PREAMPLIFIER.h"
/* Private typedef ---------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------*/
#define PREAMPLIFIER_VOLUME_DEFAULT_VALUE			(LMC1992_VOLUME_MID)
#define PREAMPLIFIER_FADER_DEFAULT_VALUE			(LMC1992_FADER_MID)
#define PREAMPLIFIER_TONE_DEFAULT_VALUE				(LMC1992_TONE_FLAT)

/* Private macro -----------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------*/

namespace Preamplifier
{
  const char * FunctionNameTable[LMC1992N_FUNCTION_COUNT] =
  {
      "Input",
      "Bass",
      "Treble",
      "Volume",
      "Fader FR",
      "Fader FL",
      "Fader RR",
      "Fader RL",
  };

  input_t INPUT::source {LMC1992N_INPUT_SELECT_ADDRESS, LMC1992N_INPUT_SELECT_MIN, LMC1992N_INPUT_SELECT_MAX, INPUT_OPEN};

  INPUT * source;

}  // namespace Preamplifier

/* Private function prototypes ---------------------------------------------------*/
/*
  Function:
  Input Data:
  Action:
*/

/* Private functions -------------------------------------------------------------*/
void
Preamplifier::init(void)
{
  source = new(INPUT);

  source->changeSource(3);
  source->fd_left_rear.setValue(LMC1992N_FADER_MAX);
  source->fd_right_rear.setValue(LMC1992N_FADER_MAX);
  source->fd_left_front.setValue(LMC1992N_FADER_MAX);
  source->fd_right_front.setValue(LMC1992N_FADER_MAX);

  source->volume.setValue(LMC1992N_VOLUME_MAX);
}

Preamplifier::INPUT::INPUT()
{

}

int8_t
Preamplifier::INPUT::getSource() { return source.getValue(); }

void
Preamplifier::INPUT::changeSource(int8_t val) { source.setValue(val); }
/*-------------------------------END OF FILE--------------------------------------*/
