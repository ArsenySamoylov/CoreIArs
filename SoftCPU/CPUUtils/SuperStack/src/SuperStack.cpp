#include "SuperStack.h"

int      SSresize       (SuperStack* stk, int mode);
void     FillPoisonHeap (element_t* heap, size_t size);

int _HEAP_GROWTH_RATE_    = 2;
int _HEAP_REDUCTION_RATE_ = 2;

enum SSresize
    {
    INCREASE_STACK =  1,
    DECREASE_STACK = -1,
    };

#define verificateSS(soldat, SrsLoc, ...)                             \
    do                                                                \
    {                                                                 \
    unsigned flag_err = MedComissionSS (soldat);                      \
    /*printf("I am verifiacator, error flag = %d\n", flag_err); */    \
    if (flag_err != 0)                                                \
        {                                                             \
        SSdump (soldat, flag_err, SrsLoc, __func__);                  \
                                                                      \
        return __VA_ARGS__;                                           \
        }                                                             \
    } while (0)

// Dany's macros breaks if NCANARY defined
//stk->hash     = generateHash(&stk->opening_canary, &stk->heapHash);  /! - change this char
#define KURWA_HASH(stk)                                                     \
do                                                                          \
{                                                                           \
    stk->heapHash = generateHash(stk->heap, stk->heap + stk->capacity);     \
                                                                            \
    stk->hash     = generateHash(&stk->opening_canary, &stk->heapHash);     \
} while (0)

int SuperStackCtor (SuperStack* stk, size_t capacity
                   ON_SUPERDEBUG(, SrcLocationInfo init_inf) )
    {
    if (!stk)                                 return NULL_STK_PTR_CTR ;
 // if (capacity < 0)                         return WRONG_CAPACITY   ;
    if (stk->status != UNINITIALIZED)         return INITIALIZED_STACK;

    stk->capacity = capacity;
    stk->top      = -1;
    stk->status   = INITIALIZED;

    if (capacity > 0) 
        stk->heap = (element_t*) canary_calloc (capacity, sizeof (element_t));

    stk->opening_canary = _OPENING_CANARY_;
    stk->closing_canary = _CLOSING_CANARY_;

    #ifndef NDEBUG
    FillPoisonHeap (stk->heap, capacity);
    stk->init_inf = init_inf;
    #endif

    KURWA_HASH(stk);
    verificateSS(stk, init_inf, ERROR_INITIALIZATION);

    return SUCCESS_INITIALIZATION;
    }

void SuperStackDtor (SuperStack* stk
                    ON_SUPERDEBUG(, SrcLocationInfo location) )
    {
    verificateSS(stk, location);
    
    canary_free ((void*) stk->heap);

    stk->status = DEAD; 

    stk->heap     = NULL;
    stk->capacity =  0;
    stk->top      = -1; 
    }

void  SSpush (SuperStack* stk, element_t value
              ON_SUPERDEBUG( , SrcLocationInfo  location)  )
    {
    //if (stk == NULL)   return;
    $
    verificateSS(stk, location);
    $
    /*
    if (!stk->capacity)
        {
        stk->heap     = (element_t*) canary_realloc(stk->heap, _HEAP_MIN_CAPACITY_, _ELEMENT_T_SIZE_);
        stk->capacity = _HEAP_MIN_CAPACITY_;
        }

    if (stk->top + 1 >= stk->capacity)
        {
        stk->heap = (element_t*) canary_realloc(stk->heap, stk->capacity*2, _ELEMENT_T_SIZE_);
        stk->capacity *= 2;/// Why 2? Why not 'const int MY_SACK_CONST_FOR_GROTH_BY_TWO = 2;'
        }
     */
   
    if ( (!stk->capacity) || ( (size_t) (stk->top + 1) >= stk->capacity) )
        {
        int flag_error = SSresize(stk, INCREASE_STACK);

        if (flag_error != 1)
            return; // Ebat oshibka!
        }
        
    (stk->top)++; 
    (stk->heap)[stk->top] = value; // make own memcpy for custom structure(deep copy);
    

    printf("Push top = %zd, value = %d\n", stk->top, value);

    KURWA_HASH(stk);
    verificateSS(stk, location);
    }

 element_t SSpop    (SuperStack* stk
                    ON_SUPERDEBUG( , SrcLocationInfo  location) )
    {
    verificateSS(stk, location, 0);

    if (stk->top      == -1)   return 0;
    if (stk->capacity ==  0)   return 0;

    //change to SSresize
    if (stk->capacity / (_HEAP_REDUCTION_RATE_ * 2) > (size_t) (stk->top + 1))
        {
        SSresize(stk, DECREASE_STACK);
        /*
        stk->heap      = (element_t*) canary_realloc(stk->heap, stk->capacity / 2, _ELEMENT_T_SIZE_); // heap затирается
        stk->capacity /= 2;
        */
        }

    element_t temp = stk->heap[(stk->top)--];

    KURWA_HASH(stk);
    verificateSS(stk, location, 0);

    return temp;
    }

element_t SStop   (SuperStack* stk 
                  ON_SUPERDEBUG(, SrcLocationInfo location) )
    {
    verificateSS(stk, location, 0);

    if (stk->top == -1)
        return 0;
        
    return (stk->heap)[(stk->top)];
    }

#define ERROR_OCCURED (-1)
#define TOTAL_SUCCESS  (1)

int SSresize (SuperStack* stk, int mode)
    {
    if (!stk)           return ERROR_OCCURED;
    if (!stk->heap)     return ERROR_OCCURED;
    
    element_t* temp_heap  = stk->heap;
    size_t     capacity   = stk->capacity;
    ssize_t    top        = stk->top; //?

    size_t new_capacity = 0;

    if (mode == INCREASE_STACK)
        {
        if (capacity == 0)
            new_capacity = _HEAP_MIN_CAPACITY_;
        else 
            new_capacity = capacity * _HEAP_GROWTH_RATE_;
        }

    if (mode == DECREASE_STACK)
        {
        if (capacity == 0)
            return ERROR_OCCURED;
        else
            new_capacity = capacity / _HEAP_REDUCTION_RATE_;
        }
    if ((size_t) (top + 1 )>= new_capacity)
        return ERROR_OCCURED;

    temp_heap = (element_t*) canary_realloc (temp_heap, new_capacity, _ELEMENT_T_SIZE_ );

    if (!temp_heap)
        return ERROR_OCCURED;

    stk->heap     = temp_heap;
    stk->capacity = new_capacity;

    return TOTAL_SUCCESS;
    }
#undef ERROR_OCCURED
#undef TOTAL_SUCCESS