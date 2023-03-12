/** @file microSD.h
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Nov 12, 2022
* @version 	1.0.0
* @copyright 	© 2022. All Rights Reserved.
*
* @brief brief description of microSD.h.
*
* @page microSD.h
* @details Detail description of microSD.h.
*
*/

/* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef SOURCE_MODULE_MICROSD_INC_MICROSD_H_
#define SOURCE_MODULE_MICROSD_INC_MICROSD_H_

/* Includes ----------------------------------------------------------------------*/
#include "SD_commands.h"
/* Exported types ----------------------------------------------------------------*/

/* Exported constants ------------------------------------------------------------*/
/* Exported macro ----------------------------------------------------------------*/

#define MICROSD_SPI_CS_SET      				GPIOB->BSRR|=GPIO_BSRR_BS12
#define MICROSD_SPI_CS_CLR      				GPIOB->BSRR|=GPIO_BSRR_BR12

#define MICROSD_ASSIGNED_PERIPH					SPI2

#define SD_FRAME_LENGTH	6
#define SD_FRAME_ADD_START_BIT (SD_DefaultBuffer[0]=0x80)
#define SD_FRAME_ADD_STOP_BIT (SD_DefaultBuffer[6]=0x01)
//#define SD_FRAME_ADD_CMD (SD_DefaultBuffer[0]|=0x01)
/* Exported functions ----------------------------------------------------------- */
/**
* @brief Brief description of function
*/


/* Private macro -----------------------------------------------------------------*/

/* Private variables -------------------------------------------------------------*/

//DMA_Module DMA;
//SD_CardStatus

typedef union
{
  uint8_t reg[16];

  struct
  {
    uint8_t crc;
    uint8_t MDT_Month	: 4;	//miesiac produkcji
    uint8_t MDT_Year2	: 4;
    uint8_t MDT_Year1	: 4;	//rok produkcji od 2000
    uint8_t reserved	: 4;	//same zera

    uint32_t PSN;		//SN
    uint8_t PRV;		//version number
    char PNM[5];		//product name
    char OID[2];		//indentyfikator producenta w ASCII
    uint8_t MID;		//indentyfikator producenta karty
  };

} SD_CIDReg;

typedef enum
{
  CID_CRC		= 0,
  CID_MANUFACTURER_DATE_MONTH,
  CID_MANUFACTURER_DATE_YEAR2,
  CID_MANUFACTURER_DATE_YEAR1,	// MDT - Manufacturer Date
  CID_PRODUCT_SERIAL_NUMBER,	// PSN - Product serial number
  CID_PRODUCT_REVISION,		// PRV - Product revision
  CID_PRODUCT_NAME,		// PNM - Product name
  CID_APPLICATION_ID,		// OID - Application ID
  CID_MANUFACTURER_ID,		// MID - Manufacturer ID

} CID_field;

typedef union
{
  uint8_t reg[16];
  struct
  {
    uint8_t crc;
    uint8_t res1          	: 2;
    uint8_t File_Format   	: 2;
    uint8_t Tmp_WR_Protect  	: 1;
    uint8_t Perm_WR_Protect 	: 1;
    uint8_t Copy            	: 1;
    uint8_t File_Frm_Group  	: 1;
    uint8_t res2          	: 5;
    uint8_t Write_BL_Partial 	: 1;
    uint8_t Write_BL_Len  	: 4;
    uint8_t R2WFactor     	: 3;
    uint8_t res3          	: 2;
    uint8_t WP_Grp_En       	: 1;
    uint8_t WP_Grp_Size   	: 7;
    uint8_t Sector_Size   	: 7;
    uint8_t Erase_Blk_En    	: 1;
    uint8_t C_Size_mult   	: 3;
    uint8_t VDD_W_Curr_max 	: 3;
    uint8_t VDD_W_Curr_min 	: 3;
    uint8_t VDD_R_Curr_max 	: 3;
    uint8_t VDD_R_Curr_min 	: 3;
    uint16_t C_Size       	: 12;
    uint8_t res5          	: 2;
    uint8_t DSR_Imp         	: 1;
    uint8_t Read_Blk_Misalign  	: 1;
    uint8_t Write_Blk_Misalign 	: 1;
    uint8_t Read_Bl_Partial 	: 1;
    uint8_t Read_Bl_Len   	: 4;
    uint16_t CCC          	: 12;
    uint8_t Tran_Speed;
    uint8_t NSAC;
    uint8_t TAAC;
    uint8_t res6          	: 6;
    uint8_t CSD_Struct    	: 2;  //Wersja struktury CSD 0 -1.0, 1 -2.0
  };

} SD_CSDRegv1;

typedef union
{
  uint8_t reg[16];
  struct
  {
    uint8_t crc;
    uint8_t res1          	: 2;
    uint8_t File_Format   	: 2;
    uint8_t Tmp_WR_Protect  	: 1;
    uint8_t Perm_WR_Protect 	: 1;
    uint8_t Copy            	: 1;
    uint8_t File_Frm_Group  	: 1;
    uint8_t res2         	: 5;
    uint8_t Write_BL_Partial 	: 1;
    uint8_t Write_BL_Len  	: 4;
    uint8_t R2WFactor     	: 3;
    uint8_t res3          	: 2;
    uint8_t WP_Grp_En       	: 1;
    uint8_t WP_Grp_Size   	: 7;
    uint8_t Sector_Size   	: 7;
    uint8_t Erase_Blk_En    	: 1;
    uint8_t res4          	: 1;
    uint32_t C_Size       	: 22;
    uint8_t res5          	: 6;
    uint8_t DSR_Imp         	: 1;
    uint8_t Read_Blk_Misalign  	: 1;
    uint8_t Write_Blk_Misalign 	: 1;
    uint8_t Read_Bl_Partial 	: 1;
    uint8_t Read_Bl_Len   	: 4;
    uint16_t CCC          	: 12;
    uint8_t Tran_Speed;
    uint8_t NSAC;
    uint8_t TAAC;
    uint8_t res6          	: 6;
    uint8_t CSD_Struct    	: 2;  //Wersja struktury CSD 0 -1.0, 1 -2.0
  };

} SD_CSDRegv2;

extern SD_CIDReg * CID;
extern SD_CSDRegv1 * CSD;
extern uint64_t size ;


extern uint8_t global_buffer [1024];
extern uint8_t global_buffer2 [512];

extern uint8_t SD_Status;               //Co aktualnie jest podpiête
extern uint8_t SD_Type;                 //Typ karty - SD lub SDHC


typedef enum
{
  SD_NoCard,
  SD_SD,
  SD_SDHC

} SD_CardStatus;


#ifdef __cplusplus
  extern "C" {
#endif


extern uint8_t SD_init(void);
extern uint32_t SD_GetR7(void);
extern uint8_t SD_CardInitV1();
extern uint8_t SD_CardInitV2();

extern void SPI_SD_CS(uint8_t SS_en);
extern void SD_CRC7(uint8_t *crc, uint8_t byte);

extern uint8_t SD_SendCMD(uint8_t cmd, uint32_t arg);
extern uint8_t SD_WaitForReady();
extern uint8_t SD_GetResponse(void *buf, uint8_t size);

extern uint8_t SD_Rec_Datablock(uint8_t *buff, uint16_t size);
extern uint8_t SD_Sendblock(const uint8_t *buff, uint8_t token);

extern uint8_t SD_disk_read (uint8_t *buff, uint32_t sector, uint8_t count);
extern uint8_t SD_disk_write(const uint8_t *buff, uint32_t sector, uint8_t count);



#ifdef __cplusplus
  }
#endif

  /* Exported Object types ---------------------------------------------------------*/
/* Exported Object constants -----------------------------------------------------*/
/* Exported Object macro ---------------------------------------------------------*/
/* Exported Object functions -----------------------------------------------------*/



#endif /* SOURCE_MODULE_MICROSD_INC_MICROSD_H_ */

/*-------------------------------END OF FILE--------------------------------------*/
