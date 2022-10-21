#include <stdio.h>

#include "Asm.h"

int main(const int argc, const char* const argv[])
    {
    if (argc != 2)
        {
        printf("This program requares 1 arguments: name of .txt file with program\n");
        printf("Press any key to close program\n");

        getchar();
        return WROMG_NUMBER_OF_ARGUMENTS;
        }

    Asmprogram* new_program = OpenAssmprogram(argv[1]);
    if (!new_program)
        {
        printf("ERORR OCCURED MAKING NEW ASM PROGRAM (%s)!!!\n", argv[1]);
        return MAIN_ERROR;
        } 
    
    int status = MakeCmdCode (new_program);
    if (status == TRANSLATER_SUCCESS)
        {
        printf("Program successfully translated code for ArsCPU\n");
        }
   
    status = MakeExeForCPU (new_program, argv[1]);
    if (status == SUCCESS)
        {
        printf("Program successfully put code in file: %s.ars\n", argv[1]);
        }

    CloseAssmprogram (new_program);
    
    return 0;
    }