#include "my_buffer.h"

const char* get_src_file (const char *file_direction)
    {
    if (!file_direction) return NULL;
    
    //printf("File direction: %s\n", file_direction);

    FILE *txt = fopen(file_direction, "r");
    if (!txt)
        return NULL;
    
    struct stat txt_data;
    stat(file_direction, &txt_data);

    if (txt_data.st_size < 1)
        {
        fclose(txt);
        return NULL;
        }

    char* txt_buffer = (char*) calloc (txt_data.st_size + 1, sizeof (char));

    size_t number_of_ch = fread (txt_buffer, sizeof(char), txt_data.st_size, txt);

    txt_buffer = (char*)realloc(txt_buffer, number_of_ch + 1);
    txt_buffer[number_of_ch] = '\0';

    fclose(txt);

    return txt_buffer;
    }

const char** SplitBufferIntoLines (const char* buffer, size_t number_of_lines)
    {
    if (!buffer)          return NULL;
    if (!number_of_lines) return NULL;

    const char** lines_array = (const char**) calloc (number_of_lines + 1, sizeof(lines_array[0]));
    if (lines_array == NULL) return NULL;

    size_t current_line = 0;
    int number_of_characters_in_line = 0;
    size_t i = 0;

    while (buffer[i] != '\0')
        {
        if (buffer[i] == '\n')
            {
            lines_array[current_line] = (buffer + i - number_of_characters_in_line);

            number_of_characters_in_line = 0;
            current_line++;
            }

        else if (buffer[i+1] == '\0')
            {
            lines_array[current_line] = (buffer + i - number_of_characters_in_line);

            current_line++;
            number_of_characters_in_line = 0;
            }

        else
            number_of_characters_in_line++;

        i++;
        }

    lines_array[number_of_lines] = NULL;

    // //
    // printf("%s: number of lines %d\n", __func__, number_of_lines);
    // printf("Last line: %s\n\n", lines_array[number_of_lines-1]);
    // getchar();
    // //

    return lines_array;
    }

size_t CountLines(const char* text, char end_of_line)
    {
    if (!text)
        return 0;

    size_t number_of_lines = 0;
    size_t i = 0;

    while (text[i] != '\0')
        {
        if (text[i] == end_of_line || text[i+1] == '\0' )
            number_of_lines++;

        i++;
        }

    return number_of_lines;
    }

void CloseComments (const char* buffer, char terminator)
    {
    if (!buffer)
        return;
    
    int i = 0;

    while( (*(buffer + i)) != '\0')
        {
        if (*(buffer + i) == terminator)
            *(buffer + i) == '\0';
            
        ++i;    
        }
    
    return;
    }

