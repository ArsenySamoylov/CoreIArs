#include <stdlib.h>
#include "my_log.h"

FILE* OpenLog  (const char* log_name = "std");
void  CloseLog ();

static FILE* my_log = OpenLog(LOGNAME);

FILE* GetLog()
    {
    return my_log;
    }
//! @note CHANGE!!!!!!!!!!
FILE* OpenLog(const char* log_name)
    {
    // if (log_name == "console")
    //     return stdout;

    FILE* file = fopen(log_name ? log_name : "", "w");

    if (!file)
        file = stdout;

    atexit(CloseLog);

    return file;//(file == NULL) ? ?????stdin?????? : file;   
    }

void CloseLog()
    {
    fputs("\n****************************************************", my_log);
    fputs("\n                Log Successfuly ended               ", my_log);
    fputs("\n****************************************************", my_log);

    if (my_log && my_log != stdout)
        fclose(my_log);
    }
