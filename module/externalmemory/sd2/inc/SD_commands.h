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
#ifndef _SD_COMMANDS_H_
#define _SD_COMMANDS_H_

/* Includes ----------------------------------------------------------------------*/

/* Exported types ----------------------------------------------------------------*/
//extern uint16_t somevariable; /**< Line description of somevariable */
/* Exported constants ------------------------------------------------------------*/
/* Exported macro ----------------------------------------------------------------*/

/* MMC/SD command (in SPI mode) */
#define CMD0	(0U)			/* GO_IDLE_STATE */
#define CMD1	(1U)			/* SEND_OP_COND (MMC) */
#define	ACMD41	(0x80+41U)		/* SEND_OP_COND (SDC) */
#define CMD8	(8U)			/* SEND_IF_COND */
#define CMD9	(9U)			/* SEND_CSD */
#define CMD10	(10U)			/* SEND_CID */
#define CMD12	(12U)			/* STOP_TRANSMISSION */
#define ACMD13	(0x80+13U)		/* SD_STATUS (SDC) */
#define CMD13	(13U)			/* SD_STATUS (SDC) */

#define CMD16	(16U)			/* SET_BLOCKLEN */
#define CMD17	(17U)			/* READ_SINGLE_BLOCK */
#define CMD18	(18U)			/* READ_MULTIPLE_BLOCK */
#define CMD23	(23U)			/* SET_BLOCK_COUNT (MMC) */
#define	ACMD23	(0x80+23U)		/* SET_WR_BLK_ERASE_COUNT (SDC) */
#define CMD24	(24U)			/* WRITE_BLOCK */
#define CMD25	(25U)			/* WRITE_MULTIPLE_BLOCK */
#define CMD32	(32U)			/* ERASE_ER_BLK_START */
#define CMD33	(33U)			/* ERASE_ER_BLK_END */
#define CMD38	(38U)			/* ERASE */
#define CMD55	(55U)			/* APP_CMD */
#define CMD58	(58U)			/* READ_OCR */

#define SD_R1_Idle			(1U)   	//Karta w stanie Idle
#define SD_R1_EraseReset		(2U)
#define SD_R1_IllegaCommand		(4U)	//Nierozpoznane polecenie
#define SD_R1_CommandCRCError		(8U)	//Blad CRC polecenia
#define SD_R1_EraseSeqError		(16U)
#define SD_R1_AddressError		(32U)
#define SD_R1_ParameterError		(64U)
#define SD_R1_Response			(128U)	//Bit odpowiedzi - zawsze r�wny 0

#define SD_OCR_CCS              	(1UL<<30U) 	//Bit CCS rejestru OCR
/* Exported functions ----------------------------------------------------------- */
/**
* @brief Brief description of function
*/

/* Exported Object types ---------------------------------------------------------*/
/* Exported Object constants -----------------------------------------------------*/
/* Exported Object macro ---------------------------------------------------------*/
/* Exported Object functions -----------------------------------------------------*/



#endif /* _SD_COMMANDS_H_ */

/*-------------------------------END OF FILE--------------------------------------*/
