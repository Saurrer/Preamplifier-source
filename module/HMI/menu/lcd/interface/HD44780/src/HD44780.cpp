/** @file HD44780.cpp
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Mar 2, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of HD44780.cpp.
*
* @page HD44780.cpp
* @details Detail description of HD44780.cpp.
*
*/
/* Includes ----------------------------------------------------------------------*/
#include <stdint.h>
#include <stdlib.h>

#include <cmsis_gcc.h>
#include <stm32f091xc.h>

#include "../inc/HD44780.h"
#include <STM32/gpio/inc/gpio.h>

#include <Utils/delay/inc/delay.h>
/* Private typedef ---------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------*/
#define LCD_DATA_PORT			GPIOB
/* Private macro -----------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------*/
/* Private function prototypes ---------------------------------------------------*/
/* Private functions -------------------------------------------------------------*/

/**
 * @fn void HD44780::send_half_byte(uint8_t data)
 *
 * @details
 *
 * @param[in] x operand 1
 *
 */
void HD44780::send_half_byte(uint8_t data)	// do poprawy - dla zapisu i odczytu
{
  if(data & (1<<0)) LCD_D4_PORT->ODR |= LCD_D4_PIN;
  else 		    LCD_D4_PORT->ODR &= ~LCD_D4_PIN;

  if(data & (1<<1)) LCD_D5_PORT->ODR |= LCD_D5_PIN;
  else 		    LCD_D5_PORT->ODR &= ~LCD_D5_PIN;

  if(data & (1<<2)) LCD_D6_PORT->ODR |= LCD_D6_PIN;
  else 		    LCD_D6_PORT->ODR &= ~LCD_D6_PIN;

  if(data & (1<<3)) LCD_D7_PORT->ODR |= LCD_D7_PIN;
  else 		    LCD_D7_PORT->ODR &= ~LCD_D7_PIN;
}

/**
 * @fn void HD44780::send_byte(unsigned char _data)
 *
 * @details
 *
 * @param[in] x operand 1
 *
 */
void HD44780::send_byte(unsigned char _data)
{
  changeBusDirection(bus_direction::output);

#if USE_RW == 1
  LCD_RW_CLR;
#endif
  LCD_E_SET;
  send_half_byte(_data>>4);	/** old nibble */
  LCD_E_CLR;

  LCD_E_SET;
  send_half_byte(_data);	/** young nibble */
  LCD_E_CLR;

#if USE_RW == 1
    while(read_BF() & 0x80);
#else
    delay_us(120);
#endif
}

/**
 * @fn void HD44780::send_cmd(uint8_t cmd)
 *
 * @details
 *
 * @param[in] x operand 1
 *
 */
void HD44780::send_cmd(uint8_t cmd)
{
  LCD_RS_CLR;
  send_byte(cmd);
}

/**
 * @fn void HD44780::send_data(uint8_t data)
 *
 * @details
 *
 * @param[in] x operand 1
 *
 */
void HD44780::send_data(uint8_t data)
{
  LCD_RS_SET;
  send_byte(data);
}

/**
 * @fn uint8_t HD44780::read_half_byte(void)
 *
 * @details
 *
 */
uint8_t HD44780::read_half_byte(void)
{
  uint8_t data = 0;

  if(LCD_D4_PORT->IDR & LCD_D4_PIN) data |= (1<<0);
  if(LCD_D5_PORT->IDR & LCD_D5_PIN) data |= (1<<1);
  if(LCD_D6_PORT->IDR & LCD_D6_PIN) data |= (1<<2);
  if(LCD_D7_PORT->IDR & LCD_D7_PIN) data |= (1<<3);

  return data;
}

/**
 * @fn uint8_t HD44780::read_byte(void)
 *
 * @details
 *
 * @return
 */
uint8_t HD44780::read_byte(void)
{
  uint8_t data = 0;
  changeBusDirection(bus_direction::input);

  LCD_RW_SET;
  LCD_E_SET;
  data |= (read_half_byte() << 4);		//old nibble
  LCD_E_CLR;
  LCD_E_SET;
  data |= read_half_byte();
  LCD_E_CLR;

  return data;
}

/**
 * @fn uint8_t HD44780::read_BF(void)
 *
 * @details
 *
 * @return
 */
uint8_t HD44780::read_BF(void)
{
  LCD_RS_CLR;
  return read_byte();
}

/**
 * @fn void HD44780::changeBusDirection(bus_direction dir)
 *
 * @details
 *
 * @param[in] x operand 1
 *
 * @return
 */
void HD44780::changeBusDirection(bus_direction dir)
{
  if(dir == bus_direction::input)
    {
      GpioPinConfig(LCD_D7_PORT, LCD_D7_PIN, gpio_input_floating);
      GpioPinConfig(LCD_D6_PORT, LCD_D6_PIN, gpio_input_floating);
      GpioPinConfig(LCD_D5_PORT, LCD_D5_PIN, gpio_input_floating);
      GpioPinConfig(LCD_D4_PORT, LCD_D4_PIN, gpio_input_floating);
    }
  else	/** dir == bus_direction::output */
    {
      GpioPinConfig(LCD_D7_PORT, LCD_D7_PIN, gpio_output_PP_PU_HS);
      GpioPinConfig(LCD_D6_PORT, LCD_D6_PIN, gpio_output_PP_PU_HS);
      GpioPinConfig(LCD_D5_PORT, LCD_D5_PIN, gpio_output_PP_PU_HS);
      GpioPinConfig(LCD_D4_PORT, LCD_D4_PIN, gpio_output_PP_PU_HS);
    }
}

/**
 * @fn void HD44780::init(void)
 *
 * @details
 *
 */
void HD44780::init(void)
{
  delay_init();

  GpioPinConfig(LCD_RS_PORT, LCD_RS_PIN, gpio_output_PP_PU_HS);
  GpioPinConfig(LCD_RW_PORT, LCD_RW_PIN, gpio_output_PP_PU_HS);
  GpioPinConfig(LCD_E_PORT, LCD_E_PIN, gpio_output_PP_PU_HS);

  changeBusDirection(bus_direction::output);

  LCD_RS_SET;
  LCD_E_SET;
  LCD_RW_SET;
  delay_ms(15);

  LCD_E_CLR;
  LCD_RS_CLR;
  LCD_RW_CLR;

				/** BF not available yet */
  LCD_E_SET;
  send_half_byte(0x03);		/** 8bits mode, DL = 1 */
  LCD_E_CLR;
  delay_us(4100);

  LCD_E_SET;
  send_half_byte(0x03);		/** 8bits mode, DL = 1 */
  LCD_E_CLR;
  delay_us(100);

  LCD_E_SET;
  send_half_byte(0x03);		/** 8bits mode, DL = 1 */
  LCD_E_CLR;
  delay_us(100);

  LCD_E_SET;
  send_half_byte(0x02);		/** 4bits mode, DL = 0 */
  LCD_E_CLR;
  delay_us(100);

				/** BF is available now */
  /* BF - ON,
   * 4bit interface,
   * 2 row, sign size 5x7 busy
   * */
  send_cmd(FUNCTION_SET | FUNCTION_SET_DATA_LENGTH_4_BIT | FUNCTION_SET_DISPLAY_LINES_SET | FUNCTION_SET_CHARACTER_FONT_CLR );
  send_cmd(DISPLAY_CONTROL | DISPLAY_CONTROL_CURSOR_OFF);		/** cursor off */
  send_cmd(DISPLAY_CONTROL | DISPLAY_CONTROL_DISPLAY_ON);		/** turn on display */
  send_cmd(ENTRY_MODE | ENTRY_MODE_CURSOR_RIGHT);			/** moving cursor without moving data on screen */
  cls();								/** clear screen */

}

/**
 * @fn void HD44780::cls(void)
 *
 * @details
 *
 */
void HD44780::cls(void)
{
  send_cmd(CLEAR_DISPLAY);
#if USE_RW == 0
  delay_us(4900);
#endif
}

/**
 * @fn void HD44780::locate(uint8_t x, uint8_t y)
 *
 * @details
 *
 * @param[in] x operand 1
 * @param[in] y operand 2
 *
 */
void HD44780::locate(uint8_t x, uint8_t y)
{
  switch(x)
  {
    case 0:
      x = LCD_LINE1; break;	/** 1 sign of 0 row */
#if (LCD_ROWS > 1)
    case 1:
      x = LCD_LINE2; break;	/** 1 sign of 1 row */
#endif
#if (LCD_ROWS > 2)
    case 2:
      x = LCD_LINE3; break;	/** 1 sign of 2 row */
#endif
#if (LCD_ROWS > 3)
    case 3:
      x = LCD_LINE4; break;	/** 1 sign of 3 row */
#endif
  }

  send_cmd( (0x80+x+y) );
}

/**
 * @fn void HD44780::home(void)
 *
 * @details
 *
 */
void HD44780::home(void)
{
  send_cmd(CLEAR_DISPLAY | HOME);
#if USE_RW == 0
  delay_us(4900);
#endif
}

/**
 * @fn void HD44780::cursor_on(void)
 *
 * @details
 *
 */
void HD44780::cursor_on(void)
{
  send_cmd(DISPLAY_CONTROL | DISPLAY_CONTROL_DISPLAY_ON | DISPLAY_CONTROL_CURSOR_ON);
}

/**
 * @fn void HD44780::cursor_off(void)
 *
 * @details
 *
 */
void HD44780::cursor_off(void)
{
  send_cmd(DISPLAY_CONTROL | DISPLAY_CONTROL_DISPLAY_ON);
}

/**
 * @fn void HD44780::blink_on(void)
 *
 * @details
 *
 */
void HD44780::blink_on(void)
{
  send_cmd(DISPLAY_CONTROL | DISPLAY_CONTROL_DISPLAY_ON | DISPLAY_CONTROL_CURSOR_ON | DISPLAY_CONTROL_CURSOR_BLINK_ON);
}

/**
 * @fn void HD44780::blink_off(void)
 *
 * @details
 *
 */
void HD44780::blink_off(void)
{
  send_cmd(DISPLAY_CONTROL | DISPLAY_CONTROL_DISPLAY_ON );
}


/**
 * @fn void HD44780::send_string(char *s)
 *
 * @details
 *
 */
void HD44780::send_string(char *s)
{
  while(*s)
  {
    send_data(*s);
    s++;
  }
}

/**
 * @fn void HD44780::send_int(int data)
 *
 * @details
 *
 */
void HD44780::send_int(int data)
{
  char bufor[20];
  send_string(itoa(data, bufor, 10));
}

/**
 * @fn void HD44780::send_hex(int data)
 *
 * @details
 *
 */
void HD44780::send_hex(int data)
{
  char bufor[20];
  send_string(itoa(data, bufor, 16));
}


/*-------------------------------END OF FILE--------------------------------------*/
