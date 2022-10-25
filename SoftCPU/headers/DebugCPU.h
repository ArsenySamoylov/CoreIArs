#ifndef DEBUG_CPU
#define DEBUG_CPU

const size_t START_IP_FOR_DUMP = 7;
const size_t END_IP_FOR_DUMP   = 10;

const ssize_t NUMBER_OF_LAST_HEAP_ELEMENTS = 4;

enum EXE_VERIFICATOR_ERRORS
    {
    NULL_EXE_PTR        = 0x1 << 0,
    NULL_COMANDS_ARRAY  = 0x1 << 1,
    NULL_STK_PTR        = 0x1 << 2,
    NULL_RAM_PTR        = 0x1 << 3,
    NULL_REG_ARRAY      = 0x1 << 4,
    };
    
#define $D DumpCPUandStack(core);

#define VERIFICATE_CORE(core, return_expression)                                             \
                                   {                                                         \
                                     if (MedComissionCPU(core))                              \
                                     {                                                       \
                                     func_message("Ebat, govno core %s, go and check it\n", #core); \
                                     return_expression;                                      \
                                     }                                                       \
                                   }

void ShowCPUcomands (const cmd_code* const comands_array, size_t number_of_comands, size_t ip);

#endif