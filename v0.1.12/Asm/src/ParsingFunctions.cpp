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

    "jmp",
    };

int stricmp (const char *s1, const char *s2 )
    {
    int i = 0;
    for( ; s1[i] && s2[i]; i++)
        if ((tolower(s1[i]) != tolower(s2[i])))
            return s1[i] - s2[i];   

    return (s1[i] - s2[i]);
    }

cmd_code CompareLineWithComands (const char* asm_comand)
    {
    if (!asm_comand)
        return -1;

    if (!stricmp(asm_comand, PROCESSOR_COMANDS[CPU_HLT])) 
            return CPU_HLT;

    if (!stricmp(asm_comand, PROCESSOR_COMANDS[CPU_PUSH])) 
            return CPU_PUSH;
    
    if (!stricmp(asm_comand, PROCESSOR_COMANDS[CPU_POP])) 
            return CPU_POP;
    
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

    if (!stricmp(asm_comand, PROCESSOR_COMANDS[CPU_JMP])) 
            return CPU_JMP;

    return CPU_UNKNOWN_COMAND;
    }

reg_arg IsReg (const char* line)
    {
    if (!line)
        return ERORR_REG;

    int result = tolower(*(line + 1)) + 1 - 'a';

    return (reg_arg) ((result > 0 && result < 20) ? result : 0);
    }