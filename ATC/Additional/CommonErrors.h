#ifndef COMMONERRORS
#define COMMONERRORS

enum CommonErrors
    {
    NO_ARGUMENTS,
    WRONG_ARGUMENT, 
    WROMG_NUMBER_OF_ARGUMENTS,

    ERROR_OPENING_FILE,
    
    BAD_CALLOC,
    BAD_REALLOC,

    NULL_PTR,
    NULL_STRUCTURE_MEMBER,

    SYNTAX_ERROR,

    MAIN_ERROR,
    
    SUCCESS, 
    FAILURE,   
    };

static const char* COMMON_ERROR_MESSAGES[] =
                  {
                  "Dyrak, no arguments\n",
                  "Dyrachok, wrong argument",
                  "Fool, wrong number of arguments\n",

                  "Shoot, can't open file!",

                  };

#pragma GCC diagnostic ignored "-Wunused-value"
//! @note Use this macros with return val (for example: CHECK_PTR_RET(ptr, return NULL_PTR)) 
// 
#define CHECK_PTR_STD_RET(ptr, return_value)                           \
                                                {                      \
                                                if(!ptr)               \
                                                  {                    \
                                                  printf("%s common error: %s\n", __func__, COMMON_ERROR_MESSAGES[return_value]); \
                                                  return return_value; \
                                                  }                    \
                                                }

#define CHECK_PTR_MSG_RET(ptr, return_expression, ...)                 \
                                               {                       \
                                                if(!ptr)               \
                                                  {                    \
                                                  printf(__VA_ARGS__); \
                                                  return_expression;   \
                                                  }                    \
                                               }

#define CHECK_PTRS_RET(return_expression, ...) {                                                          \
                                      const void* __arszsr[] = {__VA_ARGS__};                             \
                                      int number_of_pointers = sizeof(__arszsr) / sizeof(__arszsr[0]);    \
                                                                                                          \
                                      for(int i = 0; i < number_of_pointers; i++)                         \
                                        {                                                                 \
                                        if (!__arszsr[i])                                                 \
                                          {                                                               \
                                          printf("%s: !ERORR! Null pointer (number of pointer %d),\n"     \
                                                 "\t%s, from this function\n",__func__, i + 1, #return_expression);        \
                                          return_expression;                                              \
                                          }                                                               \
                                        }                                                                 \
                                      }

#define CHECK_PTR_RET(ptr, return_expression)                                   \
                                          {                                     \
                                          if(!ptr)                              \
                                            {                                   \
                                            printf("\033[53m" "%s error: %s - NULL ptr\033[0m\n", __func__, #ptr);    \
                                            return_expression;                  \
                                            }                                   \
                                          }


#define func_message(...)  {                              \
                            printf("\t%s: ", __func__);   \
                            printf(__VA_ARGS__);          \
                            }                           

#endif