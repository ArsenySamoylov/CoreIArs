#ifndef MY_LOG // turn off buferization? (mb add modes)
#define MY_LOG

#include <stdio.h>

//! @note if you want to change log file name
//!          than define LOGNAME with name before including this file
//! @note if you want to show logs in console
//!          than define LOGNAME without name
#ifndef LOGNAME
#define LOGNAME 

//#define LOGNAME "StdLogFile.txt"
#endif

struct SrcLocationInfo
{
    const char* var_name;
    const char* src_file;
    const char* src_function;
    int         src_line;
};

//#include "my_colors.h"
FILE* GetLog   ();

#define init_inf(name)  \
    (SrcLocationInfo{#name, __FILE__, __func__, __LINE__}) 

#define  src_loc(name)  \
    (SrcLocationInfo{#name, __FILE__, __func__, __LINE__})
                                                  
#endif