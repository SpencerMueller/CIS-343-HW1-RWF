#include <stdio.h>

#ifndef FILE_H_FILE
#define FILE_H_FILE

/*****************************************************************************
 * read_file will take in a filename and pointer to a pointer buffer that will
 * read in the contents of the file and return the size of the file.
*****************************************************************************/
size_t read_file(char* filename, char** buffer);

/************************************************************************
 *write_file will take in a filename, buffer pointer, and a size and then
 write the contents of the buffer to the filename's file, then it will
 also report the size of the new written file.
 ***********************************************************************/
size_t write_file(char* filename, char* buffer, size_t size);

#endif
