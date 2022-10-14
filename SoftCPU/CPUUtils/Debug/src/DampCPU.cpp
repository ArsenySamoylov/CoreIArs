#include "SoftCPU.h"
#include "DebugCPU.h"

static void ShowCPUcomands (const comands* const comands_array, const size_t number_of_comands);


void DumpCPUandStack(ExeProgram* program, unsigned error_flag)
    {
    if (!program)
        {
        printf ("Null exe program pointer\n");
        return;
        }
    
    const comands* comands_array = program->comands_array;
    if (!comands_array)
        {
        printf("Comands array pointers is NULL\n");
        return;
        }

    printf("CPU comands array:\n");
    ShowCPUcomands(comands_array, program->number_of_comands);

    SuperStack* stk_ptr = program->CPU_stk;
    
    if (!stk_ptr)
        {
        printf("Null stack pointer\n");
        return;
        }
    }

static void ShowCPUcomands (const comands* const comands_array, const size_t number_of_comands)
    {
    if (!comands_array)
        {
        printf("NULL comands array pointer\n");
        return;
        }
    
   // printf("Number of comands %zu\n", comands_array[15] );

    printf("   %d  ", 0);
    for (size_t i = 1; i < number_of_comands; i++)
        printf("  %.2zu  ", i);

    printf("\n");

    for (size_t i = 0; i < number_of_comands; i++)
        printf(" [%02d] ", comands_array[i]);

    printf("\n");
    return;
    }


void ShowHeap(element_t* heap, int top);

#define HEAP(stk_ptr)  ShowHeap( (stk_ptr) -> heap, (stk_ptr) -> top);

void ShowHeap(element_t* heap, int top)
    {
    if (!heap)
        {
        printf("FOOLLLLL, null ptr\n");
        return;
        }
    printf ("SUPER HEAP (top = %d): \n", top);

    for (int i = 0; i <= top; i++)
        {
        printf("heap[%d] = %d\n", i, *(heap + i));
        }
    printf("END OF SUPER HEAP\n");
    
    return;
}