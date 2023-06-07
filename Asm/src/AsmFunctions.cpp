#include "Asm.h"
#include "show_binary.h"
       
int MakeCmdCode (Asmprogram* asm_program)
    {
    VERIFICATE_ASM_PROGRAM(return FAILURE, asm_program);

    int compilation_status = FirstCompilation(asm_program);
    if (compilation_status != SUCCESS)
        COMPILE_ERROR(first);
    
    compilation_status = SecondCompilation(asm_program);
    if (compilation_status != SUCCESS)
        COMPILE_ERROR(second);

    // printf("ebar %zu\n", asm_program->number_of_CPU_comands);
  
    return SUCCESS;
    }

int FirstCompilation (Asmprogram* asm_program)
    {
    VERIFICATE_ASM_PROGRAM(return FAILURE, asm_program);

    const char** lines_array     = asm_program->lines_array;
    size_t       number_of_lines = asm_program->number_of_lines;
    
    // size_t current_line = 0;
    size_t pc           = 0;

    size_t i = 0;
    while (i < number_of_lines)
        { 
        char* current_line = SkipSpaces(lines_array[i]);

        char* comment =  strchr(current_line, ';');  
        if (comment)
            *comment = '\0';
            
        if (*current_line == ':')
            {
            if (AddLabel(asm_program, current_line, pc) == FAILURE)
                {
                func_message("Ebat, MAKE BETTER LABELS!!!\n");
                return FAILURE;
                }
    
            i++;
            continue;
            }
        
        if (*current_line == '\0' || *current_line == '\n')
            {
            //printf("\t\tEMPTY LINE %d", i + 1);
            i++;
            continue;
            }

        char asm_comand[_MAX_COMAND_LENGTH_] = {0};
        
        int n = 0;
        sscanf (current_line, "%s%n", asm_comand, &n);  
        //printf("pc %zu, after \n", pc);
        switch (cmd_code cmd = CompareLineWithComands (asm_comand))
            {
            #define CPU_CMD(name, num, arg, code)    \
                case num:                            \
                        pc++;                        \
                                                     \
                        if (arg)                     \
                            COUNT_PC_FOR_LABELS(pc); \
                                                     \
                        break;              

            #include "cmd.h"
            #undef CPU_CMD
        
            case UNKNOWN_COMAND:
            default:
                {
                //printf("Unknow comand: %s\n, at line %zu\n", current_line, i + 1);
                printf("Debug, unknown cmd (line %d): \n", i+1);
                ShowLine(current_line);
                return UNKNOWN_COMAND;
                }
        
            }
        i++;
        }
    asm_program->number_of_compiliation += 1;
    
    // ShowLabelsTable(asm_program);
    // getchar();
    // printf("END OF FIRST COMP\n");
    return SUCCESS;
    }


int SecondCompilation (Asmprogram* asm_program)
    {
    VERIFICATE_ASM_PROGRAM(return FAILURE, asm_program);
    
    const char** lines_array     = asm_program->lines_array;
    size_t       number_of_lines = asm_program->number_of_lines;
    
    // size_t current_line = 0;
    size_t pc           = 0;
    
    size_t code_arr_current_limit = number_of_lines * 2 - sizeof(imm_arg) - sizeof(reg_arg) - sizeof(cmd_code);
    
    cmd_code* code_array = (cmd_code*) calloc (number_of_lines * 2, sizeof(code_array[0]));
    CHECK_PTR_STD_RET(code_array, BAD_CALLOC);
    
    fprintf(Listing, " pc |    cmd     arg   | code\n");
    fprintf(Listing, "    -          -     \n");
    size_t i = 0;
    while (i < number_of_lines)
        { 
        const char* current_line = SkipSpaces(lines_array[i]);
        
        if (*current_line == ':' || *current_line == '\0')
            {
            i++;
            continue;
            }
        
        char asm_comand[_MAX_COMAND_LENGTH_] = {0};
        
        int n = 0;
        sscanf (current_line, "%s%n", asm_comand, &n);  

        
        switch (cmd_code cmd = CompareLineWithComands (asm_comand))
        {
        #define CPU_CMD(name, num, arg, code)                  \
            case num:                                          \
                if (!arg)                                      \
                    {                                          \
                    code_array[pc++] = cmd;                    \
                    fprintf(Listing, "%3zX | %02X               | %s", pc, cmd, SkipSpaces(lines_array[i]));\
                    }                                          \
                if (arg)                                       \
                    {                                          \
                    fprintf(Listing, "%3zX | ", pc);            \
                    SET_ARGUMENTS(code_array, pc);             \
                    fprintf(Listing, " | %s", SkipSpaces(lines_array[i]));   \
                    }                               \
                break;                        
        
        #include "cmd.h"
        #undef CPU_CMD

        case UNKNOWN_COMAND:
        default:
            {
            printf("Unknow comand: %s\n, at line %zu\n", current_line, i + 1);

            return UNKNOWN_COMAND;
            }
        
        }
        if (pc >= code_arr_current_limit)
        {
        code_arr_current_limit += number_of_lines * 2;

        cmd_code* temp = (cmd_code*) realloc (code_array, sizeof(cmd_code) * code_arr_current_limit);
        CHECK_PTR_STD_RET(temp, BAD_REALLOC);
        
        code_array = temp;
        }

        i++;
        fprintf(Listing, "\n");
        }

    cmd_code* temp = (cmd_code*)  realloc (code_array, pc * sizeof(cmd_code)); 
    CHECK_PTR_STD_RET(temp, BAD_REALLOC);

    asm_program->binary_code             = temp;
    asm_program->number_of_CPU_comands   = pc;
    asm_program->number_of_compiliation += 1;

    return SUCCESS;
    }

int MakeExeForCPU (Asmprogram* program, const char* exe_program_name)
    {
    VERIFICATE_ASM_PROGRAM(return FAILURE, program);
    CHECK_PTR_RET(exe_program_name, return FAILURE);

    const char* full_exe_name = GetFullExecutingprogramName (exe_program_name); 
    CHECK_PTR_RET(full_exe_name, FAILURE);

    FILE* exe_program = fopen (full_exe_name, "wb");
    CHECK_PTR_STD_RET(exe_program, ERROR_OPENING_FILE);
   
    IntelIArsSignature signature = {SOFT_CPU_VERSION, program->number_of_CPU_comands};

    size_t flag_signature = fwrite (&signature, sizeof(signature), 1, exe_program);
    if (flag_signature != 1)
        return FAILURE;

    size_t flag_commands = fwrite (program->binary_code, sizeof(cmd_code), program->number_of_CPU_comands,exe_program);
    if (flag_commands != program->number_of_CPU_comands)
        return FAILURE;

    return SUCCESS;
    }
