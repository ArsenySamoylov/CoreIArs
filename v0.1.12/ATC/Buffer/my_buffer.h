#ifndef MY_BUFFER_HACK_YOUR_ASS
#define MY_BUFFER_HACK_YOUR_ASS

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

//! @todo terminate_comments(const char* buffer, char terminator);

char*  GetSrcFile (const char *file_direction);

const char** SplitBufferIntoLines (const char* buffer, size_t number_of_lines);
size_t       CountLines           (const char* text,   char end_of_line);
void         RemoveComments       (char* buffer, char terminator);
char*        SkipSpaces           (const char* s);
#endif