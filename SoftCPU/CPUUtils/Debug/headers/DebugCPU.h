#ifndef DEBUG_CPU
#define DEBUG_CPU

#include "SoftCPU.h"

enum EXE_VERIFICATOR_ERRORS
    {
    NULL_EXE_PTR        = 0x1 << 0,
    NULL_COMANDS_ARRAY  = 0x1 << 1,
    NULL_STK_PTR        = 0x1 << 2,
    NULL_RAM_PTR        = 0x1 << 3,
    NULL_REG_ARRAY      = 0x1 << 4,
    };

unsigned MedComissionCPU (ExeProgram* soldat);

#endif