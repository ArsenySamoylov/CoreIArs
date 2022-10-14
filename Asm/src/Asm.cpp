#include <stdio.h>

#include "Asm.h"

// #ifndef LINUS_IS_MY_LIFE
// #warning "YOU SUCK!!\n"
// #endif

int main(const int argc, const char* const argv[])
    {
    if (argc != 2)
        {
        printf("This program requares 1 arguments: name of .txt file with program\n");
        printf("Press any key to close program\n");

        getchar();
        return -1;
        }

    // GetFullProgammName(argv[1]);
    //printf("%s\n", argv[0]);

    Asmprogram* new_program = OpenAssmprogram(argv[1]);
    if (!new_program)
        {
        printf("ERORR OCCURED MAKING NEW ASM PROGRAM!!!\n");
        return -2;
        } 
    
    TranslateSrcprogrameToBinaryCode (new_program);
   
    MakeExeForCPU (new_program, argv[1]);
    
    CloseAssmprogram (new_program);
    
    return 0;
    }