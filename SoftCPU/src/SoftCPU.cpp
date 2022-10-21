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
        return WROMG_NUMBER_OF_ARGUMENTS;
        }
    
    ArsCore core = {};
    if ( (int flag_error = CtorArsCore (&core, argv[1])) != SUCCESS)
        {
        func_message("Can't create ArsCorp, (error %d)\n", flag_error);
        return MAIN_ERROR;
        }
            
    if ( (int status = ExecuteCPUCommands(&core)) != SUCCESS)
        {
        func_message("Ebat, something went wromg :/ (error %d)\n", ); 
        return MAIN_ERROR;
        }
           
    if ( (int status = DtorArsCore(&core)) != DEAD)
        {
        func_message("Ebat, You can't even kill f*cking Core (error %d)\n", status);
        return MAIN_ERROR;
        }

    return 0;    
    }
