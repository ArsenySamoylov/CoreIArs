#ifndef INTEL_WILL_SUCK_AFTER_I_FINISH_THIS_PROJECT
#define INTEL_WILL_SUCK_AFTER_I_FINISH_THIS_PROJECT (false)

#include <stdlib.h>
#include <math.h>

#include "Config.h"
#include "Architecture.h"

#include "SuperStack.h"

#include "DebugCPU.h"
#include "CommonErrors.h"
#include "my_buffer.h"
#include "EasyDebug.h"

const int CPU_STACK_INITIAL_CAPACITY = 10;
const int CALL_STACK_INITIAL_CAPACITY = 20;

const int _ACCURACY_          = 100;
const int NUMBER_OF_REGISTERS = 5;

const int _RAM_SIZE_ = 2048;
const int _REGISTER_ARRAY_SIZE_ = 5;
const cmd_code MASK = 224; // 1110 0000

struct ArsCore
    {
    const cmd_code* comands_array;
    SuperStack      CPU_stk; 
    SuperStack      Call_stk;

    size_t number_of_comands;
    size_t ip;

    data  REG_ARR[_REGISTER_ARRAY_SIZE_] = {0};
    data* RAM;
    };

enum CTOR_ARS_CORE_ERROR
    {
    NULL_CORE_PTR,
    NULL_ARS_FILE_PTR,
    WRONG_SIGNATURE,
    NUMBER_OF_COMANDS_DOESNT_MATCH,
    NULL_REG_ARR,
    };

int  CtorArsCore (ArsCore* core, const char* ars_file);
int  DtorArsCore (ArsCore* core);

int  ExecuteCPUCommands (ArsCore* core);

size_t CheckSignature (FILE* CPU_comands);
void    SetAccuracy   (ArsCore* core);

void     DumpCPUandStack (ArsCore* core);
unsigned MedComissionCPU (ArsCore* soldat);
void     ShowHeap   (element_t* heap, ssize_t top);
void     ShowRegArr (data* reg_arg);

size_t SetComandsArrayAndCheckSignature(cmd_code** cmd_arr, const char* ars_file);

#define SOZDAY(core, program)                       \
    {                                               \
    int flag_error = CtorArsCore (&core, program);  \
    if (flag_error  != SUCCESS)                     \
        {                                           \
        func_message("Can't create ArsCorp, (error %d)\n", flag_error); \
        return MAIN_ERROR;                                              \
        }                                           \
    }

#define EBANI_PROGRAMKU(core)                       \
    {                                               \
    int status = ExecuteCPUCommands(&core);         \
    if (status != SUCCESS)                          \
        {                                           \
        func_message("Ebat, something went wromg :/ (error %d)\n", status);  \
        return MAIN_ERROR;                          \
        }                                           \
    }

#define YBEI_DURU(core)                             \
    {                                               \
    int status = DtorArsCore(&core);                \
    if (status != DEAD)                             \
        {                                           \
        func_message("Ebat, You can't even kill f*cking Core (error %d)\n", status); \
        return MAIN_ERROR;                          \
        }                                           \
    }
#endif