#ifndef ZARPLATA
#define ZARPLATA 

#pragma GCC diagnostic ignored "-Wunused-variable"

#include <stddef.h>

typedef unsigned char  cmd_code; 
typedef int            imm_arg;
typedef unsigned char  reg_arg;
typedef int            data;

const int SOFT_CPU_VERSION = 2;

struct IntelIArsSignature
    {
    int version;
    size_t number_of_comands;
    };

#endif