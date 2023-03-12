/** @file SD.c
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Nov 12, 2022
* @version 	1.0.0
* @copyright 	© 2022. All Rights Reserved.
*
* @brief brief description of SD.c
*
* @page SD.c
* @details Detail description of SD.c
*
*/

/* Includes ----------------------------------------------------------------------*/
#include <stdint.h>

#include <cmsis_gcc.h>
#include <stm32f091xc.h>

#include <stm32/dma/inc/dma.h>
#include <STM32/spi/inc/spi.h>
#include <STM32/gpio/inc/gpio.h>
#include <utils/delay/inc/delay.h>

#include "../interface/FatFS/source/inc/ffconf.h"
#include "../interface/FatFS/source/inc/ff.h"

//#include <STM32/DMA/inc/DMA.h>

#include "../inc/SDv2.h"
/* Private typedef ---------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------*/
/* These types must be 16-bit, 32-bit or larger integer */
typedef int		INT;
typedef unsigned int	UINT;

/* These types must be 8-bit integer */
typedef char		CHAR;
typedef unsigned char	UCHAR;
typedef unsigned char	BYTE;

/* These types must be 16-bit integer */
typedef short		SHORT;
typedef unsigned short	USHORT;
typedef unsigned short	WORD;
typedef unsigned short	WCHAR;

/* These types must be 32-bit integer */
typedef long		LONG;
typedef unsigned long	ULONG;
typedef unsigned long	DWORD;

uint8_t global_buffer [1024];
uint8_t global_buffer2 [512];

#include "../interface/FatFS/source/inc/diskio.h"

uint8_t SD_Status;		/**< Co aktualnie jest podpiete */
uint8_t SD_Type;		/**< Typ karty - SD lub SDHC */

SD_CIDReg * CID;
SD_CSDRegv1 * CSD;
uint64_t size;

/* Private function prototypes ---------------------------------------------------*/
/*
  Function:
  Input Data:
  Action:
*/
static void SPI_init(SPI_TypeDef * __restrict pSPI, uint8_t SPI_CS_mode);
//static void DMA_peripheral_conf(DMA_Channel_TypeDef * pDMA_Channel);
//static void DMA_memory_conf(DMA_Channel_TypeDef * pDMA_Channel);

//utils
uint64_t check(SD_CSDRegv1 * preg);

uint32_t SD_GetR7(void);

uint8_t SD_CardInitV1(void);
uint8_t SD_CardInitV2(void);

void SPI_SD_CS(uint8_t SS_en);
void SD_CRC7(uint8_t *crc, uint8_t byte);

uint8_t SD_SendCMD(uint8_t cmd, uint32_t arg);
uint8_t SD_WaitForReady();
uint8_t SD_GetResponse(void *buf, uint8_t size);

uint8_t SD_readDataBlock(uint8_t *buff, uint16_t size);
uint8_t SD_sendDataBlock(const uint8_t *buff, uint8_t token);

uint8_t SD_disk_read (uint8_t *buff, uint32_t sector, uint8_t count);
uint8_t SD_disk_write(const uint8_t *buff, uint32_t sector, uint8_t count);

/* Private functions -------------------------------------------------------------*/

void SPI_init(SPI_TypeDef * __restrict pSPI, uint8_t SPI_CS_mode)
{

  GpioPinConfig(SD_SPI_MOSI_PORT, SD_SPI_MOSI_PIN, gpio_AF0_PP_HS);
  GpioPinConfig(SD_SPI_MIS0_PORT, SD_SPI_MIS0_PIN, gpio_AF0_PP_HS);	//gpio_AF0_PP_HS
  GpioPinConfig(SD_SPI_SCK_PORT, SD_SPI_SCK_PIN, gpio_AF0_PP_HS);

  //mozna to rozbic na funkcje
  if(SPI_CS_mode == 0)
    {
      //NSS - GPIO
      GpioPinConfig(SD_SPI_CS_PORT, SD_SPI_CS_PIN, gpio_output_PP_HS);

      //software CS
      SPI_enableSlaveSoftwareManagment(pSPI);
      pSPI->CR1 |= SPI_CR1_SSI;
    }
  else
    {
      //NSS hardware manage
      GpioPinConfig(SD_SPI_CS_PORT, SD_SPI_CS_PIN, gpio_AF0_PP_HS);

      //hardware CS
      SPI_disableSlaveSoftwareManagment(pSPI);
      pSPI->CR2 |= SPI_CR2_SSOE;
    }

  SPI_setBaudRate(pSPI, SPI_BAUDRATE_DIV_2);
  SPI_setMode(pSPI, SPI_MODE_0);
  SPI_setDataLength(pSPI, SPI_DATA_LENGTH_8_BIT);
  SPI_setReceptionFiFoTreshold(pSPI, SPI_RX_FIFO_TRESHOLD_GREATER_OR_EQUAL_8b);
  SPI_setDataOrder(pSPI, SPI_DATA_ORDER_MSB_FIRST);
  SPI_setFrameFormat(pSPI, SPI_FRAME_FORMAT_MOTOROLA);
  SPI_setMasterSlaveMode(pSPI, SPI_MASTER_MODE);

  SPI_Enable(pSPI);

}

/** 
 * @fn uint64_t check(SD_CSDRegv1 * preg)
 * 
 * @details
 *
 * @param[in] x operand 1
 * @param[in] y operand 2
 *
 * @return result of Addition
 */
uint64_t check(SD_CSDRegv1 * preg)
{
  extern uint64_t size;

  if(preg->CSD_Struct == 0)
  {
    size = (preg->C_Size + 1) * (1UL << preg->Read_Bl_Len) * (1UL << (preg->C_Size_mult + 2));
  }
  else
  {
    size = (((SD_CSDRegv2*)preg)->C_Size + 1) * 524288ULL; 	/**< C_Size zawiera liczbę bloków po 512 kB */

  }

  return size;
}

uint8_t SD_init(void)
{
  uint8_t i, ret, result;

  //SPI init
  //SPI_DMA_TX_conf(DMA1_Stream4);
  //SPI_DMA_RX_conf(DMA1_Stream3);

  SPI_init(SD_SPI_USED, 0);

  __DSB();
  __ISB();

  __NOP();
  __NOP();

  SPI_setBaudRate(SD_SPI_USED, SPI_BAUDRATE_DIV_256);	/**< max 400kHz | przy 48MHz daje 375 kHz */

  SPI_SD_CS(0);

  for(i = 0; i < 20; i++)
    {
      SPI_sendData(SD_SPI_USED, 0xff);
    }

  i = 10;

  do
    {
      ret = SD_SendCMD(CMD0, 0);
    } while((ret != SD_R1_Idle) && --i);


  if(!i)
    {
      SD_Status = STA_NODISK;		/**< SD_NoCard */
      return 0;
    }

  i = 10;

  do
    {
      ret = SD_SendCMD(CMD8, 0x1aa);

    } while ((ret & 0xc0) && --i);	/**< R7 response */


  if(ret == 0x05) { result = SD_CardInitV1(); }
  else 		  { result = SD_CardInitV2(); } 	/**< Z jaka karta mamy doczynienia */

  if(result == 0) {  SD_Status = STA_NODISK; }

  SPI_setBaudRate(SD_SPI_USED, SPI_BAUDRATE_DIV_16);	/**< max 25MHz | przy 48MHz daje 3MHz */

  SPI_SD_CS(1);



  return result;
}

uint8_t SD_CardInitV1()
{
  uint8_t i;

  for(i = 0; i < 255; i++)
  {
    if(SD_SendCMD(ACMD41, 0) == 0) { break; }		/**< Karta w tryb aktywny */
    else 			   { delay_ms(10); }

  }


  if(i == 255) { return 0; }	/**< Karta nie akceptuje polecenia - uszkodzona? */

  SD_GetR7();			/**< Co prawda mamy odpowied� R3, ale jej d�ugo�� jest taka sama jak R7 */
  SD_SendCMD(CMD16, 512);	/**< Dlugosc bloku 512 bajtow */

  SD_Status = SD_SD;		/**< sd_sd */
  SD_Type = CT_SD1;

  return 1;
}

uint8_t SD_CardInitV2()
{
  uint16_t i;
  uint32_t r7;

  r7 = SD_GetR7();

  if(r7 != 0x1aa) { return 0; }  /**< bledne napiecie pracy karty */

  for(i = 0; i < 255; i++)
  {

    if(SD_SendCMD(ACMD41, SD_OCR_CCS) == 0)  { break; }		/**< karta w tryb aktywny */
    else 				     { delay_ms(40); }

  }

  if(i > 255) { return 0; }           /**< Karta nie akceptuje polecenia - uszkodzona? */

  if(SD_SendCMD(CMD58, 0) == 0)
  {
    SD_Status = 0;

    if(SD_GetR7() & SD_OCR_CCS) { SD_Type = CT_SD2; } /**< SD_SDHC | Pobierz OCR */
    else 			{ SD_Type = CT_SD1; }
  }

  return 1;
}

uint32_t SD_GetR7()  	/**< Pobierz odpowied� typu R7 */
{
  uint32_t R7 = 0;

  for(uint8_t i = 0; i < 4; i++)
  {
    R7 <<= 8;
    R7 |= (uint8_t) SPI_readData(SD_SPI_USED);
  }

  return R7;
}

uint8_t SD_SendCMD(uint8_t cmd, uint32_t arg)
{
  uint8_t crc=0, res;

  if(cmd & 0x80)
  {
    cmd &= 0x7F;            		/**< Skasuj najstarszy bit polecenia */
    res = SD_SendCMD(CMD55, 0);  	/**< Kolejne polecenie nalezy do grupy ACMD */

    if(res > 0x01) { return res; }	/**< polecienie cmd55 zakoczylo sie bledem */
  }

  SPI_SD_CS(0);         		/**< deaktywuj karte */
  SPI_SD_CS(1);         		/**< aktywuj karte */


  cmd |= 0x40;          		/**< najstarsze bity zawsze rowne 01 */

  SPI_sendData(SD_SPI_USED, cmd);
  SD_CRC7(&crc, cmd);

  for(uint8_t i = 0; i < 4; i++)
  {
    SPI_sendData(SD_SPI_USED, (arg >> 24) & 0xff);
    SD_CRC7(&crc, (arg >> 24) & 0xff);
    arg <<= 8;
  }

  crc = (crc << 1) | 1;        		/**< CRC7 dla SD jest przesuniete o jeden bit w lewo i ma ustawiony najm�odszy bit */
  SPI_sendData(SD_SPI_USED, crc);       /**< Wyslij crc polecenia */

  uint8_t i = 10;			/**< Odpowiedz moze nadejdzie od 1 do 10 bajtow po wyslaniu polecenia */
  do
  {
    res = (uint8_t) SPI_readData(SD_SPI_USED);
  } while ((res & 0x80) && --i);

  return res;				/**< Po wys�aniu polecenia karta pozostaje wybrana w celu odczytu/zapisu kolejnych bajtow */
}

void SPI_SD_CS(uint8_t SS_en)
{
  if(SS_en)
  {
    SD_SPI_CS_CLR;			/**< aktywuj karte sd */
    SD_WaitForReady();  		/**< zaczekaj az karta bedzie gotowa */
  }
  else
  {
    SD_SPI_CS_SET;
    SPI_sendData(SD_SPI_USED, 0xff);	/**< Karta ulega dezaktywacji po otrzymaniu kolejnego zbocza sygnalu SCK */
  }
}

void SD_CRC7(uint8_t *crc, uint8_t byte)  /**< Wylicza CRC7 dla karty, poczatkowo crc = 0 */
{
  for (uint8_t i=0; i < 8; i++)
  {
    *crc <<= 1;

    if ((((byte & 0x80) ^ (*crc & 0x80)) != 0))
    {
      *crc ^= 0x09;
    }

    byte <<= 1;
  }

}


uint8_t SD_WaitForReady()
{
  uint32_t counter = 500;             /**< Czekamy maksymalnie ok. 500 ms */

  SPI_sendData(SD_SPI_USED, 0xff);
  do					/**< zaczekaj na gotowosc karty - sygnal CS musi byc wczesniej aktywowany */
  {
    if((uint8_t) SPI_readData(SD_SPI_USED) == 0xff) { break; }

    delay_us(100);

  } while (--counter);

  return counter ? 1 : 0;		/**< czy wystatpil timeout */
}

uint8_t SD_readDataBlock(uint8_t *buff, uint16_t size)
{
  uint8_t rec, timeout;

  timeout = 200;
  do
  {
    delay_us(500);                  	/**< zanim blok danych bedzie gotowy potrzebujemy chwilke poczekac */
    rec = (uint8_t) SPI_readData(SD_SPI_USED);

  } while((rec == 0xFF) && timeout--); 	/**< Czekamy na otrzymanie 0xfe, ale max 100 ms */

  if(rec != 0xfe) { return 0; }		/**< blad - nie ma poczatku danych */

  do
  {					/**< odbierz blok danych */
    *buff = (uint8_t) SPI_readData(SD_SPI_USED);
    buff++;

  } while(--size);

  SPI_readData(SD_SPI_USED);
  SPI_readData(SD_SPI_USED);

  return 1;
}

uint8_t SD_sendDataBlock(const uint8_t *buff, uint8_t token)  /**< Wyslij 512B blok danych i zakoncz go tokenem */
{
  uint16_t resp;
  uint16_t counter;

  if(SD_WaitForReady() == 0) { return 0; }	/**< zaczekaj na gotowosc karty */

  SPI_sendData(SD_SPI_USED, token);		/**< wyslij token poczatku/konca danych */
  if(token != 0xfd)                   		/**< 0xfd to token konca danych - po nim nic nie wysylamy */
  {
    counter = 512;

    do
    {
      SPI_sendData(SD_SPI_USED, *buff);	/**< wyslij dane */
      buff++;
    }
    while(--counter);

    //send needless CRC16
    SPI_readData(SD_SPI_USED);
    SPI_readData(SD_SPI_USED);

    //resp nie jest zerowy
    resp = (uint8_t) SPI_readData(SD_SPI_USED);	/**< odczytaj odpowiedz karty */

    //resp &= 0x1F;				/**< (resp & 0x1F) */

    if((SPI2->DR & 0x1F) != 0x05)
      {
	return 0;				/**< sprawdz czy karta zaakceptowala dane */
      }
  }

  return 1;
}

uint8_t SD_disk_read (uint8_t *buff, uint32_t sector, uint8_t count)
{
  if(SD_Status != 0) 	{ return RES_NOTRDY; }	/**< SD_NoCard */
  if(SD_Type == CT_SD1) { sector *= 512; }	/**< SDSC adresowana jest bajtami */

  SPI_SD_CS(1);

  if(count == 1)
  {
    //Odczytujemy pojedynczy sektor
    if((SD_SendCMD(CMD17, sector) == 0) && SD_readDataBlock(buff, 512)) { count = 0; }
  }
  else
  {						/**< odczytujemy kilka sektorow na raz */
    if(SD_SendCMD(CMD18, sector) == 0)
    {
      do
      {
	if(!SD_readDataBlock(buff, 512)) { break; }
	buff += 512;
      } while(--count);
      SD_SendCMD(CMD12, 0);			/**< Koniec transmisji */
    }
  }

  SPI_SD_CS(0);

  return (count) ? (RES_ERROR) : (RES_OK);
}

uint8_t SD_disk_write(const uint8_t *buff, uint32_t sector, uint8_t count)
{
  if(SD_Status != 0) 	{ return RES_NOTRDY; }
  if(SD_Type == CT_SD1)	{ sector *= 512; }	/**< SDSC adresowana jest bajtami */

  SPI_SD_CS(1);

  if(count == 1)
    {
    if((SD_SendCMD(CMD24, sector) == 0) && SD_sendDataBlock(buff, 0xfe)) { count = 0; }	/**< zapis pojedynczego sektora */
    }
  else	/**< zapis kilku sektorow na raz */
    {
      SD_SendCMD(ACMD23, count);
      if(SD_SendCMD(CMD25, sector) == 0)
	{
	  do
	    {
	      if (!SD_sendDataBlock(buff, 0xfc)) { break; }
	      buff += 512;
	    } while (--count);

	  if (!SD_sendDataBlock(0, 0xfd)) { count=1; }	/**< token konca wielobajtowego bloku danych */
	}
    }

  SPI_SD_CS(0);

  return (count) ? (RES_ERROR): (RES_OK);
}

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS
disk_status ( BYTE pdrv	) 		/* Physical drive nmuber to identify the drive */
{
  if(pdrv) { return STA_NOINIT; }
  else 	   { return SD_Status; }
}

/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS
disk_initialize ( BYTE pdrv ) 		/* Physical drive nmuber to identify the drive */
{
  if(pdrv) { return STA_NOINIT; }
  else
    {
      SD_init();
      return SD_Status;
    }
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT
disk_read (
	    BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	    BYTE *buff,			/* Data buffer to store read data */
  /*LBA_t*/ DWORD sector,		/* Start sector number (LBA) */
	    BYTE count			/* Number of sectors to read */
	   )
{
  if(pdrv) { return RES_ERROR; }
  else 	   { return (DRESULT) SD_disk_read(buff, sector, count); }
}

/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT
disk_write (
	    BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	    const BYTE *buff,	/* Data to be written */
/*LBA_t*/   DWORD sector,	/* Start sector in LBA */
	    BYTE count		/* Number of sectors to write */
	    )
{
  if(pdrv) { return RES_ERROR; }
  else 	   { return (DRESULT) SD_disk_write(buff, sector, count); }
}

#endif

/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/
#if _USE_IOCTL

uint8_t SD_GetResponse(void *buf, uint8_t size)
{
  uint8_t i = 10;

  while(((uint8_t) SPI_readData(SD_SPI_USED) != 0xfe) && (--i));

  if(!i) { return 0; }

  //i = 0;
  while(size)
  {
    ((uint8_t*)buf)[size-1] = (uint8_t) SPI_readData(SD_SPI_USED);
    --size;
    //((uint8_t*)buf)[i] = SPI_read_byte_v2(SPI2);
    //i++;
  }

  return 1;
}

DRESULT disk_ioctl (
		    BYTE pdrv,		/* Physical drive nmuber (0..) */
		    BYTE cmd,		/* Control code */
		    void *buff		/* Buffer to send/receive control data */
		    )
{
  if(SD_Status != 0) { return RES_NOTRDY; }    /**< pamiec niezainicjalizowana */

  DRESULT res = RES_OK;

  switch(cmd)
  {
    case GET_SECTOR_SIZE:
       *((DWORD*)buff)	= 512;			/**< dlugosc sektora 512B */
       break;

    case GET_SECTOR_COUNT:
    {
	char buf[16];
	SD_CSDRegv1 *csd=(SD_CSDRegv1*)buf;
	uint8_t r1=SD_SendCMD(CMD9, 0);  	/**< odczyt CSD */
	if(r1==0)
	  {

	    SD_GetResponse(csd->reg, 16);
	    uint64_t size;  			/**< rozmiar karty */

	    if(csd->CSD_Struct == 0)
	      {
		size=(csd->C_Size + 1) * (1ULL << csd->Read_Bl_Len) * (1UL << (csd->C_Size_mult + 2));
	      }
	    else
	      {
		size=(((SD_CSDRegv2*)csd)->C_Size + 1) * 524288ULL;  /**< C_Size zawiera liczbe blokow po 512 kB */
	      }

	    *((DWORD*)buff) = size/512;     	/**< Zwraca liczbe 512B sektorow */
	  }
	else
	  {
	    res = RES_NOTRDY;
	  }
    }
			  break;

    case GET_BLOCK_SIZE:
	  *((DWORD*)buff)=1;	/**< ile mozna na raz skasowac sektorow */
	  break;
    case CTRL_SYNC:	break;
//    case CTRL_ERASE_SECTOR:
//			break;
    default: 		res = RES_PARERR;              	/**< nieznane polecenie */
  }

  return res;

}
#endif

#if _USE_WRITE

DWORD get_fattime (void)
{
  return 0;  					/**< blad, nelezy tu zwrocic poprawna date */
}

#endif


/*-------------------------------END OF FILE--------------------------------------*/
