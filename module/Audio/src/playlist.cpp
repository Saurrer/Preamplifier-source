/** @file playlist.cpp
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Apr 16, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of playlist.cpp.
*
* @page playlist.cpp
* @details Detail description of playlist.cpp.
*
*/
/* Includes ----------------------------------------------------------------------*/
#include "../inc/playlist.h"

#include <string.h>
/* Private typedef ---------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------*/
#define FILE_NAME_DOT	'.'
/* Private macro -----------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------*/

/* Private function prototypes ---------------------------------------------------*/
/*
  Function:
  Input Data:
  Action:
*/

/* Private functions -------------------------------------------------------------*/

const char * PLAYLIST::file_extension[1] =
{
   "wav"
};

static bool find_dot_in_file_name(const void *s, size_t len);
static bool find_wav_files(const void *s, size_t len);

char PLAYLIST::file_name_list[64][64] {0};

PLAYLIST::PLAYLIST()
:count(0)
{

}

PLAYLIST::~PLAYLIST()
{

}

int8_t
PLAYLIST::init(DIR * dir)
{
  uint8_t i,j;
  FRESULT res;
  FILINFO fno;

  count = 0;

  /*
   * clearing buffer before reading files in directory
   */
  for(i = 0; i < PLAYLIST_CONFIG_MAX_FILES_COUNT; i++)
    {
      for(j = 0; j < PLAYLIST_CONFIG_MAX_FILES_COUNT; j++)
	{
	  file_name_list[i][j] = '\0';
	}
    }

  if(dir == NULL) { return PLAYLIST_STATUS_WRONG_DIRECTORY_GIVEN; }

  while(1)
    {
      res = f_readdir(dir, &fno);
      if(res != FR_OK || fno.fname[0] == 0) { break; }
      if(fno.fname[0] == '.') { continue; }

      addFileName(fno.fname, strlen(fno.fname));

//      if(fno.fattrib & AM_DIR)  { /*katalog*/}
//      else 			{/*plik*/}

    }

  return PLAYLIST_STATUS_OK;
}

int8_t
PLAYLIST::addFileName(const char * pFileName, uint8_t filename_len)
{
  if(isFull()) { return PLAYLIST_STATUS_MAX_FILES; }

  if(find_dot_in_file_name(pFileName, filename_len))
    {
      if(find_wav_files(pFileName, filename_len))
	{
	  strncpy(*(file_name_list + count), pFileName,
		  PLAYLIST_CONFIG_MAX_FILE_NAME_LENGTH);
	  count++;
	}

      else { return PLAYLIST_STATUS_FILENAME_WRONG_EXTENSION; }
    }
  else
    {
      return PLAYLIST_STATUS_FILENAME_NO_EXTENSION;
    }

  return PLAYLIST_STATUS_OK;
}

int8_t
PLAYLIST::getFileName(char * pFileName, uint8_t position_on_list)
{
  if(isEmpty()) { return PLAYLIST_STATUS_NO_FILES; }
  if(position_on_list >= PLAYLIST_CONFIG_MAX_FILES_COUNT) { return PLAYLIST_STATUS_POSITION_EXCEEDED; }

  pFileName = *(file_name_list + position_on_list);

  return PLAYLIST_STATUS_OK;
}

uint8_t
PLAYLIST::getNumberOfFiles() { return count; }

uint8_t
PLAYLIST::isEmpty() { return count == NULL; }

uint8_t
PLAYLIST::isFull() { return count == PLAYLIST_CONFIG_MAX_FILES_COUNT; }

bool
find_dot_in_file_name(const void *s, size_t len)
{
  char * pos = (char *) memchr(s, FILE_NAME_DOT, len);
  return (pos == (char *)0) ? false : true;
}

bool
find_wav_files(const void *s, size_t len)
{
  int i = 0;
  int char_match = 0;

  char * pos = (char *) memchr(s, FILE_NAME_DOT, len);

  while(*(*(PLAYLIST::file_extension) + i))
    {
      // +1 for pos address to avoid dot sign and compare only extension name
      if(*(pos + (i + 1)) == *(PLAYLIST::file_extension[PLAYLIST::FILE_EXTENSION_WAV] + i)) { char_match++; }
      i++;
    }

  size_t file_extension_len = strlen(PLAYLIST::file_extension[PLAYLIST::FILE_EXTENSION_WAV]);

  return (char_match == file_extension_len) ? true : false;
}

/*-------------------------------END OF FILE--------------------------------------*/
