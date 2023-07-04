/** @file microwire.h
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Mar 5, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of microwire.h.
*
* @page microwire.h
* @details Detail description of microwire.h.
*
*/

/* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef _MICROWIRE_H_
#define _MICROWIRE_H_

/* Includes ----------------------------------------------------------------------*/

/* Exported define ---------------------------------------------------------------*/
#define MICROWIRE_DATA_PORT		GPIOB
#define MICROWIRE_DATA_PIN		PB11

#define MICROWIRE_CLK_PORT		GPIOB
#define MICROWIRE_CLK_PIN		PB10

#define MICROWIRE_ENABLE_PORT		GPIOB
#define MICROWIRE_ENABLE_PIN		PB2

#define MICROWIRE_DATA_SET		MICROWIRE_DATA_PORT->BSRR|=GPIO_BSRR_BS_11
#define MICROWIRE_DATA_CLEAR		MICROWIRE_DATA_PORT->BSRR|=GPIO_BSRR_BR_11

#define MICROWIRE_CLK_SET		MICROWIRE_CLK_PORT->BSRR|=GPIO_BSRR_BS_10
#define MICROWIRE_CLK_CLEAR		MICROWIRE_CLK_PORT->BSRR|=GPIO_BSRR_BR_10

#define MICROWIRE_ENABLE_SET		MICROWIRE_ENABLE_PORT->BSRR|=GPIO_BSRR_BS_2
#define MICROWIRE_ENABLE_CLEAR		MICROWIRE_ENABLE_PORT->BSRR|=GPIO_BSRR_BR_2


#define MICROWIRE_FRAME_LENGTH				(11U)
#define MICROWIRE_FRAME_CHIP_ADDRESS_Pos		(9U)
#define MICROWIRE_FRAME_FUNCTION_ADDRESS_Pos		(6U)
#define MICROWIRE_FRAME_DATA_Pos			(0U)

/* Exported types ----------------------------------------------------------------*/
/* Exported constants ------------------------------------------------------------*/
/* Exported macro ----------------------------------------------------------------*/
/* Exported functions ----------------------------------------------------------- */
/**
* @brief Brief description of function
*/

/* Exported Object types ---------------------------------------------------------*/
class MICROWIRE
{

public:
  typedef union
  {
    uint16_t frame;

    struct
    {
	uint16_t data 						:6;
	uint16_t function_address 				:3;
	uint16_t chip_address					:2;
	uint16_t reserved					:5;

    };

  } lmc1992n_frame;

  void init(void);
  uint16_t build(uint8_t function_adr, uint8_t data);
  void send(uint16_t frame);

  lmc1992n_frame buf;

private:
  static uint8_t chip_select_address;

};
/* Exported Object constants -----------------------------------------------------*/
/* Exported Object macro ---------------------------------------------------------*/
/* Exported Object functions -----------------------------------------------------*/



#endif /* _MICROWIRE_H_ */

/*-------------------------------END OF FILE--------------------------------------*/
