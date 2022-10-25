#ifndef MY_BUFFER_HACK_YOUR_ASS
#define MY_BUFFER_HACK_YOUR_ASS

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

//! @todo terminate_comments(const char* buffer, char terminator);

char*  GetSrcFile (const char *file_direction);

//! @note This functions changes all '\n' to '\0' while dividing buffer 
//! @note AND ALO CHANGES ';' TO '\0'
//! If you want to split buffer without changing '\n', then use SplitBufferIntoLines
const char** DivideBufferIntoLines (char* buffer, size_t number_of_lines);
const char** SplitBufferIntoLines (const char* buffer, size_t number_of_lines);

char*  SkipSpaces           (const char* s);

size_t CountLines           (const char* text,   char end_of_line);

void   RemoveComments       (char* buffer, char terminator);
void   RemoveComments       (char* buffer, unsigned size,  char terminator);

void ShowLine(const char* line);
void TotalShow(const char* line);


#endif