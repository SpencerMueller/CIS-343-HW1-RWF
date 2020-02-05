#include <stdio.h>
#include <stdlib.h>
#include "file.h" 

/***********************************************************************
 * Read in the a file witht the filename paramter and then malloc enough
 * space for the file, then close the file and return the size of it.
 **********************************************************************/
size_t read_file(char* filename, char** buffer){
	//the size of the file we want to allocate memory for but don't know yet
	size_t fileSize = 0;
	//create a new file pointer for reading the file
	FILE *fp; 
	//open the filename in read mode
	fp = fopen(filename, "r");

	//if the file is null or missing, give an error to the user
	if(fp == NULL){
		//put an error if there is a file read error
		fputs("File Error on read.\n", stderr);
		exit(-1);
	}
		
	//using fseek, found on (stackoverflow.com/questions/238603/how-can-i-get-a-files-size-in-c)
	fseek(fp, 0, SEEK_END);
	//sets fileSize to what ftell says the file pointer's file size is
	fileSize = ftell(fp);
	//rewind to the beginning of the file
	rewind(fp);	
	//print out the file and the size of the file
	printf("File: %s has %zu bytes.\n", filename, fileSize);
	//malloc enough space for that of a char aka 1 byte times the fileSize
	*buffer = malloc(sizeof(char) * fileSize);
	//if the malloc does not malloc correctly, give an error message to the user
	if(buffer == NULL){
		//put an error if there is a malloc error
		fputs("Memory allocation for the file size has failed!\n", stderr);
	}
	//read in the the contents of the file
	fread(*buffer, 1, fileSize, fp);
	//close the file
	fclose(fp);
	//return the size of the file
	return fileSize;
}

/**********************************************************************************
 * Read in a file but this time in write mode as we are going to write to this file
 * and then close the file.
 **********************************************************************************/
size_t write_file(char* filename, char* buffer, size_t size){
	//the size of the second file we will be returning after we write
	size_t fileSize2 = 0;
	//create a new file pointer for writing to the second file 
	FILE *fp2;
	//open the second filename in write mode
	fp2 = fopen(filename, "w");

	//if the file is null or missing, give an error to the user
	if(fp2 == NULL){
		//put an error if there is a file read error
		fputs("File Error on write.\n", stderr);
		exit(-1);
	}
	
	//cycle through the beginning of the file and since we need this info, write it normally to the file
	for(int i = 0; i < 44; i++){
		//fwrite allowing us to give it a buffer and size of a char to write to the file
		fwrite(buffer + i, sizeof(char), 1, fp2);
	}

	//cycle through the size of the file and for the actual data in the file, write it backwards
	for(int i = size; i >= 45; i--){
		//fwrite allows us to give it a buffer and size of a character to be able to write onto a file
		fwrite(buffer + i, sizeof(char), 1, fp2);
	}

	//using fseek, as shown above
	fseek(fp2, 0, SEEK_END);
	//sets fileSize2 to what ftell says the file pointer's file size is
	fileSize2 = ftell(fp2);
	//rewind to the beginning of the file
	rewind(fp2);
	//print out the file and the size of the file
	printf("File: %s has %zu bytes.\n\n", filename, fileSize2);
	//close the file
	fclose(fp2);
	//return the size of the file as it returns a size_t 
	return fileSize2;
}
