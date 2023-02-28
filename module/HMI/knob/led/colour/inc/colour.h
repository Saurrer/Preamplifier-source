/** @file colour.h
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Feb 11, 2023
* @version 	1.0.0
* @copyright 	© 2022. All Rights Reserved.
*
* @brief brief description of colour.h.
*
* @page colour.h
* @details Detail description of colour.h.
*
*/

/* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef _COLOUR_H_
#define _COLOUR_H_

/* Exported define ---------------------------------------------------------------*/
#define RGB_DEFAULT							(0U)
#define HSV_DEFAULT							RGB_DEFAULT

#define RGB_RESOLUTION_MAX						(UINT8_MAX)
#define RGB_DATATYPE							uint8_t
/* Exported constants ------------------------------------------------------------*/
/* Exported macro ----------------------------------------------------------------*/
/* Exported functions ----------------------------------------------------------- */
/**
* @brief Brief description of function
*/
/* Exported Object types ---------------------------------------------------------*/

namespace colour
{

  class RGB
  {

  public:
    RGB_DATATYPE red;
    RGB_DATATYPE green;
    RGB_DATATYPE blue;

    RGB();

  };


  class HSV
  {

  public:
   int16_t hue;
   uint8_t saturation;
   uint8_t value;

   HSV();

  };

  extern HSV rgb2hsv(colour::RGB * rgb);
  extern RGB hsv2rgb(colour::HSV * hsv);


} // namespace colour

/* Exported Object constants -----------------------------------------------------*/
/* Exported Object macro ---------------------------------------------------------*/
/* Exported Object functions -----------------------------------------------------*/


#endif /* _COLOUR_H_ */

/*-------------------------------END OF FILE--------------------------------------*/
