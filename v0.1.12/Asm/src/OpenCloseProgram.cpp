#include "Asm.h"

#pragma GCC diagnostic ignored "-Wcast-qual"

Asmprogram* OpenAssmprogram (const char* src_name)
    {
    const char* full_src_name = GetFullProgammName (src_name);
    CHECK_PTR_RET(full_src_name, return NULL);

    char* src_buffer = (char*) GetSrcFile (full_src_name);
    CHECK_PTR_RET(src_buffer, return NULL);
    
    
    size_t number_of_lines = CountLines (src_buffer, '\n');
    const char** lines_array = SplitBufferIntoLines (src_buffer, number_of_lines);

    label* labels_arr = (label*) calloc(_MAX_NUMBER_OF_LABELS_, sizeof(labels_arr[0]));
    CHECK_PTR_RET(labels_arr, return NULL);
    
    Asmprogram* temp = (Asmprogram*) calloc (1, sizeof(Asmprogram));
    CHECK_PTR_RET(temp, return NULL);

    temp->src_program              = src_buffer;
    temp->number_of_lines          = number_of_lines;
    temp->lines_array              = lines_array;
    temp->current_number_of_labels = 0;
    temp->labels_arr               = labels_arr;
    temp->binary_code              = NULL;
    temp->number_of_CPU_comands    = 0;
    temp->number_of_compiliation   = 0;

    return temp;
    }

void CloseAssmprogram (Asmprogram* asm_program)
    {
    if (!asm_program)
        return;

    free(asm_program->src_program);
    free(asm_program->lines_array);
    free(asm_program->binary_code);
    free(asm_program->labels_arr);

    return;
    }