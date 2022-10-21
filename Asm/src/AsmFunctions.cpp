#include "Asm.h"
#include "show_binary.h"

imm_arg IsLabel (const char* line, Asmprogram* asm_program);

#define COMPILE_ERROR(number_of_compilation)                    \
                                            do {                   \
                                            func_message("Error in" #number_of_compilation "compilation"); \
                                            return FAILURE;     \
                                            } while(0)                  
int MakeCmdCode (Asmprogram* asm_program)
    {
    VERIFICATE_ASM_PROGRAM(return FAILURE, asm_program);

    int compilation_status = FirstCompilation(asm_program);
    if (compilation_status != SUCCESS)
        COMPILE_ERROR(first);

    compilation_status = SecondCompilation(asm_program);
    if (compilation_status != SUCCESS)
        COMPILE_ERROR(second);

    printf("ebar %zu\n", asm_program->number_of_CPU_comands);
  
    return TRANSLATER_SUCCESS;
    }

int FirstCompilation (Asmprogram* asm_program)
    {
    VERIFICATE_ASM_PROGRAM(return FAILURE, asm_program);

    const char** lines_array     = asm_program->lines_array;
    size_t       number_of_lines = asm_program->number_of_lines;
    
    size_t current_line = 0;
    size_t pc           = 0;
    
    RemoveComments(asm_program->src_program, ';'); 
    RemoveComments(asm_program->src_program, '\n');

    size_t i = 0;
    while (i < number_of_lines)
        { 
        const char* current_line = SkipSpaces(lines_array[i]);

        if (*current_line == ':')
            {
            label* new_label = (asm_program ->labels_arr) + (asm_program->current_number_of_labels);
            ++(asm_program->current_number_of_labels);
            
            new_label->name = SkipSpaces(current_line + 1);
            new_label->cmd_address = pc;

            ++i;
            continue;
            }

        char asm_comand[_MAX_COMAND_LENGTH_] = {0};
        
        int n = 0;
        sscanf (current_line, "%s%n", asm_comand, &n);  
        printf("pc %zu, after \n", pc);
        switch (cmd_code cmd = CompareLineWithComands (asm_comand))
            {
            #define CPU_CMD(name, num, arg, code) \
                case num :                       \
                        pc++;                     \
                                                  \
                        if (arg)                  \
                            {                     \
                            const char* line = current_line + n; \
                                                                 \
                            imm_arg     imm = 0;                 \
                            reg_arg     reg = 0;                 \
                                                                 \
                            cmd_code mask = GetArguments(SkipSpaces(line), &imm, &reg, asm_program); \
                                                                                        \
                            if (mask & IMM_ARGUMENT)             \
                                pc += sizeof(imm);               \
                                                                 \
                            if (mask & REG_ARGUMENT)             \
                                pc += sizeof(reg);               \
                            }                                    \
                                                                 \
                        break;              

            #include "../../Arch/cmd.h"
            #undef CPU_CMD
        
            case UNKNOWN_COMAND:
            default:
                {
                printf("Unknow comand: %.4s\n, at line %zu\n", current_line, i);

                return ASM_TRNSLTR_UNKNOWN_COMAND;
                }
        
            }
        i++;
        }
    asm_program->number_of_compiliation += 1;

    ShowLabelsTable(asm_program);
    
    return SUCCESS;
    }


int SecondCompilation (Asmprogram* asm_program)
    {
    VERIFICATE_ASM_PROGRAM(return FAILURE, asm_program);
    
    const char** lines_array     = asm_program->lines_array;
    size_t       number_of_lines = asm_program->number_of_lines;
    
    size_t current_line = 0;
    size_t pc           = 0;
    
    size_t code_arr_current_limit = number_of_lines * 2 - sizeof(imm_arg) - sizeof(reg_arg) - sizeof(cmd_code);
    
    cmd_code* code_array = (cmd_code*) calloc (number_of_lines * 2, sizeof(code_array[0]));
    CHECK_PTR_STD_RET(code_array, BAD_CALLOC);
    
    FILE* listing = fopen("Examples/Listing/Ebat.lst", "w");
    CHECK_PTR_STD_RET(listing, ERROR_OPENING_FILE);

    size_t i = 0;
    while (i < number_of_lines)
        { 
        const char* current_line = SkipSpaces(lines_array[i]);
        
        if (*current_line == ':')
            {
            i++;
            continue;
            }
        
        char asm_comand[_MAX_COMAND_LENGTH_] = {0};
        
        int n = 0;
        sscanf (current_line, "%s%n", asm_comand, &n);  
        
        fprintf(listing, "%zu %s", pc, asm_comand);
        
        switch (cmd_code cmd = CompareLineWithComands (asm_comand))
        {
        #define CPU_CMD(name, num, arg, code) \
            case num:                       \
                if (!arg)                     \
                    code_array[pc++] = cmd;   \
                                              \
                if (arg)                      \
                    {                         \
                    const char* line = current_line + n; \
                                              \
                    imm_arg     imm = 0;      \
                    reg_arg     reg = 0;      \
                                              \
                    cmd_code mask = GetArguments(SkipSpaces(line), &imm, &reg, asm_program);   \
                                              \
                    if (!mask)                \
                        {                     \
                        printf("Wrong argument (line %.10s) for comand,"          \
                               "imm = %d, reg = %d \n", line - n, imm, reg);      \
                        return WRONG_ARGUMENT;\
                        }                     \
                                              \
                    cmd |= mask;              \
                    code_array[pc++] = cmd;   \
                                              \
                    if (cmd & IMM_ARGUMENT)   \
                        {                     \
                        *((imm_arg*)(code_array + pc)) = imm; \
                        pc += sizeof(imm);    \
                                              \
                        fprintf(listing, " %d ", imm); \
                        }                     \
                                              \
                    if (cmd & REG_ARGUMENT)   \
                        {                     \
                        *((reg_arg*)(code_array + pc)) = reg; \
                        pc += sizeof(reg);    \
                                              \
                        fprintf(listing, " %d ", reg);        \
                        }                     \
                    }                         \
                                              \
                break;                        
        
        #include "cmd.h"
        #undef CPU_CMD

        case UNKNOWN_COMAND:
        default:
            {
            printf("Unknow comand: %.4s\n, at line %zu\n", current_line, i);

            return ASM_TRNSLTR_UNKNOWN_COMAND;
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
        fprintf(listing, "\n");
        }

    cmd_code* temp = (cmd_code*)  realloc (code_array, pc * sizeof(cmd_code)); 
    CHECK_PTR_STD_RET(temp, BAD_REALLOC);

    asm_program->binary_code            = temp;
    asm_program->number_of_CPU_comands  = pc;
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

size_t SetArguments (Asmprogram* asm_program, cmd_code* code_array, const char* line) 
    {
    CHECK_PTR_STD_RET (line, return 0);
    VERIFICATE_ASM_PROGRAM(asm_program);

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
                              
    if (cmd & IMM_ARGUMENT)   
        {                     
        *((imm_arg*)(code_array + pc)) = imm;
        pc += sizeof(imm);    
        }                     
                              
    if (cmd & REG_ARGUMENT)   
        {                     
        *((reg_arg*)(code_array + pc)) = reg;
        pc += sizeof(reg);    
        } 

    return pc;                    
    }

cmd_code GetArguments (const char* line, imm_arg* imm, reg_arg* reg, Asmprogram* asm_program)
    {
    CHECK_PTRS_RET(return 0, line, imm, reg);
    VERIFICATE_ASM_PROGRAM(return 0, asm_program);

    cmd_code mask = 0;
    
    char first_char = *line;
    if (first_char == '[')
        {
        const char* closing_braket = strchr(line, ']');

        if (!closing_braket)
            {
            printf ("Syntax error: missing closing braket\n");
            return SYNTAX_ERROR;
            }

        mask |= MEMORY_ARGUMENT;
        ++line;
        }
    
    if (first_char == ':')
        {
        imm_arg temp = IsLabel(line + 1, asm_program);
        if (temp != -1)
            {
            *imm = (imm_arg) (temp);
            mask |= IMM_ARGUMENT;

            return mask;
            } 

        if (asm_program->number_of_compiliation) 
            {
            printf("%s - is wrong label\n", line);
            return 0;
            }
        
        
        *imm = -666;
        mask |= IMM_ARGUMENT;

        return mask; 
        }

    int n = 0;
    if (sscanf(line, "%d%n", imm, &n))
        {    
        mask |= IMM_ARGUMENT;

        line += n + 1;
        char plus = *(line);
    
        if (plus != '+')
            return mask;
        line = SkipSpaces (line);
        line += 1; // skip '+' 
        }
    
    char reg_code[33] = "";
    if (sscanf(line, "%s", reg_code))
        {
        *reg = IsReg(reg_code);

        if (!(*reg))
            {
            printf("System: SHITREG: Govno register\n");
            return NO_ARGUMENTS;
            }

        mask |= REG_ARGUMENT; 
        }
    
    return mask;
    }

const char*  GetFullProgammName (const char* src_name)
    {
    if (!src_name) return NULL;

    size_t full_name_length          = strlen(src_name) + strlen(_STD_COMMAND_FILE_PREFIX_) + 100;
    char*  direction_to_command_file = (char*) calloc (full_name_length, sizeof(char));
    if   (!direction_to_command_file)
         return NULL;

    snprintf (direction_to_command_file, full_name_length, "%s%s", _STD_COMMAND_FILE_PREFIX_, src_name);
        
    return direction_to_command_file;
    }

imm_arg IsLabel(const char* line, Asmprogram* asm_program)
    {
    VERIFICATE_ASM_PROGRAM(return -1, asm_program);

    int    number_of_labels = asm_program->current_number_of_labels ;
    label* lables_arr       = asm_program->labels_arr;

    line = SkipSpaces(line);

    printf("Mb this is label %s\n", line);
    for(int i = 0; i < number_of_labels; i++)
        {
        label* lbl = lables_arr + i;

        $s(line)
        $s(lbl->name)

        if (!stricmp(line, lbl->name))
            {
            $ $ $ 
                $s(line)
                $s(lbl->name)
                $i((lbl->cmd_address))
            return (imm_arg) (lbl->cmd_address);
            }
        }

    return -1;
    }

const char*  GetFullExecutingprogramName (const char* exe_name)
    {
    if (!exe_name) return NULL;
    
    size_t     full_name_length          = strlen(exe_name) + strlen(_STD_EXECUTING_program_PREFIX_) + strlen(_STD_EXECUTING_program_SUFFIX_) + 100;
    char*      direction_to_exe_program = (char*) calloc (full_name_length, sizeof(char));
    if (!direction_to_exe_program)
        return NULL;

    snprintf (direction_to_exe_program, full_name_length, "%s%s%s", _STD_EXECUTING_program_PREFIX_, exe_name, _STD_EXECUTING_program_SUFFIX_);
        
    return direction_to_exe_program;
    }

void ShowLabelsTable(Asmprogram* asm_program)
    {
    VERIFICATE_ASM_PROGRAM(return, asm_program);  
    
    label* labels_arr = asm_program->labels_arr;
    int number_of_labels = asm_program->current_number_of_labels;
  
    for(int i = 0; i < number_of_labels; i++)
        {
        label* lbl = labels_arr + i; 
        func_message("label[%d]: pc %zu, name %s\n", i, lbl->cmd_address, lbl->name);
        } 
    
    return;
    }