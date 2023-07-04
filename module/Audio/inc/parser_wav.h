/*
 =============================================================================+
 Name        : parser_wav.h
 Author      : Mariusz Mikulski
 Date	     : Apr 2, 2023
 Version     : 0.0.1
 Copyright   : Your copyright notice (� 2021. All Rights Reserved.)
 Description : Write description of file. 
 =============================================================================+
*/
#ifndef _PARSER_WAV_H_
#define _PARSER_WAV_H_

#define WAV_HEADER_SIZE				(44U)
#define WAV_HEADER_CHUNK_ID_FIELD_SIZE		(4U)
#define WAV_HEADER_CHUNK_SIZE_FIELD_SIZE	(4U)
#define WAV_HEADER_CHUNK_FORMAT_FIELD_SIZE	(4U)
#define WAV_HEADER_SUBCHUNK_1_ID_FIELD_SIZE	(4U)
#define WAV_HEADER_SUBCHUNK_1_SIZE_FIELD_SIZE	(4U)
#define WAV_HEADER_AUDIO_FORMAT_FIELD_SIZE	(2U)
#define WAV_HEADER_NUM_CHANNELS_FIELD_SIZE	(2U)
#define WAV_HEADER_SAMPLE_RATE_FIELD_SIZE	(4U)
#define WAV_HEADER_BYTE_RATE_FIELD_SIZE		(4U)
#define WAV_HEADER_BLOCK_ALLIGN_FIELD_SIZE	(2U)
#define WAV_HEADER_BITS_PER_SAMPLE_FIELD_SIZE	(2U)
#define WAV_HEADER_SUBCHUNK_2_ID_FIELD_SIZE	(4U)
#define WAV_HEADER_SUBCHUNK_2_SIZE_FIELD_SIZE	(4U)

typedef union
{
  uint32_t ChunkSize;
  uint8_t reg[4];

} ChunkSize_t;

typedef union
{
  uint32_t SubchunkSize;
  uint8_t reg[4];

} SubchunkSize_t;

typedef union
{
  uint32_t SampleRate;
  uint8_t reg[4];

} SampleRate_t;

typedef union
{
  uint32_t ByteRate;
  uint8_t reg[4];

} ByteRate_t;


struct wav_header
{

  char ChunkID[4];
  ChunkSize_t ChunkSize;
  char Format[4];
  /* fmt subchunk - describe sound data format */
  uint8_t Subchunk1ID[4];
  SubchunkSize_t Subchunk1Size;
  uint8_t AudioFormat[2];
  uint8_t NumChannels[2];
  SampleRate_t SampleRate;
  ByteRate_t ByteRate;
  uint8_t BlockAlign[2];
  uint8_t BitsPerSample[2];
  //uint8_t ExtraParamSize;
  //uint8_t ExtraParams;
  /* data subchunk - describe size of the data and the actual sound */
  uint8_t Subchunk2ID[4];
  SubchunkSize_t Subchunk2Size;
  uint8_t * Data;

};

typedef union wav_header_t
{
  uint8_t reg[WAV_HEADER_SIZE];
  struct wav_header wav;

} WAV_H;

#endif /* _PARSER_WAV_H_ */
