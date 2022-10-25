#include "Asm.h"

size_t CountPC (Asmprogram* asm_program, const char* line)
    {
    VERIFICATE_ASM_PROGRAM(return 0, asm_program);
    CHECK_PTR_RET(line, return 0);

    size_t pc = 0;

    imm_arg     imm = 0;                 
    reg_arg     reg = 0;                 
                                            
    cmd_code mask = GetArguments(SkipSpaces(line), &imm, &reg, asm_program); 
                                                                
    if (mask & IMM_ARGUMENT)             
        pc += sizeof(imm);               
                                            
    if (mask & REG_ARGUMENT)             
        pc += sizeof(reg);  

    return pc;             
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

imm_arg GetLabel (const char* line, Asmprogram* asm_program)
    {
    VERIFICATE_ASM_PROGRAM(return -1, asm_program);

    int    number_of_labels = asm_program->current_number_of_labels ;
    label* lables_arr       = asm_program->labels_arr;

    line = SkipSpaces(line);
    // printf("\n\tMb this is label (%s)\n", line);
    // ShowLine(line);
    // printf("\n");
    // sscanf(line, "%s", temp);

    for(int i = 0; i < number_of_labels; i++)
        {
        label* lbl = lables_arr + i;

        if (!skip_spaces_cmp(line, lbl->name))
            {
            return (imm_arg) (lbl->cmd_address);
            }
        }

    return NOT_A_LABEL;
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

int AddLabel(Asmprogram* asm_program, const char* current_line, size_t pc)
            {
            VERIFICATE_ASM_PROGRAM(return FAILURE, asm_program);

            label* new_label = (asm_program ->labels_arr) + (asm_program->current_number_of_labels);
            ++(asm_program->current_number_of_labels);
            
            new_label->name = SkipSpaces(current_line + 1);
            new_label->cmd_address = pc;

            return SUCCESS;
            }