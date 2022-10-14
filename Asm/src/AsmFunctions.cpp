#include "Asm.h"

//! @todo 3) switch
//!       4) listing

Asmprogram* OpenAssmprogram (const char* src_name)
    {
    const char* full_src_name = GetFullProgammName (src_name);
    
    //printf("SRC_NAME: %s\n", src_name);

    const char* src_buffer = get_src_file (full_src_name);

    if (!src_buffer)
        return NULL;
    
    //printf("%s\n", src_buffer);
    
    size_t number_of_lines = CountLines (src_buffer, '\n');
    const char** lines_array = SplitBufferIntoLines (src_buffer, number_of_lines);
    
    //  int i = 0;
    //  while(lines_array[i] != NULL)
    //      printf("line %d: %s", i, lines_array[i++]); 
    
    Asmprogram* temp = (Asmprogram*) calloc (1, sizeof(Asmprogram));
    *temp = {src_buffer, number_of_lines, lines_array, NULL, 0};

    //free(full_src_name);
    return temp;
    }

void CloseAssmprogram (Asmprogram* asm_program)
    {
    if (!asm_program)
        return;

    free((void*)(asm_program->src_program));
    free(asm_program->lines_array);
    free(asm_program->binary_code);

    return;
    }

int TranslateSrcprogrameToBinaryCode (Asmprogram* asm_program)
    {
    if (!asm_program)
        return EMPTY_ASM_PROGRAM_POINTER;
    // if (!asm_program->src_program)
    //     return ;
    // if (asm_program->number_of_lines ==)
    //     return;
    // if (!asm_program->lines_array)
    //     returnl

    const char** lines_array     = asm_program->lines_array;
    size_t       number_of_lines = asm_program->number_of_lines;

    // printf("%s: number of lines %d\n", __func__, number_of_lines);
    // printf("Last line: %s\n\n", lines_array[number_of_lines-1]);
    
    comands* comands_array = NULL;
    
    size_t MAX_NUMBER_OF_COMANDS = 2 * number_of_lines;
    size_t COMANDS_ARRAY_LIMIT   = MAX_NUMBER_OF_COMANDS - sizeof(argument) - sizeof(cpu_register) - sizeof(comands);
    
    comands_array = (comands*) calloc (MAX_NUMBER_OF_COMANDS, sizeof(comands));
    
    if (!comands_array)
           return DYNAMIC_MEMORY_ERORR;
    
    size_t current_line = 0;
    size_t pc           = 0;
    
    CloseComments(asm_program->src_program, ';');
    
    int hlt_flag = 0;

    while (current_line < number_of_lines && !hlt_flag)
        { 
        //printf("pc: %d, COMANDS_LIMIT: %d\n", pc, COMANDS_ARRAY_LIMIT);
        if (pc >= COMANDS_ARRAY_LIMIT)
            {
            COMANDS_ARRAY_LIMIT += MAX_NUMBER_OF_COMANDS;

            comands* temp = (comands*) realloc (comands_array, sizeof(comands) * COMANDS_ARRAY_LIMIT);
            if (!temp)
                return DYNAMIC_MEMORY_ERORR;
            
            comands_array = temp;
            }

        // printf("  cyka  MAX_number_of_cmd = %d\n",MAX_NUMBER_OF_COMANDS);
        //
        // printf("cyka2\n");

        char asm_comand[_MAX_COMAND_LENGTH_] = "";
        
        int n = 0;
        sscanf (lines_array[current_line], "%s%n", asm_comand, &n);  
        //printf("cyka3\n");
        switch (comands cmd = CompareLineWithComands (asm_comand))
        {
        case -1:
            {
            printf("%s: Null lines array pointer!\n", __func__);
            return NULL_LINES_ARRAY_PTR;
            }
        case CPU_PUSH:
            {
            const char* line = lines_array[current_line] + n;

            argument     arg = 0;
            cpu_register reg = 0;

            comands mask = GetArguments(line + 1, &arg, &reg); 

            // printf("Arg: %d, Reg: %d\n", arg, reg);
            // printf("mask: ");

            unsigned temp = mask;
            int s[8] = {0,0,0,0, 0,0,0,0};
            for(int i = 0; i < 8; i++)
                {
                s[i] = temp % 2;
                temp /= 2;
                //printf ("%d", s[i]);
                }

            for (int i =0; i<8;i++)
                printf("%d", s[7-i]);
            
            printf("\n");
            getchar();
            //
            if (!mask)
                {
                printf("Wrong argument (line %.10s) for comand PUSH, arg = %d, reg = %d \n", line - n, arg, reg);
                return WRONG_PUSH_ARGUMENT;
                }
            
            cmd |= mask;
            comands_array[pc++] = cmd;

            if (cmd & IMM_ARGUMENT)
                {
                *((int*)(comands_array + pc)) = arg;
                pc += sizeof(arg);
                }
            
            if (cmd & REG_ARGUMENT)
                {
                *((cpu_register*)(comands_array + pc)) = reg;
                pc += sizeof(reg);
                }
            break;
            }
        case CPU_POP:
            {
            const char* line = lines_array[current_line] + n;

            argument     arg = 0;
            cpu_register reg = 0;

            comands mask = GetArguments(line, &arg, &reg);

            if (!mask)
                {
                printf("Wrong argument (line %.10s) for comand POP, arg = %d, reg = %d \n", line - n, arg, reg);
                return WRING_POP_ARGUMENT;
                }
            if (! (mask & MEMORY_ARGUMENT))
                {
                printf("Ebat, for pop argument have to be in [brakes] \n");
                return WRING_POP_ARGUMENT;
                }

            cmd |= mask;
            comands_array[pc++] = cmd;

            if (cmd & IMM_ARGUMENT)
                {
                *((int*)(comands_array + pc)) = arg;
                pc += sizeof(arg);
                }
            
            if (cmd & REG_ARGUMENT)
                {
                *((cpu_register*)(comands_array + pc)) = reg;
                pc += sizeof(reg);
                }
            break;
            }
        case CPU_HLT:
            {
            printf("This is hlt, I won't check anything below!\n");
            comands_array[pc] = cmd;
            pc++;
            
            hlt_flag = 1;
            break;
            }

        case CPU_ADD: 
        case CPU_SUB:
        case CPU_MUL:
        case CPU_DIV: 
        case CPU_OUT:
        case CPU_IN :
            {
            // const char* line = lines_array[current_line];
            // printf("LINE: %.10s\n", line);

            comands_array[pc] = cmd;
            ++pc;

            break;
            }   

        case CPU_UNKNOWN_COMAND:
        default:
            {
            printf("Unknow comand: %.4s\n", lines_array[current_line]);

            return ASM_TRNSLTR_UNKNOWN_COMAND;
            }
        }

        current_line++;
        }

    // printf("Number of CPU comands: %d\n", pc);

    comands* temp = (comands*) realloc (comands_array, pc * sizeof(comands));
    if (!temp)
        return DYNAMIC_MEMORY_ERORR;

    asm_program->binary_code           = temp;
    asm_program->number_of_CPU_comands = pc;

    return TRANSLATER_SUCCESS;
    }

int MakeExeForCPU (Asmprogram* program, const char* exe_program_name)
    {
    if (!program)
        return -1;
    if (!exe_program_name)
        return -1;
    if (!program->binary_code)
        return -1;

    // check program data
    const char* full_exe_name = GetFullExecutingprogramName (exe_program_name);

    FILE* exe_program = fopen (full_exe_name, "wb");
    if (!exe_program)
        return -1;

    IntelIArsSignature signature = {SOFT_CPU_VERSION, program->number_of_CPU_comands};

    size_t flag_signature = fwrite (&signature, sizeof(signature), 1, exe_program);
    if (flag_signature != 1)
        return -1;

    size_t flag_commands = fwrite (program->binary_code, sizeof(comands), program->number_of_CPU_comands,exe_program);
    if (flag_commands != program->number_of_CPU_comands)
        return -1;

    return 0;
    }
  
comands GetArguments (const char* line, argument* arg, cpu_register* reg)
    {
    if (!line)   return 0;
    if (!arg)    return 0;
    if (!reg)    return 0;

    comands mask = 0;
    
    char first_char = 0;
    sscanf(line, "%c", &first_char);
    
    if (first_char == '[')
        {
        char* closing_braket = strchr(line, ']');

        if (!closing_braket)
            return NO_ARGUMENTS;
        
        *closing_braket = '\0';

        mask |= MEMORY_ARGUMENT;
        ++line;
        //printf("Line without brk: %s", line);
        }

    printf("Why??\n");
    char test[30] = " 36 ";
    int a;
    sscanf(test, "%d", &a);
    printf("Zaebesh: %d\n", a);

    if (sscanf(line, "%d", arg))
        {
        //
        printf("Ebat!, schital chislo: %d\n", *arg);
        //
        mask |=IMM_ARGUMENT;

        int n = 0;
        sscanf(line, "%*s%n", &n);
        //printf("n: %d\n", n);
        //getchar();
        line += n;
        
        char plus = 0;
    
        sscanf(line, " %c%n", &plus, &n);
        //printf("PLUS ISss: %c\n", (plus == ' ') ? '_':plus);

        if (plus != '+')
            {
            //printf("HEHEHEHHE\n\n");
            return mask;
            }

        line += n;

        // printf("n: %d\n", n);
        // printf("CHto dalshe: %.3s\n", line);
        }
    
    char reg_code[33] = "";
    // //
    // printf("Sscanf: %d\n", sscanf(line, "%s", reg_code));
    // //
    if (sscanf(line, "%s", reg_code))
        {
        *reg = IsReg(reg_code);

        if (!(*reg))
            {
            printf("Govno register\n");
            //
            printf("Reg_code: %s\n", reg_code);
            //
            return NO_ARGUMENTS;
            }

        mask |= REG_ARGUMENT; 
        
        // printf("Reg: %d\n", *reg);
        // printf("Mask: %d\n", mask);  
        }
    
    return mask;
    }

const char*  GetFullProgammName (const char* src_name)
    {
    size_t     full_name_length          = strlen(src_name) + strlen(_STD_COMMAND_FILE_PREFIX_) + 100;
    char*      direction_to_command_file = (char*) calloc (full_name_length, sizeof(char));

    snprintf (direction_to_command_file, full_name_length, "%s%s", _STD_COMMAND_FILE_PREFIX_, src_name);
    
    //printf("%s", direction_to_command_file);
    
    return direction_to_command_file;
    }

const char*  GetFullExecutingprogramName (const char* exe_name)
    {
    size_t     full_name_length          = strlen(exe_name) + strlen(_STD_EXECUTING_program_PREFIX_) + strlen(_STD_EXECUTING_program_SUFFIX_) + 100;
    char*      direction_to_exe_program = (char*) calloc (full_name_length, sizeof(char));

    snprintf (direction_to_exe_program, full_name_length, "%s%s%s", _STD_EXECUTING_program_PREFIX_, exe_name, _STD_EXECUTING_program_SUFFIX_);
    
    //printf("%s", direction_to_exe_program);
    
    return direction_to_exe_program;
    }
