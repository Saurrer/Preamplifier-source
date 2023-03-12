/** @file microSD_commands.h
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Nov 12, 2022
* @version 	1.0.0
* @copyright 	© 2022. All Rights Reserved.
*
* @brief brief description of microSD_commands.h.
*
* @page microSD_commands.h
* @details Detail description of microSD_commands.h.
*
*/

/* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef SOURCE_MODULE_MICROSD_INC_MICROSD_COMMANDS_H_
#define SOURCE_MODULE_MICROSD_INC_MICROSD_COMMANDS_H_

/* Includes ----------------------------------------------------------------------*/

/* Exported types ----------------------------------------------------------------*/
//extern uint16_t somevariable; /**< Line description of somevariable */
/* Exported constants ------------------------------------------------------------*/
/* Exported macro ----------------------------------------------------------------*/

/* MMC/SD command (in SPI mode) */
#define CMD0	(0)			/* GO_IDLE_STATE */
#define CMD1	(1)			/* SEND_OP_COND (MMC) */
#define	ACMD41	(0x80+41)		/* SEND_OP_COND (SDC) */
#define CMD8	(8)			/* SEND_IF_COND */
#define CMD9	(9)			/* SEND_CSD */
#define CMD10	(10)			/* SEND_CID */
#define CMD12	(12)			/* STOP_TRANSMISSION */
#define ACMD13	(0x80+13)		/* SD_STATUS (SDC) */
#define CMD13	(13)			/* SD_STATUS (SDC) */

#define CMD16	(16)			/* SET_BLOCKLEN */
#define CMD17	(17)			/* READ_SINGLE_BLOCK */
#define CMD18	(18)			/* READ_MULTIPLE_BLOCK */
#define CMD23	(23)			/* SET_BLOCK_COUNT (MMC) */
#define	ACMD23	(0x80+23)		/* SET_WR_BLK_ERASE_COUNT (SDC) */
#define CMD24	(24)			/* WRITE_BLOCK */
#define CMD25	(25)			/* WRITE_MULTIPLE_BLOCK */
#define CMD32	(32)			/* ERASE_ER_BLK_START */
#define CMD33	(33)			/* ERASE_ER_BLK_END */
#define CMD38	(38)			/* ERASE */
#define CMD55	(55)			/* APP_CMD */
#define CMD58	(58)			/* READ_OCR */

#define SD_R1_Idle			1   	//Karta w stanie Idle
#define SD_R1_EraseReset		2
#define SD_R1_IllegaCommand		4	//Nierozpoznane polecenie
#define SD_R1_CommandCRCError		8	//Blad CRC polecenia
#define SD_R1_EraseSeqError		16
#define SD_R1_AddressError		32
#define SD_R1_ParameterError		64
#define SD_R1_Response			128	//Bit odpowiedzi - zawsze r�wny 0

#define SD_OCR_CCS              	(1UL<<30) 	//Bit CCS rejestru OCR
/* Exported functions ----------------------------------------------------------- */
/**
* @brief Brief description of function
*/
extern void FunctionName(void);

/* Exported Object types ---------------------------------------------------------*/
/* Exported Object constants -----------------------------------------------------*/
/* Exported Object macro ---------------------------------------------------------*/
/* Exported Object functions -----------------------------------------------------*/



#endif /* SOURCE_MODULE_MICROSD_INC_MICROSD_COMMANDS_H_ */

/*-------------------------------END OF FILE--------------------------------------*/
