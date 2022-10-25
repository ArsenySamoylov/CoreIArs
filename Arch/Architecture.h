#ifndef CORE_I_ARS_ARCHITECTURE
#define CORE_I_ARS_ARCHITECTURE


enum  ASM_AND_CPU_ARGUMENTS : cmd_code
    { 
    MEMORY_ARGUMENT = 0x1 << 7, 
    REG_ARGUMENT    = 0x1 << 6,
    IMM_ARGUMENT    = 0x1 << 5,
    };

enum CPU_COMANDS
    {
    #define CPU_CMD(name, num, arg, code) CMD_##name = num,
    #include "cmd.h"
    #undef CPU_CMD

    UNKNOWN_COMAND,
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
