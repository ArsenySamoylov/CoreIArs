#include "SoftCPU.h"

int  CtorArsCore (ArsCore* core, const char* ars_file) 
    {                                                   
    CHECK_PTR_RET(core,     return NULL_CORE_PTR);
    CHECK_PTR_RET(ars_file, return NULL_ARS_FILE_PTR);
    
    FILE* ars_commands = fopen(ars_file, "rb");
    CHECK_PTR_STD_RET(ars_commands,  ERROR_OPENING_FILE);
    
    size_t number_of_comands = CheckSignature (ars_commands);
    CHECK_PTR_MSG_RET(number_of_comands, return WRONG_SIGNATURE, "Wrong signature in file (or there is no cmd_code \\_(@ @)_/ )\n");
    
    cmd_code* comands_array = (cmd_code*) calloc (number_of_comands, sizeof(cmd_code));
    CHECK_PTR_STD_RET(comands_array, BAD_CALLOC);
   
    size_t number_of_read_elements = fread (comands_array, sizeof(cmd_code), number_of_comands, ars_commands);
    
    if (number_of_read_elements != number_of_comands)
        {
        printf("Number of cmd_code (%zu) and number of read elements (%zu) doesn't match\n",
                             number_of_comands,            number_of_read_elements);
        return NUMBER_OF_COMANDS_DOESNT_MATCH;
        }
    
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
    VERIFICATE_CORE(core);

    //! @todo 
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