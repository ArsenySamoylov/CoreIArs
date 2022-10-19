#ifndef CORE_I_ARS_ARCHITECTURE
#define CORE_I_ARS_ARCHITECTURE

#include "Config.h"

enum  ASM_AND_CPU_ARGUMENTS : cmd_code
    { 
    MEMORY_ARGUMENT = 0x1 << 7, 
    REG_ARGUMENT    = 0x1 << 6,
    IMM_ARGUMENT    = 0x1 << 5,
    };

enum CPU_COMANDS
    {
    CPU_HLT = 0,

    CPU_PUSH,
    CPU_POP,

    CPU_ADD,
    CPU_SUB,
    CPU_MUL,
    CPU_DIV,

    CPU_OUT,
    CPU_IN,

    CPU_JMP,

    CPU_UNKNOWN_COMAND
    };
    
enum RegisterName : reg_arg
    {
    ERORR_REG,
    rax,
    rbx,
    rcx,
    rdx,
    };

#endif