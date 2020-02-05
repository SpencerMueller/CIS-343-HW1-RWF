#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wav.h"
#include "file.h"

int main(int argc, char** argv){
	//the size of the file that will be returned from the read_file function
	size_t fileSize = 0;
	//filename1 will be our first argument
	char* filename1 = argv[1];
	//filename2 will be our second argument
	char* filename2 = argv[2];
	//our buffer that we will utilize to malloc and create dynamic memory
	char* buffer;
	//used to create the "=" border and look nice
	int nameSize = 0;
	//create a new wav_file struct called wav1 similar to wav1 in wav.c
	wav_file* wav1;

	//print out the arguments to see what the user put
	for(int i = 0; i < argc; i++){
		printf("%s\n", argv[i]);
	}
	//new line for aesthetic
	printf("\n");

	//insert filename 1 and the address of the buffer to read_file
	fileSize = read_file(filename1, &buffer);
	//insert filename 2 and the buffer, and lastly the size of the file
	write_file(filename2, buffer, fileSize);
	//parsing the wav file and its contents
	wav1=parse(buffer);

	//purely for aesthetic to print out the name of the second file we are writing to
	printf("File: %s \n", argv[2]);
	//get the length of the file name
	nameSize = strlen(argv[2]);
	//print a "=" character for each filename character plus 6 for "File: " to look nice
	for(int i = 0; i < nameSize + 6; i++){
	printf("=");
	}
	//new line for aesthetic
	printf("\n");	

	//print out the file size and chunk size
	printf("- File size is %zu. Read %d bytes.\n\n", fileSize, wav1->chunkSize);
	//print out the format
	printf("- Format is \"");
	//mayVary is 4 characters, so print out each character
       	for(int i = 0; i < 4; i++){
		//print out mayVary's characters
		printf("%c", wav1->mayVary[i]);
	}
	//print out the format data length
	printf("\" with format data length %d.\n\n", wav1->lengthOfFmtSection); 
	//print out the format type
	printf("- Format type is ");
	//dontSaydontUse is 4 characters so print out each character
	for(int i = 0; i < 4; i++){
		//print out dontSaydontUse's characters
		printf("%c", wav1->dontSaydontUse[i]);
	}
	//print out the rest of the sentence for aesthetic
	printf("fmt.\n\n");
	//print out the number of channels and sample rate
	printf("- %d channels with a sample rate of %d.\n\n", wav1->numChannels, wav1->sampleRate);
	//print out the block alignment and sample rate
	printf("- %d byte rate, %d alignment, %d bits per sample.\n\n", 
			wav1->byteRate, wav1->blockAlignment, wav1->bitsPerSample);
	//print out the data type
	printf("- Data is \"");
	//beginDataSection is 4 characters so print out each character
	for(int i = 0; i < 4; i++){
		//print out beginDataSection's characters
		printf("%c", wav1->beginDataSection[i]);
	}
	//print out the data size	
	printf("\" and data size is %d.\n\n", wav1->dataSize);	


	//we always free the memory we allocated
	free(buffer);

	//return
	return 0;	
}

