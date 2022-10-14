#ifndef ASS_EMBLER
#define ASS_EMBLER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Config.h"
#include "Parsing.h"

#include "my_buffer.h"
#include "my_log.h"


const char _STD_COMMAND_FILE_PREFIX_     [] = "Asmprogram/";
const char _STD_EXECUTING_program_PREFIX_[] = "../ExeSrc/";
const char _STD_EXECUTING_program_SUFFIX_[] = ".ars";

const int _MAX_FILE_NAME_LENGTH_ = 20;

const int _MAX_COMAND_LENGTH_ = 20;

struct Asmprogram
    {
    const char*   src_program;
    size_t        number_of_lines;
    const char**  lines_array;

    comands*      binary_code;
    size_t        number_of_CPU_comands;
    };

enum ASM_TRANSLATER_ERORRS
    {
    EMPTY_ASM_PROGRAM_POINTER,
   
    DYNAMIC_MEMORY_ERORR,

    WRONG_PUSH_ARGUMENT,
    WRING_POP_ARGUMENT,
    NULL_LINES_ARRAY_PTR,

    ASM_TRNSLTR_UNKNOWN_COMAND,

    TRANSLATER_SUCCESS,
    };

Asmprogram* OpenAssmprogram   (const char* src_name); 
void        CloseAssmprogram  (Asmprogram* asm_program);

int TranslateSrcprogrameToBinaryCode (Asmprogram* asm_program);
int MakeExeForCPU                    (Asmprogram* program, const char* exe_ptogramm_name);

comands GetArguments (const char* line, argument* arg, cpu_register* reg);

const char*  GetFullProgammName           (const char* src_name);
const char*  GetFullExecutingprogramName  (const char* exe_name);
#endif