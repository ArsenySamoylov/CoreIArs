#ifndef INTEL_WILL_SUCK_AFTER_I_FINISH_THIS_PROJECT
#define INTEL_WILL_SUCK_AFTER_I_FINISH_THIS_PROJECT (false)

#include <stdlib.h>

#include "Config.h"
#include "Architecture.h"

#include "SuperStack.h"

#include "DebugCPU.h"
#include "CommonErrors.h"
#include "my_buffer.h"
#include "EasyDebug.h"

const int CPU_STACK_INITIAL_CAPACITY = 10;
const int NUMBER_OF_REGISTERS = 5;

const int _RAM_SIZE_ = 2048;
const int _REGISTER_ARRAY_SIZE_ = 5;
const cmd_code MASK = 224; // 1110 0000

enum EXECUTE_ERRORS
    {
    WRONG_PROGRAM_PTR,
    
    UNKNOWN_COMAND,

    BIG_SUCCESS,
    };

struct ArsCore
    {
    const cmd_code* comands_array;
    SuperStack      CPU_stk; // set element_t as data

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
void CloseExeProgram (ArsCore* core);

int  ExecuteCPUCommands(ArsCore* core);

size_t CheckSignature (FILE* CPU_comands);

void     DumpCPUandStack (ArsCore* core);
unsigned MedComissionCPU (ArsCore* soldat);
void     ShowHeap(element_t* heap, ssize_t top);
#endif