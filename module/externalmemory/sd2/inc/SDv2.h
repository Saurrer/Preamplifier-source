/** @file SDv2.h
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Nov 12, 2022
* @version 	1.0.0
* @copyright 	© 2022. All Rights Reserved.
*
* @brief brief description of SDv2.h
*
* @page SDv2.h
* @details Detail description of SDv2.h
*
*/

/* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef _SDv2_H_
#define _SDv2_H_

/* Includes ----------------------------------------------------------------------*/
#include "SD_commands.h"
/* Exported types ----------------------------------------------------------------*/
/* Exported define ---------------------------------------------------------------*/

#define SD_INTERFACE_SPI		SPI1

#define SD_INTERFACE			SD_INTERFACE_SPI
/* Exported constants ------------------------------------------------------------*/
/* Exported macro ----------------------------------------------------------------*/

#define SD_FRAME_LENGTH						(6U)
#define SD_FRAME_ADD_START_BIT 					(SD_DefaultBuffer[0]=0x80)
#define SD_FRAME_ADD_STOP_BIT  					(SD_DefaultBuffer[6]=0x01)


//#define SD_FRAME_ADD_CMD (SD_DefaultBuffer[0]|=0x01)

/* Exported functions ----------------------------------------------------------- */
/**
* @brief Brief description of function
*/

/* Private macro -----------------------------------------------------------------*/

/* Private variables -------------------------------------------------------------*/

extern uint8_t global_buffer [1024];
extern uint8_t global_buffer2 [512];

/* Exported Object types ---------------------------------------------------------*/

typedef union
{
  uint8_t reg[16];

  struct
  {
    uint8_t crc;
    uint8_t MDT_Month		: 4;	/* miesiac produkcji */
    uint8_t MDT_Year2		: 4;
    uint8_t MDT_Year1		: 4;	/* rok produkcji od 2000 */
    uint8_t RESERVED1		: 4;	/* zera */

    uint32_t PSN;		/* serial number */
    uint8_t PRV;		/* version number */
    char PNM[5];		/* product name */
    char OID[2];		/* identyfikator producenta w ASCII */
    uint8_t MID;		/* identyfikator producenta karty */
  };

} SD_CIDReg;

typedef enum
{
  CID_CRC			= 0,
  CID_MANUFACTURER_DATE_MONTH,
  CID_MANUFACTURER_DATE_YEAR2,
  CID_MANUFACTURER_DATE_YEAR1,	/* MDT - Manufacturer Date */
  CID_PRODUCT_SERIAL_NUMBER,	/* PSN - Product serial number */
  CID_PRODUCT_REVISION,		/* PRV - Product revision */
  CID_PRODUCT_NAME,		/* PNM - Product name */
  CID_APPLICATION_ID,		/* OID - Application ID */
  CID_MANUFACTURER_ID,		/* MID - Manufacturer ID */

} CID_field;

typedef union
{
  uint8_t reg[5];
  struct
  {
    uint8_t RESERVED1		: 1;	/* 0b */
    uint8_t RESERVED2		: 1;	/* 1b */
    uint8_t RESERVED3		: 1;	/* 2b */
    uint8_t RESERVED4		: 1;	/* 3b */

    uint8_t VDD_1_6__1_7	: 1;	/* 4b */
    uint8_t VDD_1_7__1_8	: 1;	/* 5b */
    uint8_t VDD_1_8__1_9	: 1;	/* 6b */
    uint8_t VDD_1_9__2_0	: 1;	/* 7b */
    uint8_t VDD_2_0__2_1	: 1;	/* 8b */
    uint8_t VDD_2_1__2_2	: 1;	/* 9b */
    uint8_t VDD_2_2__2_3	: 1;	/* 10b */
    uint8_t VDD_2_3__2_4	: 1;	/* 11b */
    uint8_t VDD_2_4__2_5	: 1;	/* 12b */
    uint8_t VDD_2_5__2_6	: 1;	/* 13b */
    uint8_t VDD_2_6__2_7	: 1;	/* 14b */
    uint8_t VDD_2_7__2_8	: 1;	/* 15b */
    uint8_t VDD_2_8__2_9	: 1;	/* 16b */
    uint8_t VDD_2_9__3_0	: 1;	/* 17b */
    uint8_t VDD_3_0__3_1	: 1;	/* 18b */
    uint8_t VDD_3_1__3_2	: 1;	/* 19b */
    uint8_t VDD_3_2__3_3	: 1;	/* 20b */
    uint8_t VDD_3_3__3_4	: 1;	/* 21b */
    uint8_t VDD_3_4__3_5	: 1;	/* 22b */
    uint8_t VDD_3_5__3_6	: 1;	/* 23b */

    uint8_t RESERVED5		: 1;	/* 24b */
    uint8_t RESERVED6		: 1;	/* 25b */
    uint8_t RESERVED7		: 1;	/* 26b */
    uint8_t RESERVED8		: 1;	/* 27b */
    uint8_t RESERVED9		: 1;	/* 28b */
    uint8_t RESERVED10		: 1;	/* 29b */
    uint8_t RESERVED11		: 1;	/* 30b */
    uint8_t BUSY		: 1;	/* 31b */

  };

} SD_OCRreg;

typedef union
{
  uint8_t reg[16];
  struct
  {
    uint8_t crc;
    uint8_t RESERVED5          	: 2;
    uint8_t FILE_FORMAT   	: 2;
    uint8_t TMP_WRITE_PROTECT 	: 1;
    uint8_t PERM_WRITE_PROTECT 	: 1;
    uint8_t COPY            	: 1;
    uint8_t FILE_FORMAT_GRP  	: 1;
    uint8_t RESERVED4          	: 5;
    uint8_t WRITE_BL_PARTIAL 	: 1;
    uint8_t WRITE_BL_LEN  	: 4;
    uint8_t R2W_FACTOR     	: 3;
    uint8_t RESERVED3          	: 2;
    uint8_t WP_GRP_EN       	: 1;
    uint8_t WP_GRP_SIZE   	: 7;
    uint8_t SECTOR_SIZE   	: 7;
    uint8_t ERASE_BL_EN    	: 1;
    uint8_t C_SIZE_MULT   	: 3;
    uint8_t VDD_W_Curr_max 	: 3;
    uint8_t VDD_W_Curr_min 	: 3;
    uint8_t VDD_R_Curr_max 	: 3;
    uint8_t VDD_R_Curr_min 	: 3;
    uint16_t C_SIZE       	: 12;
    uint8_t RESERVED2          	: 2;
    uint8_t DSR_IMP         	: 1;
    uint8_t READ_BL_MISALLIGN  	: 1;
    uint8_t WRITE_BL_MISALLIGN 	: 1;
    uint8_t READ_BL_PARTIAL 	: 1;
    uint16_t READ_BL_LEN   	: 4;
    uint16_t CCC          	: 12;
    uint8_t TRANS_SPEED;
    uint8_t NSAC;
    uint8_t TAAC;
    uint8_t RESERVED1          	: 6;
    uint8_t CSD_STRUCTURE    	: 2;  //Wersja struktury CSD 0 -1.0, 1 -2.0
  } ;

} SD_CSDRegv1;

typedef union
{
  uint8_t reg[16];
  struct
  {
    uint8_t crc;
    uint8_t RESERVED6          	: 2;
    uint8_t FILE_FORMAT   	: 2;
    uint8_t TMP_WRITE_PROTECT  	: 1;
    uint8_t PERM_WRITE_PROTECT 	: 1;
    uint8_t COPY            	: 1;
    uint8_t FILE_FORMAT_GRP  	: 1;
    uint8_t RESERVED5         	: 5;
    uint8_t WRITE_BL_PARTIAL 	: 1;
    uint8_t WRITE_BL_LEN  	: 4;
    uint8_t R2W_FACTOR     	: 3;
    uint8_t RESERVED4          	: 2;
    uint8_t WP_GRP_EN       	: 1;
    uint8_t WP_GRP_SIZE   	: 7;
    uint8_t SECTOR_SIZE   	: 7;
    uint8_t ERASE_BL_EN    	: 1;
    uint8_t RESERVED3          	: 1;
    uint32_t C_SIZE       	: 22;
    uint8_t RESERVED2          	: 6;
    uint8_t DSR_IMP         	: 1;
    uint8_t READ_BL_MISALLIGN  	: 1;
    uint8_t WRITE_BL_MISALLIGN 	: 1;
    uint8_t READ_BL_PARTIAL 	: 1;
    uint8_t READ_BL_LEN   	: 4;
    uint16_t CCC          	: 12;
    uint8_t TRANS_SPEED;
    uint8_t NSAC;
    uint8_t TAAC;
    uint8_t RESERVED1          	: 6;
    uint8_t CSD_STRUCTURE    	: 2;  //Wersja struktury CSD 0 -1.0, 1 -2.0

  } ;

} SD_CSDRegv2;

typedef union
{
  uint8_t reg[6];

  struct
  {
    uint8_t crc;
    uint8_t OPERATION_ARGUMENT  [4];
    uint8_t OPERATION_NUMBER	: 6;
    uint8_t OPERATION_TYPE	: 1;
    uint8_t START_BIT		: 1;
  };

} SD_frame_format;

typedef union
{
  uint8_t reg[1];

  struct
  {
    uint8_t b0			: 1;	/* idle */
    uint8_t b1			: 1;	/* przerwanie operacji ERASE */
    uint8_t b2			: 1;	/* uknown cmd */
    uint8_t b3			: 1;	/* crc fail */
    uint8_t b4			: 1;	/* seq ERASE fail */
    uint8_t b5			: 1;	/* fail address */
    uint8_t b6			: 1;	/* fail cmd */
    uint8_t b7			: 1;	/* always 0 */
  };

} SD_R1_response;

typedef union
{
  uint8_t reg[1];

  struct
  {
    uint8_t b0			: 1;	/* blocked card */
    uint8_t b1			: 1;	/* protection write */
    uint8_t b2			: 1;	/* uknown fail */
    uint8_t b3			: 1;	/* fail of controller sd */
    uint8_t b4			: 1;	/* fail EEC card */
    uint8_t b5			: 1;	/* violate write protection */
    uint8_t b6			: 1;	/* erase parameter */
    uint8_t b7			: 1;	/* out of range */
  };

} SD_R2_response;

typedef union
{
  uint8_t reg[4];
} SD_R3_response;

typedef union
{
  uint8_t reg[5];
  struct
  {
    uint8_t RESPONSE_MASK;
    uint8_t ACCEPTED_VOLTAGE_VAL: 4;
    uint8_t RESERVED3		: 4;
    uint8_t RESERVED2;
    uint8_t RESERVED1		: 4;
    uint8_t OPERATION_TYPE	: 4;
  };

} SD_R7_response;


typedef enum
{
  SD_NoCard,
  SD_SD,
  SD_SDHC

} SD_CardStatus;

extern uint8_t SD_Status;		/**< Co aktualnie jest podpiete */
extern uint8_t SD_Type;			/**< Typ karty - SD lub SDHC */

extern SD_OCRreg * pOCR;
extern SD_CIDReg * pCID;
extern SD_CSDRegv1 * pCSD;

extern SD_R1_response * pR1;
extern SD_R2_response * pR2;
extern SD_R3_response * pR3;
extern SD_R7_response * pR7;

extern uint64_t size;


#ifdef __cplusplus
  extern "C" {
#endif

extern uint8_t SD_sendCMD(uint8_t cmd, uint32_t arg) __attribute__( (optimize("-O1")) );;
extern uint8_t SD_getResponse(void * buf, uint16_t buf_size);

extern void SD_SPI_CS(uint8_t SS_en);
extern void SD_CRC7(uint8_t *crc, uint8_t byte);

extern uint8_t SD_CardInitV1(void);
extern uint8_t SD_CardInitV2(void);

extern uint8_t SD_init(void);

extern uint32_t SD_GetR7(void);
extern uint8_t SD_WaitForReady(void);

extern uint8_t SD_readDataBlock(uint8_t *buff, uint16_t size);
extern uint8_t SD_sendDataBlock(const uint8_t *buff, uint8_t token);

extern uint8_t SD_disk_read (uint8_t *buff, uint32_t sector, uint8_t count);
extern uint8_t SD_disk_write(const uint8_t *buff, uint32_t sector, uint8_t count);

extern uint64_t check(SD_CSDRegv1 * preg);
extern void readOCR_reg(SD_OCRreg * preg);
extern void readCID_reg(SD_CIDReg * preg);
extern void readCSD_reg(SD_CSDRegv1 * preg);
extern void readStatus_reg(SD_R1_response * preg);

#ifdef __cplusplus
  }
#endif

/* Exported Object constants -----------------------------------------------------*/
/* Exported Object macro ---------------------------------------------------------*/
/* Exported Object functions -----------------------------------------------------*/


#endif /* _SDv2_H_ */

/*-------------------------------END OF FILE--------------------------------------*/
