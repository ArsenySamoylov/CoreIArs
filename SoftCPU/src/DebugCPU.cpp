#include "SoftCPU.h"
#include "EasyDebug.h"

unsigned MedComissionCPU (ArsCore* soldat)
    {
    unsigned flag_error = 0;

    if (soldat == NULL)
        return NULL_EXE_PTR;
    
    if (!soldat->comands_array)
         flag_error |= NULL_COMANDS_ARRAY;

    if (!&(soldat->CPU_stk))
        flag_error |= NULL_STK_PTR;

    if (!soldat->RAM)
        flag_error |= NULL_RAM_PTR;
    
    if (!soldat->REG_ARR)
         flag_error |= NULL_REG_ARRAY;
    
    return flag_error;
    }

