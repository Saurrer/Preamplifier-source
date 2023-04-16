/** @file playlist.h
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Apr 16, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of playlist.h.
*
* @page playlist.h
* @details Detail description of playlist.h.
*
*/

/* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef _PLAYLIST_H_
#define _PLAYLIST_H_

/* Includes ----------------------------------------------------------------------*/
#include <stdint.h>
//#include <dirent.h>
#include "../../externalmemory/sd2/interface/FatFS/source/inc/ff.h"

#define PLAYLIST_STATUS_OK				(0)
#define PLAYLIST_STATUS_FAIL				(1)

#define PLAYLIST_STATUS_NO_FILES			(1)
#define PLAYLIST_STATUS_MAX_FILES			(3)
#define PLAYLIST_STATUS_WRONG_DIRECTORY_GIVEN		(4)

#define PLAYLIST_STATUS_FILENAME_NO_EXTENSION		(5)
#define PLAYLIST_STATUS_FILENAME_WRONG_EXTENSION	(6)
#define PLAYLIST_STATUS_POSITION_EXCEEDED		(7)

#define PLAYLIST_CONFIG_MAX_FILES_COUNT			(64)
#define PLAYLIST_CONFIG_MAX_FILE_NAME_LENGTH		PLAYLIST_CONFIG_MAX_FILES_COUNT

/* Exported define ---------------------------------------------------------------*/
/* Exported types ----------------------------------------------------------------*/
extern uint16_t somevariable; /**< Line description of somevariable */
/* Exported constants ------------------------------------------------------------*/
/* Exported macro ----------------------------------------------------------------*/
/* Exported functions ----------------------------------------------------------- */

/* Exported Object types ---------------------------------------------------------*/
typedef class PLAYLIST playlist_t;

class PLAYLIST
{

public:
  enum : uint8_t
  {
    FILE_EXTENSION_WAV	= 0,
  };

  PLAYLIST();
  ~PLAYLIST();

  int8_t init(DIR * dir);

  int8_t addFileName(const char * pFileName, size_t filename_len);
  int8_t getFileName(char * pFileName, uint8_t position_on_list);

  uint8_t isEmpty();
  uint8_t isFull();
  uint8_t getNumberOfFiles();

  //ToDo - zrobic wskaznic do tablicy wskaznikow
  static const char * file_extension[];
  //uint32_t ** wskaznik_do_wskaznika = &tablica_wskaznikow;

  //ToDo - zrobic wskaznik do tablicy dwuwymiarowej
  //uint32_t ** wskaznik_do_wskaznika = &tablica_wskaznikow;
  char file_name_list[64][64] {0};

  uint8_t count;
private:


};

/* Exported Object constants -----------------------------------------------------*/
/* Exported Object macro ---------------------------------------------------------*/
/* Exported Object functions -----------------------------------------------------*/



#endif /* PREAMPLIFIER_SOURCE_MODULE_AUDIO_INC_PLAYLIST_H_ */

/*-------------------------------END OF FILE--------------------------------------*/
