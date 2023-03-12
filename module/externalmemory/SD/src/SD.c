/** @file microSD.c
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Nov 12, 2022
* @version 	1.0.0
* @copyright 	© 2022. All Rights Reserved.
*
* @brief brief description of microSD.c.
*
* @page microSD.c
* @details Detail description of microSD.c.
*
*/

/* Includes ----------------------------------------------------------------------*/
#include <stdint.h>

#include <cmsis_gcc.h>
#include <stm32f091xc.h>


#include <STM32/SPI/inc/SPI.h>
#include <STM32/GPIO/inc/gpio.h>
#include <utils/delay/inc/delay.h>

#include "../inc/ffconf.h"
#include <ThirdParty/FatFS/source/inc/ff.h>

//#include <STM32/DMA/inc/DMA.h>

#include "../inc/SD.h"
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

uint8_t SD_Status;               //Co aktualnie jest podpiête
uint8_t SD_Type;                 //Typ karty - SD lub SDHC

SD_CIDReg * CID;
SD_CSDRegv1 * CSD;
uint64_t size ;

uint8_t global_buffer [1024];
uint8_t global_buffer2 [512];

#include "../FatFS/source/inc/diskio.h"

/* Private function prototypes ---------------------------------------------------*/
/*
  Function:
  Input Data:
  Action:
*/
//utils
uint64_t check(SD_CSDRegv1 * preg);

uint8_t SD_init(void);

uint32_t SD_GetR7(void);

uint8_t SD_CardInitV1(void);
uint8_t SD_CardInitV2(void);

void SPI_SD_CS(uint8_t SS_en);
void SD_CRC7(uint8_t *crc, uint8_t byte);

uint8_t SD_SendCMD(uint8_t cmd, uint32_t arg);
uint8_t SD_WaitForReady();
uint8_t SD_GetResponse(void *buf, uint8_t size);

uint8_t SD_Rec_Datablock(uint8_t *buff, uint16_t size);
uint8_t SD_Sendblock(const uint8_t *buff, uint8_t token);

uint8_t SD_disk_read (uint8_t *buff, uint32_t sector, uint8_t count);
uint8_t SD_disk_write(const uint8_t *buff, uint32_t sector, uint8_t count);

/* Private functions -------------------------------------------------------------*/

/** 
 * @fn uint8_t Addition(int x, int y)
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
  if(preg->CSD_Struct == 0)
  {
    size = (preg->C_Size + 1) * (1UL << preg->Read_Bl_Len) * (1UL << (preg->C_Size_mult + 2));
  }
  else
  {
    size = (((SD_CSDRegv2*)preg)->C_Size + 1) * 524288ULL; // C_Size zawiera liczbę bloków
							    // po 512 kB
  }

  return size;
}

uint8_t SD_init(void)
{
  uint8_t i, ret;

  //SPI init
  SPI_DMA_TX_conf(DMA1_Stream4);
  SPI_DMA_RX_conf(DMA1_Stream3);

  SPI_init_MicroSD(SPI2, 0);

  __DSB();
  __ISB();

  __NOP();
  __NOP();

  SPI_set_baud_rate(SPI2, SPI_BAUDRATE_DIV_64);	//przy 16MHz daje 250kHz

  SPI_SD_CS(0);

  for(i = 0; i < 20; i++)
    {
      SPI_write_data(SPI2, 0xff);
    }

  i = 10;

  do
    {
      ret = SD_SendCMD(CMD0, 0);
    } while((ret != SD_R1_Idle) && --i);


  if(!i)
    {
      SD_Status = STA_NODISK;	//SD_NoCard
      return 0;
    }


  i = 10;
  do
    {
      ret = SD_SendCMD(CMD8, 0x1aa);

    } while ((ret & 0xc0) && --i);	//R7 response


  uint8_t result;

  if(ret == 0x05) { result = SD_CardInitV1(); }
  else 		  { result = SD_CardInitV2(); } 	//Z jak� kart� mamy do czynienia

  if(result == 0) {  SD_Status = STA_NODISK; }

  SPI_set_baud_rate(SPI2, SPI_BAUDRATE_DIV_4);

  SPI_SD_CS(1);

  return result;
}

uint8_t SD_CardInitV1()
{
  uint8_t i;

  for(i = 0; i < 255; i++)
  {
    if(SD_SendCMD(ACMD41, 0) == 0) { break; }		//Karta w tryb aktywny
    else 			   { delay_ms(10); }

  }


  if(i == 255) { return 0; }      //Karta nie akceptuje polecenia - uszkodzona?

  SD_GetR7();                     //Co prawda mamy odpowied� R3, ale jej d�ugo�� jest taka sama jak R7
  SD_SendCMD(CMD16, 512);         //D�ugo�� bloku 512 bajt�w

  SD_Status = 0;	//sd_sd
  SD_Type = CT_SD1;

  return 1;
}

uint8_t SD_CardInitV2()
{
  uint16_t i;
  uint32_t r7;

  r7 = SD_GetR7();

  if(r7 != 0x1aa) { return 0; }  //B�edne napi�cie pracy karty

  for(i = 0; i < 255; i++)
  {

    if(SD_SendCMD(ACMD41, SD_OCR_CCS) == 0)  { break; }		//Karta w tryb aktywny
    else 				     { delay_ms(40); }

  }

  if(i > 255) { return 0; }           //Karta nie akceptuje polecenia - uszkodzona?

  if(SD_SendCMD(CMD58, 0) == 0)
  {
    SD_Status = 0;

    if(SD_GetR7() & SD_OCR_CCS) { SD_Type = CT_SD2; } //SD_SDHC | Pobierz OCR
    else 			{ SD_Type = CT_SD1; }
  }

  return 1;
}

uint32_t SD_GetR7()  //Pobierz odpowied� typu R7
{
  uint32_t R7 = 0;

  for(uint8_t i = 0; i < 4; i++)
  {
    R7 <<= 8;
    R7 |= SPI_read_byte_v2(SPI2);
  }

  return R7;
}

uint8_t SD_SendCMD(uint8_t cmd, uint32_t arg)
{
  uint8_t crc=0, res;

  if(cmd & 0x80)
  {
    cmd &= 0x7F;            		//Skasuj najstarszy bit polecenia
    res = SD_SendCMD(CMD55, 0);  		//Kolejne polecenie nale�y do grupy ACMD

    if(res > 0x01) { return res; }	//Polecenie CMD55 zako�czy�o si� b��dem
  }

  SPI_SD_CS(0);         //Deaktywuj kart�
  SPI_SD_CS(1);          //Aktywuj kart�


  cmd |= 0x40;                //najstarsze dwa bity zawsze s� r�wne 01

  SPI_write_data(SPI2, cmd);
  SD_CRC7(&crc, cmd);

  for(uint8_t i = 0; i < 4; i++)
  {
    SPI_write_data(SPI2, (arg >> 24) & 0xff);
    SD_CRC7(&crc, (arg >> 24) & 0xff);
    arg <<= 8;
  }

  crc = (crc << 1) | 1;        		//CRC7 dla SD jest przesuni�te o jeden bit w lewo i ma ustawiony najm�odszy bit
  SPI_write_data(SPI2, crc);          	//Wy�lij CRC polecenia

  uint8_t i = 10;         //Odpowied� mo�e nadej�� od 1 do 10 bajt�w po poleceniu
  do
  {
    res = SPI_read_byte_v2(SPI2);
  } while ((res & 0x80) && --i);

  return res;                //Po wys�aniu polecenia karta pozostaje wybrana w celu odczytu/zapisu kolejnych bajt�w
}

void SPI_SD_CS(uint8_t SS_en)
{
  if(SS_en)
  {
    MICROSD_SPI_CS_CLR;	//Aktywuj kart� SD
    SD_WaitForReady();  //Zaczekaj a� karta b�dzie gotowa
  }
  else
  {
    MICROSD_SPI_CS_SET;
    SPI_write_data(SPI2, 0xff);        //Karta ulega deaktywacji po otrzymaniu kolejnego zbocza sygna�u SCK
  }
}

void SD_CRC7(uint8_t *crc, uint8_t byte)  //Wylicza CRC7 dla karty, pocz�tkowo crc=0
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
  uint32_t counter = 80000;              				//Czekamy maksymalnie ok. 500 ms

  SPI_write_data(SPI2, 0xff);
  do									//Zaczekaj na gotowo�� karty - sygna� CS musi by� wcze�niej aktywowany
  {
    if(SPI_read_byte_v2(SPI2) == 0xff) { break; }

    delay_us(100);

  } while (--counter);

  return counter ? 1 : 0;      //Czy wyst�pi� timeout?
}

uint8_t SD_Rec_Datablock(uint8_t *buff, uint16_t size)
{
  uint8_t rec, timeout;

  timeout = 200;
  do
  {
    delay_us(500);                  	//Zanim blok danych b�dzie gotowy potrzebujemy chwilk�
    rec = SPI_read_byte_v2(SPI2);
  } while((rec == 0xFF) && timeout--); //Czekamy na otrzymanie 0xfe, ale max 100 ms

  if(rec != 0xfe) { return 0; }		 //B��d - nie ma pocz�tku danych

  do
  {						         //Odbierz blok danych
    *buff = SPI_read_byte_v2(SPI2);
    buff++;

  } while(--size);

  SPI_read_byte_v2(SPI2);
  SPI_read_byte_v2(SPI2);

  return 1;
}

uint8_t SD_Sendblock(const uint8_t *buff, uint8_t token)  //Wy�lij 512-bajtowy blok danych i zako�cz go tokenem
{
  uint16_t resp;
  uint16_t counter;

  if(SD_WaitForReady() == 0) { return 0; }//Zaczekaj na gotowo�� karty

  SPI_write_data(SPI2, token);		//Wy�lij token pocz�tku/ko�ca danych
  if(token != 0xfd)                   //0xfd to token ko�ca danych - po nim nic nie wysy�amy
  {
    counter = 512;

    do
    {
      SPI_write_data(SPI2, *buff);	//Wy�lij dane
      buff++;
    } while(--counter);

    //send needless CRC16
    SPI_read_byte_v2(SPI2);
    SPI_read_byte_v2(SPI2);

    //resp nie jest zerowy
    resp = (uint8_t) SPI_read_byte_v2(SPI2);			//Odczytaj odpoweid� karty

    //resp &= 0x1F;			//(resp & 0x1F)

    if((SPI2->DR & 0x1F) != 0x05)
      {
	return 0;
      }	//Sprawd� czy karta zaakceptowa�a dane
  }

  return 1;
}

uint8_t SD_disk_read (uint8_t *buff, uint32_t sector, uint8_t count)
{
  if(SD_Status != 0) { return RES_NOTRDY; }	//SD_NoCard
  if(SD_Type == CT_SD1) { sector *= 512; }	//SDSC adresowana jest bajtami

  SPI_SD_CS(1);

  if(count == 1)
  {
    //Odczytujemy pojedynczy sektor
    if((SD_SendCMD(CMD17, sector) == 0) && SD_Rec_Datablock(buff, 512)) { count = 0; }
  }
  else
  {				//Odczytujemy kilka sektor�w na raz
    if(SD_SendCMD(CMD18, sector) == 0)
    {
      do
      {
	if(!SD_Rec_Datablock(buff, 512)) { break; }
	buff += 512;
      } while(--count);
      SD_SendCMD(CMD12, 0);				//Koniec transmisji
    }
  }

  SPI_SD_CS(0);

  return (count) ? (RES_ERROR) : (RES_OK);
}

uint8_t SD_disk_write(const uint8_t *buff, uint32_t sector, uint8_t count)
{
  if(SD_Status != 0) { return RES_NOTRDY; }
  if(SD_Type == CT_SD1)	{ sector *= 512; }	//SDSC adresowana jest bajtami

  SPI_SD_CS(1);

  if(count == 1)
  {	//Zapisujemy pojedynczy sektor
    if((SD_SendCMD(CMD24, sector) == 0) && SD_Sendblock(buff, 0xfe)) { count = 0; }
  }
  else
  {				//Zapisujemy kilka sektor�w na raz
    SD_SendCMD(ACMD23, count);
    if(SD_SendCMD(CMD25, sector) == 0)
     {
	do
	{
	  if (!SD_Sendblock(buff, 0xfc)) { break; }
	  buff += 512;
	} while (--count);

	if (!SD_Sendblock(0, 0xfd)) { count=1; }//Token ko�ca wielobajtowego bloku danych
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
  else 	   { return SD_disk_read(buff, sector, count); }
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
  else 	   { return SD_disk_write(buff, sector, count); }
}

#endif

/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/
#if _USE_IOCTL

uint8_t SD_GetResponse(void *buf, uint8_t size)
{
  uint8_t i = 10;

  while((SPI_read_byte_v2(SPI2) != 0xfe) && (--i));

  if(!i) { return 0; }

  //i = 0;
  while(size)
  {
    ((uint8_t*)buf)[size-1] = SPI_read_byte_v2(SPI2);
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
  if(SD_Status != 0) { return RES_NOTRDY; }    //Pamiêæ niezainicjowana

  DRESULT res = RES_OK;

  switch(cmd)
  {
    case GET_SECTOR_SIZE:
			 *((DWORD*)buff)=512;         //D³ugoœæ sektora 512 bajtów
			 break;

    case GET_SECTOR_COUNT:
    {
			char buf[16];
			SD_CSDRegv1 *csd=(SD_CSDRegv1*)buf;
			uint8_t r1=SD_SendCMD(CMD9, 0);  //Odczytaj CSD
			if(r1==0)
			  {

			    SD_GetResponse(csd->reg, 16);
			    uint64_t size;  //Rozmiar karty

			    if(csd->CSD_Struct == 0)
			      {
				  size=(csd->C_Size + 1) * (1ULL << csd->Read_Bl_Len) * (1UL << (csd->C_Size_mult + 2));
			      }
			    else
			      {
				size=(((SD_CSDRegv2*)csd)->C_Size + 1) * 524288ULL;  //C_Size zawiera liczbê bloków po 512 kB
			      }

			    *((DWORD*)buff) = size/512;      //Zwracami liczbê 512-bajtowych sektorów
			  }
			else
			  {
			    res = RES_NOTRDY;
			  }
    }
			  break;

    case GET_BLOCK_SIZE:
		        *((DWORD*)buff)=1;           //Ile mo¿na na raz skasowaæ sektorów
			break;
    case CTRL_SYNC:
			break;
//    case CTRL_ERASE_SECTOR:
//			break;
    default:
	    res = RES_PARERR;              //Nieznane polecenie
  }

  return res;

}
#endif

#if _USE_WRITE

DWORD get_fattime (void)
{
  return 0;  //B³êdnie, nale¿y tu zwróciæ poprawn¹ datê
}

#endif
/*-------------------------------END OF FILE--------------------------------------*/
