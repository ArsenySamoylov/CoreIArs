#ifndef STACK_CONFIG
#define STACK_CONGIG

#include "Config.h"
//! @note if you want to change type of elements, than change this typefef
typedef data element_t; 

//! @note define NDEBUG if you want to release project
#ifndef NDEBUG

//! @note if this macros defined then dump will dump all
//!          all elements from stack
#define SSDUMP_ALL
#endif

#define GZHA_UNDERSTOOD true //thx Ded

#endif