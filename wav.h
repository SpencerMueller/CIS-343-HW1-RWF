#include <stdio.h>
#ifndef WAV_H_FILE
#define WAV_H_FILE

/****************************************************************************
 * wav_file is a struct that will contain all the information about the wav 
 * file and split it into different data types so we can manipulate it and 
 * present it neatly on the output and return a pointer to the struct.
 ***************************************************************************/
typedef struct wav_file {
	//Bytes 0-3
	char sameVals[4];
	//Bytes 4-7	
	int chunkSize;
	//Bytes 8-11
	char dontSaydontUse[4];
	//Bytes 12-15
	char mayVary[4];
	//Bytes 16-19
	int lengthOfFmtSection;
	//Bytes 20-21
	short formatType;
	//Bytes 22-23
	short numChannels;
	//Bytes 24-27
	int sampleRate;
	//Bytes 28-31
	int byteRate;
	//Bytes 32-33
	short blockAlignment;
	//Bytes 34-35
	short bitsPerSample;
	//Bytes 36-39
	char beginDataSection[4];
	//Bytes 40-43
	int dataSize;
	//Bytes 44-End
	char* actualData;
} wav_file;

/************************************************************************
 * parse will take in the contents of the file and then split them up and
 * respectively attribute each of the contents/bytes of the file with the 
 * correct variable and type that variable is so we can display it.
 ***********************************************************************/
wav_file* parse(char* contents);

#endif 

