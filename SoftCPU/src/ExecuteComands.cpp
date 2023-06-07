#include "SoftCPU.h"
#include "show_binary.h"
#include "DebugCPU.h"

data* GetArgument (ArsCore* core, cmd_code mask);

int ExecuteCPUCommands (ArsCore* core)
    {
    if (!core) return NULL_PTR; 
    VERIFICATE_CORE(core, return FAILURE);
    
    const cmd_code*   comands_array     =   core->comands_array;
    SuperStack*       stk_ptr           = &(core->CPU_stk);
    SuperStack*       call_stk_ptr      = &(core->Call_stk);
    size_t            number_of_comands =   core->number_of_comands;
    data*             REG_ARR           =   core->REG_ARR;
    data*             RAM               =   core->RAM;

    SetAccuracy(core);

    while (core->ip < number_of_comands)
            {
            cmd_code cmd = comands_array[core->ip];
            ++(core->ip);

            // printf("CMD: ");
            // ShowCharInBinary(cmd);
            
            // printf("CMD AND MASK: ");
            // ShowCharInBinary((char) (cmd & ~MASK));
            
            switch (cmd & ~MASK)
                {
                #define CPU_CMD(name, num, arg, code)       \
                    case num:                               \
                                                            \
                        code                                \
                                                            \
                        break;

                #include "cmd.h"
                #undef CPU_CMD             

                default:
                    {
                    printf("I don't fucking know %d comand, go buy new CoreIArs for only 300$(bucks)\n", cmd & ~MASK);
                    $D
                    return UNKNOWN_COMAND;

                    break;
                    }
                }

            }

    return SUCCESS; // something to return
    }

data* GetArgument (ArsCore* core, cmd_code mask)
    {
    if (!mask)    return NULL;
    VERIFICATE_CORE(core, return NULL);

    const cmd_code*   comands_array     = core->comands_array;
    size_t            number_of_comands = core->number_of_comands;
    data*             REG_ARR           = core->REG_ARR;
    data*             RAM               = core->RAM;

    data*       arg = NULL;
    static data buffer = 0;

    if (mask & IMM_ARGUMENT)
        {
        #pragma GCC diagnostic ignored "-Wcast-qual"
        buffer = (data) (* ( (imm_arg*) (comands_array + core->ip) ) );
        core->ip+= sizeof(imm_arg);
        
        // printf("Buffer: %d\n", buffer);
        }
    
    if (mask & REG_ARGUMENT)
        {
        if (comands_array[core->ip] - 1 > _REGISTER_ARRAY_SIZE_)
            {
            func_message("Yo, you trying to reach register (%d), that doesn't exist\n", comands_array[core->ip]);
            return NULL;
            }

        arg = REG_ARR + comands_array[core->ip]; // check RAM value
        core->ip += sizeof(reg_arg);


        if (! (mask & (~REG_ARGUMENT)) )
            return arg;


        buffer += *arg ; 
        
        // printf("Register value: %d, total val: %d\n", *arg, buffer);
        }
    
    if (mask & MEMORY_ARGUMENT)
        {
        if (buffer > _RAM_SIZE_)
            {
            func_message("Ebat, dyrachok, RAM SIZE is %d, and you truing to accsess %d\n", _RAM_SIZE_, buffer);
            return NULL;
            }

        arg = RAM + buffer;

        return arg;
        }

    return &buffer;    
    }

void SetAccuracy(ArsCore* core)
    {
    VERIFICATE_CORE(core, return);

    (core->REG_ARR)[0] = _ACCURACY_;

    return;
    }