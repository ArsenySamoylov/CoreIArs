#include "Parsing.h"


int stricmp (const char *s1, const char *s2 )
    {
    int i = 0;

    for( ; s1[i] && s2[i] ; i++)
        if ((tolower(s1[i]) != tolower(s2[i])))
            return s1[i] - s2[i];   
        
    return (s1[i] - s2[i]);
    }

int skip_spaces_cmp (const char *s1, const char *s2 )
    {
    int i = 0;

    for( ; s1[i] && s2[i] ; i++)
        {
        if (s1[i] == ' ' && s2[i] == ' ')
            return 0;

        if ((tolower(s1[i]) != tolower(s2[i])))
            return s1[i] - s2[i];   
        }
    return (s1[i] - s2[i]);
    }
cmd_code CompareLineWithComands (const char* asm_comand)
    {
    if (!asm_comand)
        return -1;
    #define CPU_CMD(name, num, arg, code)                   \
         if (!stricmp(asm_comand, #name))                   \
            return num;                                     \

    #include "cmd.h"
    #undef CPU_CMD

    return UNKNOWN_COMAND;
    }

reg_arg IsReg (const char* line)
    {
    if (!line)
        return ERORR_REG;
    if (*line != 'r' || *(line+2) != 'x')
        return ERORR_REG;
        
    int result = tolower(*(line + 1)) + 1 - 'a';

    return (reg_arg) ((result > 0 && result < 20) ? result : 0);
    }