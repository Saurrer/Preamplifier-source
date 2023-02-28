/** @file colour.cpp
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Feb 28, 2023
* @version 	1.0.0
* @copyright 	© 20202322. All Rights Reserved.
*
* @brief brief description of colour.cpp.
*
* @page colour.cpp
* @details Detail description of colour.cpp.
*
*/
/* Includes ----------------------------------------------------------------------*/
#include <stdint.h>
#include <stdlib.h>

#include <cmsis_gcc.h>
#include <stm32f091xc.h>

#include "../inc/colour.h"
/* Private typedef ---------------------------------------------------------------*/
#define RGB_COLOR_NONE				(0U)
#define RGB_COLOR_RED				(1U)
#define RGB_COLOR_GREEN				(2U)
#define RGB_COLOR_BLUE				(3U)

#define HSV_COLOR_POSITION_RED			(0U)
#define HSV_COLOR_POSITION_GREEN		(2U)
#define HSV_COLOR_POSITION_BLUE			(4U)

/* Private define ----------------------------------------------------------------*/

/* Private macro -----------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------*/
/* Private function prototypes ---------------------------------------------------*/

/*
  Function:
  Input Data:
  Action:
*/
template <typename T>
T max (T x, T y, T z)
{
  T temp_max;

  temp_max = (x > y) ? (x) : (y);
  temp_max = (temp_max > z) ? (temp_max) : (z);

  return temp_max;
}

template <typename T>
T min (T x, T y, T z)
{
  T temp_min;

  temp_min = (x < y) ? (x) : (y);
  temp_min = (temp_min < z) ? (temp_min) : (z);

  return temp_min;
}

using namespace colour;

static uint8_t max_colour(colour::RGB * rgb, uint8_t x);

//__attribute__( (optimize("-O1")) )
/* Private functions -------------------------------------------------------------*/


RGB::RGB()
:red{RGB_DEFAULT},
green{RGB_DEFAULT},
blue{RGB_DEFAULT}
{

}

HSV::HSV()
:hue{HSV_DEFAULT},
saturation{HSV_DEFAULT},
value{HSV_DEFAULT}
{

}

HSV colour::rgb2hsv(colour::RGB * rgb)
{
  HSV temp_hsv;				/**<  */

  // assistant variables
  float temp_hue;			/**<  */
  uint8_t delta, col;			/**<  */

  // calc Value
  temp_hsv.value = max(rgb->red, rgb->green, rgb->blue);
  delta = temp_hsv.value - min(rgb->red, rgb->green, rgb->blue);

  // which color has max value?
  col = max_colour(rgb, (uint8_t)temp_hsv.value);

  // calc Saturation
  if(temp_hsv.value) { temp_hsv.saturation = ((float) delta / temp_hsv.value) * 100; }
  else 		     { temp_hsv.saturation = 0.0f; }

  // calc Hue
  switch(col)
  {
    case RGB_COLOR_NONE:
	  temp_hue = 0;
	  break;
    case RGB_COLOR_RED:
	  temp_hue = ((float) (rgb->green - rgb->blue) / delta);
          temp_hue += HSV_COLOR_POSITION_RED;
          break;
    case RGB_COLOR_GREEN:
	  temp_hue = ((float) (rgb->blue - rgb->red) / delta);
	  temp_hue += HSV_COLOR_POSITION_GREEN;
          break;
    case RGB_COLOR_BLUE:
	  temp_hue = ((float) (rgb->red - rgb->green) / delta);
	  temp_hue += HSV_COLOR_POSITION_BLUE;
          break;
  }

  if(temp_hue) 	{ temp_hsv.hue = temp_hue * 60.0f; }
  else 		{ temp_hsv.hue = 6.0f + (temp_hue * 60.0f); }

  temp_hsv.value = ((float) temp_hsv.value / RGB_RESOLUTION_MAX) * 100;

  return temp_hsv;
}


RGB colour::hsv2rgb(colour::HSV * hsv)
{
  RGB temp_rgb;			/**<  */

  // assistant variables
  float C, X, X2, m;		/**<  */
  float red, green, blue;	/**<  */

  C = (hsv->value * hsv->saturation) / 10000.0f;		  /**<  */
  X2 = ((hsv->hue * 100) / 60) % 100;
  X = C * (float) X2/100 ;					  //
  m = (float) ((hsv->value) * (100 - hsv->saturation)) / 10000.0f;//

  if(hsv->hue >= 0 && hsv->hue < 60)
    {
      red   = C;
      green = X;
      blue  = 0;
    }
  else if(hsv->hue >= 60 && hsv->hue < 120)
    {
      red   = X;
      green = C;
      blue  = 0;
    }
  else if(hsv->hue >= 120 && hsv->hue < 180)
    {
      red   = 0;
      green = C;
      blue  = X;
    }
  else if(hsv->hue >= 180 && hsv->hue < 240)
    {
      red   = 0;
      green = X;
      blue  = C;
    }
  else if(hsv->hue >= 240 && hsv->hue < 300)
    {
      red   = X;
      green = 0;
      blue  = C;
    }
  else if(hsv->hue >= 300 && hsv->hue < 360)
    {
      red   = C;
      green = 0;
      blue  = X;
    }

  temp_rgb.red   = (float) (red+m)*RGB_RESOLUTION_MAX;
  temp_rgb.green = (float) (green+m)*RGB_RESOLUTION_MAX;
  temp_rgb.blue  = (float) (blue+m)*RGB_RESOLUTION_MAX;

  return temp_rgb;
}


uint8_t max_colour(colour::RGB * rgb, uint8_t x)
{
  if(rgb->blue == x)		{ return RGB_COLOR_BLUE; }
  else if(rgb->green == x)	{ return RGB_COLOR_GREEN; }
  else if(rgb->red == x) 	{ return RGB_COLOR_RED; }
}
/*-------------------------------END OF FILE--------------------------------------*/
