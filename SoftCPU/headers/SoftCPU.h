#ifndef INTEL_WILL_SUCK_AFTER_I_FINISH_THIS_PROJECT
#define INTEL_WILL_SUCK_AFTER_I_FINISH_THIS_PROJECT (false)

#include <stdlib.h>

#include "Config.h"
#include "my_buffer.h"

#include "SuperStack.h"


const int CPU_STACK_INITIAL_CAPACITY = 10;
const int NUMBER_OF_REGISTERS = 5;

const int _RAM_SIZE_ = 2048;

const comands MASK = 224; // 1110 0000

enum EXECUTE_ERRORS
    {
    WRONG_PROGRAM_PTR,
    WRONG_ARGUMENT,

    UNKNOWN_COMAND,

    BIG_SUCCESS,
    };

struct ExeProgram
    {
    const comands* comands_array;
    SuperStack*    CPU_stk;

    size_t number_of_comands;
    size_t ip;

    cpu_register* reg_arr;

    bytes* RAM;
    };

ExeProgram* OpenExeProgram  (const char* exe_file);
void        CloseExeProgram (ExeProgram* program);

int ExecuteCPUCommands(ExeProgram* program);

size_t CheckSignature (FILE* CPU_comands);

#define VerificateExe(program) 
void DumpCPUandStack (ExeProgram* program, unsigned error_flaf = 0);

#endif