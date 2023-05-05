/*
 =============================================================================+
 Name        : _WAV_DECODER.h
 Author      : Mariusz Mikulski
 Date	     : Apr 2, 2023
 Version     : 0.0.1
 Copyright   : Your copyright notice (� 2021. All Rights Reserved.)
 Description : Write description of file. 
 =============================================================================+
*/
#ifndef _WAV_DECODER_H_
#define _WAV_DECODER_H_

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


typedef struct WAV_HEADER
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

} wav_header_t;



#endif /* _WAV_DECODER_H_ */
