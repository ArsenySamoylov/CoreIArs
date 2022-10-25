#include "SoftCPU.h"

int  CtorArsCore (ArsCore* core, const char* ars_file) 
    {                                                   
    CHECK_PTR_RET(core,     return NULL_CORE_PTR);
    CHECK_PTR_RET(ars_file, return NULL_ARS_FILE_PTR);
    
    cmd_code* comands_array = NULL;
    size_t number_of_comands = SetComandsArrayAndCheckSignature (&comands_array, ars_file);
    CHECK_PTR_RET(comands_array, return NULL_COMANDS_ARRAY);
   
    StackCtor (&(core->CPU_stk),   CPU_STACK_INITIAL_CAPACITY); 
    StackCtor (&(core->Call_stk), CALL_STACK_INITIAL_CAPACITY); 

    CHECK_PTR_RET(core->REG_ARR, return NULL_REG_ARR);
    
    int* RAM = (data*) calloc(_RAM_SIZE_, sizeof(RAM[0]));
    CHECK_PTR_MSG_RET(RAM, BAD_CALLOC, "Ebat, buy HyperX instead of this sh*t\n");

    core->comands_array = comands_array;
    core->number_of_comands = number_of_comands;
    core->ip = 0;
    core->RAM =  RAM;

    VERIFICATE_CORE(core, FAILURE)
    return SUCCESS;
    }

int DtorArsCore (ArsCore* core)
    {
    VERIFICATE_CORE(core, return FAILURE);

    //! @todo 
    return DEAD;
    }


size_t CheckSignature (FILE* CPU_comands)
    {
    if (!CPU_comands)
        return 0;
    
    IntelIArsSignature signature = {}; 

    size_t read_elements =  fread (&signature, sizeof(IntelIArsSignature), 1, CPU_comands);
    if (!read_elements)
        return 0;
        
    if (signature.version != SOFT_CPU_VERSION)
        return 0;

    return signature.number_of_comands;
    }

size_t SetComandsArrayAndCheckSignature (cmd_code** cmd_arr, const char* ars_file)
    {
    CHECK_PTRS_RET(return 0, ars_file, cmd_arr);

    FILE* ars_commands = fopen(ars_file, "rb");
    CHECK_PTR_RET(ars_commands,  return 0);
    
    size_t number_of_comands = CheckSignature (ars_commands);
    if (!number_of_comands)
        {
        func_message ("Wrong signature in file %s (or there is no cmd_code \\_(@ @)_/ )\n", ars_file);
        return 0;
        }
         
    cmd_code* comands_array = (cmd_code*) calloc (number_of_comands, sizeof(cmd_code));
    CHECK_PTR_RET(comands_array, return 0);
   
    size_t number_of_read_elements = fread (comands_array, sizeof(cmd_code), number_of_comands, ars_commands);    
    if (number_of_read_elements != number_of_comands)
        {
        printf("Number of cmd_code (%zu) and number of read elements (%zu) doesn't match\n",
                             number_of_comands,            number_of_read_elements);
        return 0;
        }

    *cmd_arr = comands_array;

    return number_of_comands;
    }