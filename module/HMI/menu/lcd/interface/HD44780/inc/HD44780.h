/** @file HD44780.h
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Mar 2, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of HD44780.h.
*
* @page HD44780.h
* @details Detail description of HD44780.h.
*
*/

/* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef _HD44780_H_
#define _HD44780_H_

/* Includes ----------------------------------------------------------------------*/

/* Exported define ---------------------------------------------------------------*/

/* DISPLAY CONFIGURATION */
#define LCD_ROWS 					2
#define LCD_COLUMNS 					16

/*
 * ustawienie szerokosci magistrali
 * - 8 bit
 * - 4 bit
 */
#define INTERFACE_8_BIT					1
#define INTERFACE_4_BIT					2
#define INTERFACE					INTERFACE_4_BIT

#if ( (LCD_ROWS == 4) && (LCD_COLUMNS == 20) )
  #define LCD_LINE1 0x00
  #define LCD_LINE2 0x28
  #define LCD_LINE3 0x14
  #define LCD_LINE4 0x54
#else
  #define LCD_LINE1 0x00
  #define LCD_LINE2 0x40
  #define LCD_LINE3 0x10
  #define LCD_LINE4 0x50
#endif

#if (INTERFACE == INTERFACE_4_BIT)
  #define LCD_D7_PORT					GPIOB
  #define LCD_D7_PIN					PB6
  #define LCD_D6_PORT					GPIOB
  #define LCD_D6_PIN					PB5
  #define LCD_D5_PORT					GPIOB
  #define LCD_D5_PIN					PB4
  #define LCD_D4_PORT					GPIOB
  #define LCD_D4_PIN					PB3
#else //(INTERFACE == INTERFACE_8_BIT)
  #define LCD_D7_PORT
  #define LCD_D7_PIN
  #define LCD_D6_PORT
  #define LCD_D6_PIN
  #define LCD_D5_PORT
  #define LCD_D5_PIN
  #define LCD_D4_PORT
  #define LCD_D4_PIN
  #define LCD_D3_PORT
  #define LCD_D3_PIN
  #define LCD_D2_PORT
  #define LCD_D2_PIN
  #define LCD_D1_PORT
  #define LCD_D1_PIN
  #define LCD_D0_PORT
  #define LCD_D0_PIN
#endif

/* Exported types ----------------------------------------------------------------*/
/* Exported constants ------------------------------------------------------------*/
/* Exported macro ----------------------------------------------------------------*/
#define USE_RW						1

#define LCD_RS_PORT					GPIOB
#define LCD_RS_PIN					PB9
#define LCD_RW_PORT					GPIOB
#define LCD_RW_PIN					PB8
#define LCD_E_PORT					GPIOB
#define LCD_E_PIN					PB7

/*
 * RS:
 * 0 - Instruction register
 * 1 - Data register
 */
#define LCD_RS_SET					LCD_RS_PORT->BSRR|=GPIO_BSRR_BS_9
#define LCD_RS_CLR					LCD_RS_PORT->BSRR|=GPIO_BSRR_BR_9

/*
 * R/W:
 * 0 - Write
 * 1 - Read
 */
#define LCD_RW_SET					LCD_RW_PORT->BSRR|=GPIO_BSRR_BS_8
#define LCD_RW_CLR					LCD_RW_PORT->BSRR|=GPIO_BSRR_BR_8

/*
 * E:
 * 0 - Read
 * 1 - Write
 */
#define LCD_E_SET					LCD_E_PORT->BSRR|=GPIO_BSRR_BS_7
#define LCD_E_CLR					LCD_E_PORT->BSRR|=GPIO_BSRR_BR_7

/* HD44780 INSTRUCTIONS */

/*
 * Clear display writes space code 20H (character pattern for character code 20H must be a blank pattern)
 * into all DDRAM addresses
 */
#define CLEAR_DISPLAY					(0x1U)

/*
 * Sets DDRAM address 0 into address counter
 * DDRAM contents do not change.
 *
 * Cursor or blinking go to the left edge of the display (in the first line if 2 lines are displayed)
 */
#define HOME						(0x2U)

/*
 * I/D - Increments/Decrements the DDRAM address by 1 when a character code
 * is written into or read from DDRAM
 *
 * The cursor or blinking moves to the right when incremented by 1
 * The cursor or blinking moves to the left when decremented by 1
 *
 * S - Shifts the entire display either to the right (I/D = 0) or to the left (I/D = 1) when S is 1
 * The display does not shift if S is 0
 *
 * If S is 1, it will seem as if the cursor does not move but the display does. The display does not shift when
 * reading from DDRAM. Also, writing into or reading out from CGRAM does not shift the display.
 */
#define ENTRY_MODE					(4U)
#define ENTRY_MODE_INC_DEC_Pos				(1U)
#define ENTRY_MODE_CURSOR_RIGHT				(1U << ENTRY_MODE_INC_DEC_Pos)
#define ENTRY_MODE_CURSOR_LEFT				(0U << ENTRY_MODE_INC_DEC_Pos)
#define ENTRY_MODE_SHIFT_Pos				(0U)
#define ENTRY_MODE_CURSOR_DYNAMIC			(1U << ENTRY_MODE_SHIFT_Pos)
#define ENTRY_MODE_CURSOR_STAIC				(0U << ENTRY_MODE_SHIFT_Pos)

/*
 * D = 1 - Display is ON
 * D = 0 - Display if OFF
 *
 * When off, the display data remains in DDRAM, but can be displayed instantly by setting D to 1
 *
 * C = 1 - Cursor is displayed
 * C = 0 - Cursor is not displayed
 *
 * The cursor is displayed using 5 dots in the 8th line for 5 × 8 dot character font selection
 * and in the 11th line for the 5 × 10 dot character font selection
 *
 * B = 1 - The character indicated by the cursor blinks
 * B = 0 - off
 */
#define DISPLAY_CONTROL					(8U)
#define DISPLAY_CONTROL_DISPLAY_Pos			(2U)
#define DISPLAY_CONTROL_DISPLAY_ON			(1U << DISPLAY_CONTROL_DISPLAY_Pos)
#define DISPLAY_CONTROL_DISPLAY_OFF			(0U << DISPLAY_CONTROL_DISPLAY_Pos)
#define DISPLAY_CONTROL_CURSOR_Pos			(1U)
#define DISPLAY_CONTROL_CURSOR_ON			(1U << DISPLAY_CONTROL_CURSOR_Pos)
#define DISPLAY_CONTROL_CURSOR_OFF			(0U << DISPLAY_CONTROL_CURSOR_Pos)
#define DISPLAY_CONTROL_CURSOR_BLINK_Pos		(0U)
#define DISPLAY_CONTROL_CURSOR_BLINK_ON			(1U << DISPLAY_CONTROL_CURSOR_BLINK_Pos)
#define DISPLAY_CONTROL_CURSOR_BLINK_OFF		(0U << DISPLAY_CONTROL_CURSOR_BLINK_Pos)

/*
 * Cursor or display shift shifts the cursor position or display to the right or left
 * without writing or reading display data
 *
 * Note that the first and second line displays will shift at the same time.
 *
 *  |__S/C__|__R/L__|
 *  |   0   |   0   | Shifts the cursor position to the left. (AC is decremented by one)
 *  |   0   |   1   | Shifts the cursor position to the right. (AC is incremented by one)
 *  |   1   |   0   | Shifts the entire display to the left. The cursor follows the display shift
 *  |   1   |   1   | Shifts the entire display to the right. The cursor follows the display shift
 *
 */
#define COD_SHIFT					(16U)
#define COD_SHIFT_RL_Pos				(2U)
#define COD_SHIFT_RIGHT					(1U << COD_SHIFT_RL_Pos)
#define COD_SHIFT_LEFT					(0U << COD_SHIFT_RL_Pos)
#define COD_SHIFT_SC_Pos				(3U)
#define COD_SHIFT_SCREEN				(1U << COD_SHIFT_SC_Pos)
#define COD_SHIFT_CURSOR				(0U << COD_SHIFT_SC_Pos)

/*
 * Sets interface data length
 * DL = 1 -> 8 bit len (D7-D0),
 * DL = 0 -> 4 bit len (D7-D4)
 *
 * |___N___|___F___|_No of Display Lines_|_Character Font_|_Duty_Factor_|
 * |   0   |   0   | 		1	 |     5x8 dots   | 	1/8     |
 * |   0   |   1   | 		1	 |     5x10 dots  | 	1/11    |
 * |   1   |   *   | 		2	 |     5x8 dots   |  	1/16    |
 *
 */
#define FUNCTION_SET					(32U)
#define FUNCTION_SET_DATA_LENGTH_Pos			(4U)
#define FUNCTION_SET_DATA_LENGTH_8_BIT			(1U << FUNCTION_SET_DATA_LENGTH_Pos)
#define FUNCTION_SET_DATA_LENGTH_4_BIT			(0U << FUNCTION_SET_DATA_LENGTH_Pos)
#define FUNCTION_SET_DISPLAY_LINES_Pos			(3U)
#define FUNCTION_SET_DISPLAY_LINES_SET			(1U << FUNCTION_SET_DISPLAY_LINES_Pos)
#define FUNCTION_SET_DISPLAY_LINES_CLR			(0U << FUNCTION_SET_DISPLAY_LINES_Pos)
#define FUNCTION_SET_CHARACTER_FONT_Pos			(2U)
#define FUNCTION_SET_CHARACTER_FONT_SET			(1U << FUNCTION_SET_CHARACTER_FONT_Pos)
#define FUNCTION_SET_CHARACTER_FONT_CLR			(0U << FUNCTION_SET_CHARACTER_FONT_Pos)

/*
 * Character Generator RAM
 *
 * Set CGRAM address sets the CGRAM address binary AAAAAA into the address counter
 * Data is then written to or read from the MPU for CGRAM
 */
#define SET_CGRAM_ADDRESS				(64U)

/*
 * Display Data RAM
 *
 * Set DDRAM address sets the DDRAM address binary AAAAAAA into the address counter
 * Data is then written to or read from the MPU for DDRAM
 *
 * However, when N is 0 (1-line display), AAAAAAA can be 00H to 4FH. When N is 1 (2-line display),
 * AAAAAAA can be 00H to 27H for the first line, and 40H to 67H for the second line
 */
#define SET_DDRAM_ADDRESS				(128U)


/* Exported functions ----------------------------------------------------------- */

/* Exported Object types ---------------------------------------------------------*/
class HD44780
{

public:
  enum class bus_direction : uint8_t
  {
    input 	= 0,
    output	= 1,
  };

  void init();

  void cls();
  void locate(uint8_t , uint8_t );
  void home(void);

  void cursor_on(void);
  void cursor_off(void);

  void blink_on(void);
  void blink_off(void);

  void send_cmd(uint8_t);
  void send_data(uint8_t );
  void send_string(char * );
  void send_int(int );
  void send_hex(int );

  uint8_t read_BF(void);

private:
  void changeBusDirection(bus_direction dir);
  void init_control_bus(void);

  uint8_t read_half_byte(void);
  uint8_t read_byte(void);

  void send_half_byte(uint8_t data);
  void send_byte(unsigned char _data);

};
/* Exported Object constants -----------------------------------------------------*/
/* Exported Object macro ---------------------------------------------------------*/
/* Exported Object functions -----------------------------------------------------*/



#endif /* _HD44780_H_ */

/*-------------------------------END OF FILE--------------------------------------*/
