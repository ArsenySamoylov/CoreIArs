#ifndef DEBUG_FUNCTIONS
#define DEBUG_FUNCTIONS

#include <stdio.h>
#include "SuperStackConfig.h"

unsigned enum MedComissionSS_err
    {
    NULL_STK_PTR_ERR         = 0x1 <<  0,
    NULL_STK_HEAP            = 0x1 <<  1,
    WRONG_STK_STATUS         = 0x1 <<  2,
    WRONG_STK_CAPACITY       = 0x1 <<  3, 
    WRONG_STK_TOP            = 0x1 <<  4,
    DEAD_STACKOPENING_CANARY = 0x1 <<  5,
    DEAD_STACKCLOSING_CANARY = 0x1 <<  6,
    DEAD_HEAPOPENING_CANARY  = 0x1 <<  7,
    DEAD_HEAPCLOSING_CANARY  = 0x1 <<  8,
    STACK_HASH_IS_DAMAGED    = 0x1 <<  9,
    HEAP_HASH_IS_DAMAGED     = 0x1 << 10,
    };

const int    IntPoison    = 0xBADDED;
const char   CharPoison   = '\0';
const double DoublePoison = NAN;

void fprintf_element_t(FILE* file, element_t* ptr);/////

//! @note if you want to use SSDump with unsupported type
//!       than add your own  function
void fprint_element_type(FILE* file, int*    element);
void fprint_element_type(FILE* file, char*   element);
void fprint_element_type(FILE* file, double* element);
    
//! @note if you want to debug Stack with unsupported type
//!       than add your own FillPoison and IsPoison function
int IsPoison   (const int*    element);
int IsPoison   (const char*   element);
int IsPoison   (const double* element);

void FillPoison (int*    element);
void FillPoison (char*   element);
void FillPoison (double* element);

#endif