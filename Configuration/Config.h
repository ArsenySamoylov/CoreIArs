#ifndef ZARPLATA
#define ZARPLATA 

#include <stddef.h>

typedef unsigned char  comands;
typedef int            argument;
typedef unsigned char  cpu_register;
typedef unsigned char  bytes;

const int SOFT_CPU_VERSION = 2;

enum  ASM_AND_CPU_ARGUMENTS : comands
    {
    NO_ARGUMENTS    = 0,
       
    MEMORY_ARGUMENT = 0x1 << 7, 
    REG_ARGUMENT    = 0x1 << 6,
    IMM_ARGUMENT    = 0x1 << 5,
    };

enum CPU_COMANDS
    {
    CPU_HLT,

    CPU_PUSH,
    CPU_POP,

    CPU_ADD,
    CPU_SUB,
    CPU_MUL,
    CPU_DIV,

    CPU_OUT,
    CPU_IN,

    CPU_UNKNOWN_COMAND
    };

enum RegisterName : cpu_register
    {
    ERORR_REG,
    rax,
    rbx,
    rcx,
    rdx,
    };

struct IntelIArsSignature
    {
    int version;
    size_t number_of_comands;
    };

#endif