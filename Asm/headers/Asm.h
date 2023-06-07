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


const char _STD_COMMAND_FILE_PREFIX_     [] = "";
const char _STD_EXECUTING_program_PREFIX_[] = "";
const char _STD_EXECUTING_program_SUFFIX_[] = ".ars";

const int _MAX_FILE_NAME_LENGTH_ = 200;

const int _MAX_COMAND_LENGTH_ = 200;

const int _MAX_NUMBER_OF_LABELS_  = 270;
const int _MAX_LABEL_NAME_LENGTH_ = 200;

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

Asmprogram* OpenAssmprogram   (const char* src_name); 
void        CloseAssmprogram  (Asmprogram* asm_program);

int MakeCmdCode    (Asmprogram* asm_program);
int MakeExeForCPU  (Asmprogram* program, const char* exe_ptogramm_name);

int FirstCompilation  (Asmprogram* asm_program);
int SecondCompilation (Asmprogram* asm_program);

size_t   SetArguments (Asmprogram* asm_program, cmd_code* code_array, cmd_code cmd, const char* line); 
cmd_code GetArguments (char* line, imm_arg* arg, reg_arg* reg, Asmprogram* asm_program);

size_t CountPC (Asmprogram* asm_program, const char* line);

const char*  GetFullProgammName           (const char* src_name);
const char*  GetFullExecutingprogramName  (const char* exe_name);

int     AddLabel        (Asmprogram* asm_program, const char* current_line, size_t pc);
imm_arg GetLabel         (const char* line, Asmprogram* asm_program);
void    ShowLabelsTable (Asmprogram* asm_program);

#define VERIFICATE_ASM_PROGRAM(return_expression, asm_program)  {                                                                \
                                                                CHECK_PTRS_RET(return_expression, asm_program,                   \
                                                                                                (asm_program)->src_program,      \
                                                                                                (asm_program)->labels_arr,       \
                                                                                                (asm_program)->lines_array    ); \
                                                                }


#define COMPILE_ERROR(number_of_compilation)                    \
                                            do {                \
                                            func_message("Error in " #number_of_compilation " compilation\n"); \
                                            return FAILURE;     \
                                            } while(0)           

#define COUNT_PC_FOR_LABELS(pc)                                         \
            {                                                           \
            const char* line = current_line + n;                        \
                                                                        \
            size_t temp = CountPC(asm_program, line);                   \
            if (!temp)                                                  \
                {                                                       \
                func_message("Ebat, something went wrong with arguments in line(%d): %s\n", i + 1, current_line); \
                return WRONG_ARGUMENT;                                  \
                }                                                       \
                                                                        \
            pc += temp;                                                 \
            }

#define SET_ARGUMENTS(code_array, pc)                                   \
            {                                                           \
            const char* line = current_line + n;                        \
                                                                        \
            size_t temp = SetArguments(asm_program, code_array + pc, cmd, line); \
            if (!temp)                                                  \
                {                                                       \
                func_message("Ebat, something went wrong with arguments in line(%d): %s\n", i + 1, current_line); \
                return WRONG_ARGUMENT;                                  \
                }                                                       \
                                                                        \
            pc += temp;                                                 \
            }                         

extern FILE* Listing;   
                                                             
#define NOT_A_LABEL (-1)
#define BAD_LABEL   (-666)
#endif