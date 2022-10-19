#include "SoftCPU.h"
#include "DebugCPU.h"

#include <stdlib.h>

static void ShowCPUcomands (const cmd_code* const comands_array, size_t number_of_comands, size_t ip);

void DumpCPUandStack(ArsCore* core)
    {
    VERIFICATE_CORE(core);

    const cmd_code* comands_array = core->comands_array; // medcomission checked this ptr 

    printf("CPU cmd_code array (number of comands %zu, ip %zu):\n", core->number_of_comands, core->ip);
    ShowCPUcomands(comands_array, core->number_of_comands, core->ip);

    SuperStack* stk_ptr = &(core->CPU_stk);
    ShowHeap (stk_ptr->heap, stk_ptr->top);
    }

const size_t START_IP_FOR_DUMP = 3;
const size_t END_IP_FOR_DUMP   = 5;

static void ShowCPUcomands (const cmd_code* const comands_array, size_t number_of_comands, size_t ip)
    {
    CHECK_PTR_MSG_RET(comands_array, return, "NULL cmd_code array pointer\n");

    size_t starting_cmd = 0;

    if (ip > START_IP_FOR_DUMP)
        starting_cmd = ip - START_IP_FOR_DUMP;
    
    if (number_of_comands > ip + END_IP_FOR_DUMP)
        number_of_comands = ip + END_IP_FOR_DUMP;
    
    for (size_t i = starting_cmd; i < number_of_comands; i++)
        printf(" %3zu   ", i);

    printf("\n");

    for (size_t i = starting_cmd; i < number_of_comands; i++)
        printf(" [%03d] ", comands_array[i]);

    printf("\n");
    
    return;
    }

const ssize_t NUMBER_OF_LAST_HEAP_ELEMENTS = 4;

void ShowHeap(element_t* heap, ssize_t top)
    {
    CHECK_PTR_MSG_RET(heap, return, "NULL heap ptr\n")
    printf ("SUPER HEAP (top = %zd): \n", top);

    if (top == -1)
        return;

    ssize_t i = (top > NUMBER_OF_LAST_HEAP_ELEMENTS) ? top - NUMBER_OF_LAST_HEAP_ELEMENTS : 0;

    for (; i <= top; i++)
        {
        printf("heap[%zd] = %d\n", i, *(heap + i));
        }
    printf("END OF SUPER HEAP\n");
    
    return;
}