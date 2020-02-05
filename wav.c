#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wav.h"

wav_file* parse(char* contents){
	//creating a new wav_file struct called wav1
	wav_file* wav1;
	//A new string for the chunk size
	char* newString;
	//A new string for the sample rate
	char* newString2;
	//A new string for the byte rate
	char* newString3;
	//A new string for the data size
	char* newString4;

	//malloc 4 characters for the 4 bytes for chunk size
	newString = malloc(sizeof(char) * 4);
	//malloc 4 characters for the 4 bytes for sample rate
	newString2 = malloc(sizeof(char) * 4);
	//malloc 4 characters for the 4 bytes for byte rate
	newString3 = malloc(sizeof(char) * 4);
	//malloc 4 characters for the 4 bytes for data size
	newString4 = malloc(sizeof(char) * 4);

	//if any of these mallocs fail, present an error message to the user
	if(newString == NULL || newString2 == NULL || newString3 == NULL || newString4 == NULL){
		//put an error message if a malloc fails to work
		fputs("Memory allocation failure!", stderr);	
	}

	//Bytes 0-3 should be for RIFF
	for(int i = 0; i < 4; i++){
		//copy each character from bytes 0-3 of contents to sameVals
		wav1->sameVals[i] = contents[i];
	}
	//Bytes 4-7 should be for the chunk size (file - 8 bytes)
	for(int i = 4; i < 8; i++){
		//copy each character from bytes 4-7 of contents to newString
		newString[i - 4] = contents[i];
	}
	
	/*
	 * Note: I found a way to convert a new string of the bytes I wanted to then
	 * be scanned and represnted as an integer to get the whole chunk size from
	 * this link: stackoverflow.com/questions/10204471/convert-char-array-to-a-int-number-in-c/10204663.
	 * It really helped because I tried everything to get the chunk size with only one
	 * int and finally I found this which did exactly what I wanted.
	 */


	//sscanf newString as an integer to be represented as one integer for chunkSize as chunk size
	sscanf(newString, "%d", &wav1->chunkSize);       

	//Bytes 8-11 should be for WAVE
	for(int i = 8; i < 12; i++){
		//copy each character from bytes 8-11 of contents to dontSaydontUse
		wav1->dontSaydontUse[i - 8] = contents[i];
	}


	//Bytes 12-15 should be for fmt
	for(int i = 12; i < 16; i++){
		//copy each character from bytes 12-15 of contents to mayVary
		wav1->mayVary[i - 12] = contents[i];
	}
	
	//Bytes 16-19 should be for the lenght of the format section
	wav1->lengthOfFmtSection = contents[16];
	
	//Bytes 20-21 should be for the format type
	wav1->formatType = contents[20];
	
	//Bytes 22-23 should be for the number of channels
	wav1->numChannels = contents[22];

	//Bytes 24-27 should be for the sample rate
	for(int i = 24; i < 28; i++){
		//copy each character from bytes 24-27 of contents to newString2
		newString2[i - 24] = contents[i];
	}

	//sscanf newString as an integer to be represented as one integer for SampleRate as sample rate
	sscanf(newString2, "%d", &wav1->sampleRate);
	
	//Bytes 28-31 should be for the byte rate
	for(int i = 28; i <31; i++){
		//copy each character from bytes 28-31 of contents to newString3
		newString3[i - 28] = contents[i];
	}

	//sscanf newString3 as an integer to be represented as one integer for byteRate as byte rate
	sscanf(newString3, "%d", &wav1->byteRate);
 
	//Bytes 32-33 should be for the block alignment
	wav1->blockAlignment = contents[32];

	//Bytes 34-35 should be for the bits per sample
	wav1->bitsPerSample = contents[34];

	//Bytes 36-39 should be for the beginning of the data section
	for(int i = 36; i < 40; i++){
		//copy each character from bytes 36-39 of contents to beginDataSection
		wav1->beginDataSection[i - 36] = contents[i];
	}

	//Bytes 40-43 should be for the size of the data
	for(int i = 40; i < 44; i++){
		//copy each character from bytes 40-43 of contents to newString4 
		newString4[i - 40] = contents[i];
	}

	//sscanf newString 4 as an integer to be represented as one integer for dataSize as data size
	sscanf(newString4, "%d", &wav1->dataSize);

	//since we no longer need the strings we can free newString to free the data from the heap
	free(newString);
	//free newString2 to free the data from the heap
	free(newString2);
	//free newString3 to free the data from the heap
	free(newString3);
	//free newString4 to free the data from the heap
	free(newString4);
	//return a pointer to wav1	
	return wav1;
}
