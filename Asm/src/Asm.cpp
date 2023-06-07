#include <stdio.h>

#include "Asm.h"

FILE* Listing = fopen("Ebat.lst", "w");

int main(const int argc, const char* const argv[])
    {
    if (argc != 2)
        {
        printf("This program requares 1 arguments: name of .txt file with program\n");
        printf("Press any key to close program\n");

        getchar();
        return WROMG_NUMBER_OF_ARGUMENTS;
        }
    
    if (!Listing)
        {
        printf ("Couldn't open file for listing\n");

        return MAIN_ERROR;
        }

    Asmprogram* new_program = OpenAssmprogram(argv[1]);
    if (!new_program)
        {
        printf("Couldn't open file in (%s)!!!\n", argv[1]);
        return MAIN_ERROR;
        } 
    
    int status = MakeCmdCode (new_program);
    if (status == SUCCESS)
        printf("Program successfully translated code for ArsCPU \n");
    else
        {
        printf("Ebat, error in compilation proceess\n");
        return MAIN_ERROR;
        }

    status = MakeExeForCPU (new_program, argv[1]);
    if (status == SUCCESS)
        printf("Program successfully put code in file: %s.ars\n\n\n", argv[1]);
    else
        {
        func_message("Erorr occurred making ars file\n");
        return MAIN_ERROR;
        }

    CloseAssmprogram (new_program);
    
    return 0;
    }
