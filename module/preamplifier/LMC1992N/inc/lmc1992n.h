/** @file lmc1992n.h
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Mar 6, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of lmc1992n.h.
*
* @page lmc1992n.h
* @details Detail description of lmc1992n.h.
*
*/

/* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef _LMC1992N_H_
#define _LMC1992N_H_

/* Includes ----------------------------------------------------------------------*/
#include <stdint.h>

#include "../interface/microwire/inc/microwire.h"
/* Exported define ---------------------------------------------------------------*/

#define LMC1992N_INPUT_COUNT					(4U)
#define LMC1992N_FUNCTION_COUNT					(8U)
#define LMC1992N_OUTPUT_SPEAKER_COUNT				(4U)

#define LMC1992N_VOLUME_MAX					(40U)
#define LMC1992N_VOLUME_MID					(20U)
#define LMC1992N_VOLUME_MIN					(0U)

#define LMC1992N_FADER_MAX					(20U)
#define LMC1992N_FADER_MID					(10U)
#define LMC1992N_FADER_MIN					(0U)

#define LMC1992N_TONE_LEVELS					(4U)
#define LMC1992N_TONE_MAX					(12U)
#define LMC1992N_TONE_FLAT					(6U)	//FLAT
#define LMC1992N_TONE_MIN					(0U)

#define LMC1992N_INPUT_SELECT_MAX				(4U)
#define LMC1992N_INPUT_SELECT_MIN				(0U)

#define LMC1992N_LEFT_REAR_FADER_ADDRESS			(0x07)
#define LMC1992N_RIGHT_REAR_FADER_ADDRES			(0x06)
#define LMC1992N_LEFT_FRONT_FADER_ADDRESS			(0x05)
#define LMC1992N_RIGHT_FRONT_FADER_ADDRESS			(0x04)
#define LMC1992N_VOLUME_ADDRESS					(0x03)
#define LMC1992N_TREBLE_ADDRESS					(0x02)
#define LMC1992N_BASS_ADDRESS					(0x01)
#define LMC1992N_INPUT_SELECT_ADDRESS				(0x00)

/* Exported types ----------------------------------------------------------------*/
/* Exported constants ------------------------------------------------------------*/
/* Exported macro ----------------------------------------------------------------*/
/* Exported functions ----------------------------------------------------------- */
/**
* @brief Brief description of function
*/

/* Exported Object types ---------------------------------------------------------*/
class LMC1992_FUNCTION
{

public:
  LMC1992_FUNCTION(uint8_t f_adr,
		   int8_t f_min_val, int8_t f_max_val,
		   int8_t f_init_val
		   );

  uint8_t getAddress();

  int8_t setValue(int8_t val);
  int8_t getValue();

  LMC1992_FUNCTION& operator++();
  LMC1992_FUNCTION& operator--();

private:
  uint8_t address;
  uint8_t min, max;
  uint8_t value;

  static int8_t init_flag;
  static MICROWIRE interface;
};

class volume_t : public LMC1992_FUNCTION /**< from -80 dB to 0 dB with 2dB attenuator step */
{
  using LMC1992_FUNCTION::LMC1992_FUNCTION;
};

class fader_t : public LMC1992_FUNCTION	/**< from -40 dB to 0 dB with 2dB attenuator step */
{
  using LMC1992_FUNCTION::LMC1992_FUNCTION;
};

class tone_t : public LMC1992_FUNCTION	/**< from -12 dB to 12 dB with 2dB attenuator step */
{
  using LMC1992_FUNCTION::LMC1992_FUNCTION;
};

class input_t : public LMC1992_FUNCTION	/**< from -12 dB to 12 dB with 2dB attenuator step */
{
  using LMC1992_FUNCTION::LMC1992_FUNCTION;
};

/* Exported Object constants -----------------------------------------------------*/
/* Exported Object macro ---------------------------------------------------------*/
/* Exported Object functions -----------------------------------------------------*/

#endif /* _LMC1992N_H_ */

/*-------------------------------END OF FILE--------------------------------------*/
