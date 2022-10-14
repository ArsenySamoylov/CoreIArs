#include <math.h>

#include "SuperStack.h"
#include "DebugFunctions.h"

#define fprintf_stars fprintf(dump_log, "****************************************************\n")
#define dump_log_printf(...) fprintf(dump_log, __VA_ARGS__)

const char* MedComissionErorrMessage[] =
    {
    "Stak pointer has NULL value\n",
    "Stak heap pointer has NULL value\n",
    "Wrong Stack status\n",
    "Wrong Stack capacity\n",
    "Wrong Stack top\n",
    "Opening StackCanary has died\n",
    "Closing StackCanary has died\n",
    "Opening HeapCanary has died\n",
    "Closing HeapCanary has died\n",
    "Hasz est gówno\n",
    "Sterty hasz est gówno\n",
    };

void SSdump(SuperStack* stk_ptr, unsigned flag_error, SrcLocationInfo src, const char* func)
    {
    FILE *dump_log = GetLog();
    if (!dump_log)
        {
        printf("Log file pointer has NULL value\n");
        return;
        }

    fprintf_stars;

    dump_log_printf( "SSdump activated from: \n\n");

    dump_log_printf( "function = %s\n", func ? func : "NULL");

    dump_log_printf( "Which called from: \n");

    dump_log_printf( "\tsource file = %s, \n", src.src_file ? src.src_file : "NULL");

    dump_log_printf( "\tsource function = %s, ", src.src_function ? src.src_function : "NULL");

    dump_log_printf( "source line = %d,\n", src.src_line);

    dump_log_printf( "\tvariable nickname = %s.\n", src.var_name ? src.var_name : "NULL");

    if (!stk_ptr)
        {
        dump_log_printf( "Error occured, given pointer to stack is invalid (Sad Meow)\n");
        dump_log_printf( "\n                   END OF SSDUMP               \n");
        fprintf_stars;
        dump_log_printf( "\n\n");
        return;
        }

    if (flag_error)
        {
        fprintf_stars;
        dump_log_printf( "\n");
        }

    for (int i = 0, error_bytes = sizeof(flag_error) * 8; i < error_bytes;i++ )
        {
        if (flag_error & (0x1 << i))
            {
            dump_log_printf( "Medcomission found error (error code %d) in stack: \n\t%s\n",
                              i, MedComissionErorrMessage[i]);
            }
        }

    fprintf_stars;

    dump_log_printf( "Stack initialization information: \n\n");
    
    dump_log_printf( "initialization name = %s, ", stk_ptr->init_inf.var_name ? stk_ptr->init_inf.var_name : "NULL");

    dump_log_printf( "initialization file = %s, \n", stk_ptr->init_inf.src_file ? stk_ptr->init_inf.src_file : "NULL");

    dump_log_printf( "initialization function = %s, ", stk_ptr->init_inf.src_function ? stk_ptr->init_inf.src_function : "NULL");

    dump_log_printf( "initialization line = %d.\n", stk_ptr->init_inf.src_line);

    fprintf_stars;

    dump_log_printf( "Stack structure information: \n\n");
    dump_log_printf( "%s[%zd] - stack name and top\n", (stk_ptr->init_inf).var_name, stk_ptr->top);
    dump_log_printf( "%zd - capacity\n", stk_ptr->capacity);
    dump_log_printf( "%p - heap adress.\n", (void *)stk_ptr->heap);

    dump_log_printf("%d est hasz.\n", stk_ptr->hash);
    dump_log_printf("%d est sterty hasz.\n", stk_ptr->heapHash);
    
    fprintf_stars;

    dump_log_printf( "Canary and hash status\n\n");
        
    fprintf_stars;

    if (!stk_ptr->heap)
        {
        dump_log_printf( "Heap pointer is invalid, therefore no Stack data ;(\n");
        dump_log_printf( "\n                   END OF SSDUMP               \n");
        fprintf_stars;
        dump_log_printf( "\n\n");
        return;
        }
    dump_log_printf( "Stack data: \n\n");
    #ifdef SSDUMP_ALL
        ssize_t size = stk_ptr->capacity;
        ssize_t top  = stk_ptr->top; //It`s not a size_t, it`s a ssize_t
    #else
        size_t  size =  stk_ptr->top + 1;
    #endif
    
    for (ssize_t i = 0; i < size; i++)
        {
        dump_log_printf( "%s[%zd] = ", (stk_ptr->init_inf).var_name, i);
        #ifdef SSDUMP_ALL
        if (i <  top)
            fprint_element_type (dump_log, stk_ptr->heap + i);
        else
            fprintf_element_t (dump_log, stk_ptr->heap + i);
        #else
        fprintf_element_type (dump_log, heap + i);
        #endif

        dump_log_printf( "\n");
        }
    
    dump_log_printf( "\n                   END OF SSDUMP               \n");
    fprintf_stars;
    dump_log_printf( "\n\n");
    }

#undef fprintf_stars
#undef dump_log_printf
