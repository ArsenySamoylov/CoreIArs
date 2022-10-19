#ifndef ASS_EMBLER
#define ASS_EMBLER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Config.h"
#include "Architecture.h"

#include "Parsing.h"
   
#include "CommonErrors.h"
#include "my_buffer.h"
#include "my_log.h"
#include "EasyDebug.h"


const char _STD_COMMAND_FILE_PREFIX_     [] = "Examples/";
const char _STD_EXECUTING_program_PREFIX_[] = "Examples/";
const char _STD_EXECUTING_program_SUFFIX_[] = ".ars";

const int _MAX_FILE_NAME_LENGTH_ = 20;

const int _MAX_COMAND_LENGTH_ = 20;

const int _MAX_NUMBER_OF_LABELS_  = 27;
const int _MAX_LABEL_NAME_LENGTH_ = 20;

struct label
    {
    const char* name;
    size_t      cmd_address;
    };

struct Asmprogram
    {
    char*         src_program;
    size_t        number_of_lines;
    const char**  lines_array;

    label* labels_arr;
    int current_number_of_labels;

    cmd_code*     binary_code;
    size_t        number_of_CPU_comands;

    unsigned number_of_compiliation;    
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

int MakeCmdCode    (Asmprogram* asm_program);
int MakeExeForCPU  (Asmprogram* program, const char* exe_ptogramm_name);

int FirstCompilation (Asmprogram* asm_program);
int SecondCompilation (Asmprogram* asm_program);
    
cmd_code GetArguments (const char* line, imm_arg* arg, reg_arg* reg);

const char*  GetFullProgammName           (const char* src_name);
const char*  GetFullExecutingprogramName  (const char* exe_name);

void ShowLabelsTable(Asmprogram* asm_program);
#define VERIFICATE_ASM_PROGRAM(return_expression, asm_program)  {                                                                \
                                                                CHECK_PTRS_RET(return_expression, asm_program,                   \
                                                                                                (asm_program)->src_program,      \
                                                                                                (asm_program)->labels_arr,       \
                                                                                                (asm_program)->lines_array    ); \
                                                                }

#endif