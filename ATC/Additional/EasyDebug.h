#ifndef DEBUG_FROM_NIGTH_TO_MORNIG
#define DEBUG_FROM_NIGTH_TO_MORNIG (false)

#pragma GCC diagnostic ignored "-Wformat="

#define $i(int_var)     {printf("\t%s: %d\n", #int_var, int_var);          }
#define $c(char_var)    {printf("\t%s: %c\n", #char_var, char_var);        }
#define $d(double_var)  {printf("\t%s: %lg\n", #double_var, double_var);   }
#define $s(string)      {printf("\t%s: %.20s\n", #string, string);         }
#define $p(pointer)     {printf("\t%s: %p\n", #pointer, (void*)pointer);         }


#define $                                                                                       \
    do                                                                                          \
    {                                                                                           \
        /*set_color*/                                                                           \
                                                                                                \
        printf("I AM WORKING IN FUNCTION: %s, in line: %d\n", __func__, __LINE__);/*add colors*/\
                                                                                                \
        /*reset_color*/                                                                         \
    } while (0);

//! @todo print all given parametrs (add later)
#define $$                                                          \
    do                                                              \
    {                                                               \
    printf("Enter any key to continue (line %d, func %s)\n", __LINE__, __func__);       \
    getchar();                                                      \
    } while (0);  
    
#endif