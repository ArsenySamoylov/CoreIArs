#include "SoftCPU.h"
#include "SuperStack.h"

#include <stdio.h>

int main(const int argc, const char* const argv[])
    {
    if (argc != 2)
        {
        printf("This program requares 1 argument: name of .ars file with program\n");
        printf("Press any key to close program\n");

        getchar();
        return -1;
        }
    
    ExeProgram* program = OpenExeProgram (argv[1]);
    
    if (!program)  return -1;
    
    VerificateExe(program);
    $
    StackPush(program->CPU_stk, 666);
    $
    //ShowHeap( (program->CPU_stk)->heap, (program->CPU_stk).top);
    
    getchar();
    //DumpCPUandStack(program, &CPU_stack);
    //getchar();

    int status = ExecuteCPUCommands(program);

    return 0;    
    }