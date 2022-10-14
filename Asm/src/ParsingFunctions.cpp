#include "Parsing.h"


const char* PROCESSOR_COMANDS[] =
    {
    "hlt",

    "push",
    "pop",
    
    "add",
    "sub",
    "mul",
    "div",
    "out",
    "in",
    };
    
comands CompareLineWithComands (const char* asm_comand)
    {
    if (!asm_comand)
        return -1;

    if (!stricmp(asm_comand, PROCESSOR_COMANDS[CPU_HLT])) 
            return CPU_HLT;

    if (!stricmp(asm_comand, PROCESSOR_COMANDS[CPU_PUSH])) 
            return CPU_PUSH;
    
    if (!stricmp(asm_comand, PROCESSOR_COMANDS[CPU_ADD])) 
            return CPU_ADD;

    if (!stricmp(asm_comand, PROCESSOR_COMANDS[CPU_SUB])) 
           return CPU_SUB;
    
    if (!stricmp(asm_comand, PROCESSOR_COMANDS[CPU_MUL])) 
           return CPU_MUL;

    if (!stricmp(asm_comand, PROCESSOR_COMANDS[CPU_OUT])) 
           return CPU_OUT;
    
    if (!stricmp(asm_comand, PROCESSOR_COMANDS[CPU_IN])) 
           return CPU_IN;

    return CPU_UNKNOWN_COMAND;
    }

cpu_register IsReg (const char* line)
    {
    if (!line)
        return ERORR_REG;

    int result = tolower(*(line+1)) + 1 - 'a';

    return (result > 0 && result < 20) ? result : 0;
    }