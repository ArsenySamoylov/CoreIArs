#include "Asm.h"

#include <string.h>

size_t SetArguments (Asmprogram* asm_program, cmd_code* code_array, cmd_code cmd, const char* line) 
    {
    CHECK_PTRS_RET(return 0, line, code_array);
    VERIFICATE_ASM_PROGRAM(return 0, asm_program);

    size_t pc = 0; 

    imm_arg     imm = 0;      
    reg_arg     reg = 0;      
                              
    cmd_code mask = GetArguments(SkipSpaces(line), &imm, &reg, asm_program);   
                                
    if (!mask)                
        {                     
        func_message("Wrong argument (line %.10s) for comand,"          
                "imm = %d, reg = %d \n", line, imm, reg);      
        return 0;
        }                     
                              
    cmd |= mask;              
    code_array[pc++] = cmd;
    unsigned char MASK = 240;
    fprintf(Listing, "%02X (%02X:%02X)  ", cmd, cmd & MASK, cmd & (~MASK)); //  0 | 32 (20:12) 0006 | call :MAIN 

    if (cmd & IMM_ARGUMENT)   
        {                     
        *((imm_arg*)(code_array + pc)) = imm;
        pc += sizeof(imm); 

        fprintf(Listing, "%04X - imm", imm);   
        }                     
                              
    if (cmd & REG_ARGUMENT)   
        {                     
        *((reg_arg*)(code_array + pc)) = reg;
        pc += sizeof(reg);  

        fprintf(Listing, "  %02X - reg", reg);  
        } 

    return pc;                    
    }

cmd_code GetArguments ( char* line, imm_arg* imm, reg_arg* reg, Asmprogram* asm_program)
    {
    CHECK_PTRS_RET(return 0, line, imm, reg);
    VERIFICATE_ASM_PROGRAM(return 0, asm_program);

    cmd_code mask = 0;
    
    char first_char = *line;
    if (first_char == '[')
        {
        char* closing_braket = strchr(line, ']');

        if (!closing_braket)
            {
            printf ("Syntax error: missing closing braket\n");
            return SYNTAX_ERROR;
            }

        // *closing_braket = ' ';

        mask |= MEMORY_ARGUMENT;
        ++line;
        }
    
    if (first_char == ':')
        {
        imm_arg temp = GetLabel (SkipSpaces(line + 1), asm_program);
        if (temp != NOT_A_LABEL)
            {
            *imm = (imm_arg) (temp);
            mask |= IMM_ARGUMENT;

            return mask;
            } 

        if (asm_program->number_of_compiliation > 0) 
            {
            printf("%s - is wrong label\n", line + 1);
            return 0;
            }
        
        *imm = BAD_LABEL;
        mask |= IMM_ARGUMENT;

        return mask; 
        }

    if (first_char == '\'')
        {
        ++line;
        sscanf(line, "%c", imm);
        mask |= IMM_ARGUMENT;

        return mask;
        }

    int n = 0;
    if (sscanf(line, "%d%n", imm, &n))
        {    
        mask |= IMM_ARGUMENT;

        line += n;

        const char plus = *(line + strspn(line, " \t"));

        // printf("plus: %c, line: %.10s\n", plus, line);

        if (plus == '\0' || plus == '\n')
            return mask;

        if (plus == ']' && mask & MEMORY_ARGUMENT)
            {
            line += strspn(line, " \t") + 1;
            goto CHECK_AFTER_COMMAND;
            }

        if (plus != '+')
            {
            printf("Not a plus char ('%c')\n", plus);
            return SYNTAX_ERROR;
            }

        line = SkipSpaces (line);
        line += 1; // skip '+' 
        }
    
    {
    char reg_code[33] = "";
    n = 0;
    if (sscanf(line, "%s%n", reg_code, &n))
        {
        *reg = IsReg(reg_code);

        if (!(*reg))
            {
            printf("System: SHITREG: Govno register\n");
            return NO_ARGUMENTS;
            }

        mask |= REG_ARGUMENT; 
        }
    }
    
    // update from december 20, 2022, 5:08 am
    line += n;

    if (mask & MEMORY_ARGUMENT)
        {
        line += strspn(line, " ");
        
        if (*line != ']')
            {
            printf("missing ']' (*line: %c)\n", *line);
            return SYNTAX_ERROR;
            }
        
        line++;
        }

    CHECK_AFTER_COMMAND:
    line += strspn(line, "  \t");

    if (*line != '\0' && *line != ';' && *line != '\n')
        {
        printf("EBAT SOMETHIG AFTER COMMAND: '%s'\n", line);
        return SYNTAX_ERROR;
        }

    return mask;
    }
