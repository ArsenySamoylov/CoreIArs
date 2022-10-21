#ifndef SUPER_DUPER_MEGA_XUEGA_STACK
#define SUPER_DUPER_MEGA_XUEGA_STACK

//! @note if you want to change settings than
//!          look up in SuperStackConfig.h
#include "SuperStackConfig.h"
#include "my_safety.h"
#include "my_log.h"

#ifndef NDEBUG
#define ON_SUPERDEBUG(...) __VA_ARGS__
#else
#define ON_SUPERDEBUG(...)
#endif

const size_t _HEAP_MIN_CAPACITY_ = 10;
const size_t _ELEMENT_T_SIZE_    = sizeof(element_t);

enum super_stack_status
    {
    UNINITIALIZED, 
    INITIALIZED,
    INITIALIZATION_ERR,
    DEAD,
    DESTRUCTOR_ERR, //WALKING_DEAD
    };

enum SuperStackCtorErr
    {
    NULL_STK_PTR_CTR       = -2,
    WRONG_CAPACITY         = -3,
    INITIALIZED_STACK      = -4,

    ERROR_INITIALIZATION   = -1,
    SUCCESS_INITIALIZATION =  1,
    };

struct SuperStack
    {
    #ifndef NCANARY
    CANARY opening_canary;
    #endif

    element_t* heap;// NULL is zero
    size_t     capacity;
    ssize_t    top;

    int status;// UNINITIALIZED is zero

    #ifndef NDEBUG
    SrcLocationInfo init_inf;
    #endif

    #ifndef NHASH
    int heapHash;
    int hash;
    #endif

    #ifndef NCANARY
    CANARY closing_canary;
    #endif
    };

int  SuperStackCtor (SuperStack* stk, size_t capacity
                     ON_SUPERDEBUG( , SrcLocationInfo init_inf)  );

void SuperStackDtor (SuperStack* stk             
                     ON_SUPERDEBUG( , SrcLocationInfo location)  );

void      SSpush    (SuperStack* stk, element_t value
                    ON_SUPERDEBUG( , SrcLocationInfo  location)  );

element_t SSpop     (SuperStack* stk
                    ON_SUPERDEBUG( , SrcLocationInfo  location)  );

element_t SStop     (SuperStack* stk                               // ded's old jokes: { return ZZTop(); }; 
                    ON_SUPERDEBUG( , SrcLocationInfo location)   ); 


#define StackCtor(stk_ptr, capacity) SuperStackCtor (stk_ptr, capacity                \
                                            ON_SUPERDEBUG(, init_inf(stk_ptr)) )                                                                                             

#define StackDtor(stk_ptr)           SuperStackDtor (stk_ptr                          \
                                            ON_SUPERDEBUG(, src_loc(stk_ptr))  )
          
#define StackPush(stk_ptr, value)        SSpush     (stk_ptr, value                   \
                                            ON_SUPERDEBUG(, src_loc(stk_ptr))  )

#define StackPop(stk_ptr)                SSpop      (stk_ptr                          \
                                            ON_SUPERDEBUG(, src_loc(stk_ptr))  )

#define StackTop(stk_ptr)                SStop      (stk_pte                          \
                                            ON_SUPERDEBUG(, src_loc(stk_ptr))  )

void     SSdump         (SuperStack* negoden, unsigned flag_err, 
                         SrcLocationInfo src_inf, const char* calling_func);
                         
unsigned MedComissionSS (SuperStack* prezyvnik); 

#define fuckDump(stk)   \
    SSdump(stk, MedComissionSS(stk), init_inf(stk), __func__) /// It`s beter than your shit
#endif