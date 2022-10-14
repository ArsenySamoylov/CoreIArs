#include "SoftCPU.h"

argument  GetArgumentForPush (ExeProgram* program, comands mask);
bytes*    GetArgumentForPop  (ExeProgram* program, comands mask);
 
ExeProgram* OpenExeProgram (const char* exe_file)
    {
    if (!exe_file)
        {
        printf("Null exe_file name\n");
        return NULL;
        }
    
    FILE* ars_commands = fopen(exe_file, "rb");
    
    if (!ars_commands)
        {
        printf("CPU can't open %s file\n", exe_file);
        return NULL;
        }
    
    size_t number_of_comands = CheckSignature (ars_commands);
    if (!number_of_comands)
        {
        printf("Wrong signature in file %s (or there is no comands \\_(@ @)_/ \n", exe_file);
        return NULL;
        } 
    
    comands* comands_array = NULL;
    comands_array = (comands*) calloc (number_of_comands, sizeof(comands));
    if (!comands_array)
        {
        printf("Can't allocate memory for comands array\n");
        return NULL;
        }

   
    size_t number_of_read_elements = fread (comands_array, sizeof(comands), number_of_comands, ars_commands);
    
    // //printf("Number of rd el: %zd, number of cmd: %zd\n", number_of_read_elements, number_of_comands);
    // struct stat text_data;
    // stat(exe_file, &text_data);
    // printf("File %s size: %zd\n", exe_file, text_data.st_size);
    // printf("Size of signature: %zd\n", sizeof(IntelIArsSignature));
    // printf("Size of commands array: %zd (num of commands: %zd)\n", text_data.st_size - sizeof(IntelIArsSignature),
    //                         (text_data.st_size - sizeof(IntelIArsSignature))/sizeof(comands) );
    // //
    if (number_of_read_elements != number_of_comands)
        {
        printf("Number of comands (%zu) and number of read elements (%zu) doesn't match\n",
                             number_of_comands,            number_of_read_elements);
        return NULL;
        }
    
    SuperStack  CPU_stack = {};
    StackCtor (&CPU_stack, CPU_STACK_INITIAL_CAPACITY);

    cpu_register* reg_arr = NULL;
    reg_arr = (cpu_register*) calloc(NUMBER_OF_REGISTERS, sizeof(cpu_register));
    if (!reg_arr)
        {
        printf("Canno't create reg arr\n");
        return 0;
        }
    
    bytes* RAM = NULL;
    RAM = (bytes*) calloc(_RAM_SIZE_, sizeof(bytes));
    if (!RAM)
        {
        printf("Ebat, buy HyperX instead of this sh*t\n");
        return NULL;
        }
    
    ExeProgram* temp = NULL;
    temp = (ExeProgram*) calloc (1, sizeof(ExeProgram));
    if (!temp)
        {
        printf("Calloc cant't allocate memory for ExeProgam strcucture\n");
        return NULL;
        }

    *temp = {comands_array, &CPU_stack, number_of_comands, 0, reg_arr, RAM};
    return temp;
    }

#define comands_array     ((program)->comands_array)
#define stk_ptr           ((program)->CPU_stk)
#define number_of_comands ((program)->number_of_comands)
#define ip                ((program)->ip)
#define reg_arr           ((program)->reg_arr)
#define RAM               ((program)->RAM)

int ExecuteCPUCommands (ExeProgram* program)
    {
    if (!program) return WRONG_PROGRAM_PTR; // Oshibka ebat

    while (ip < number_of_comands)
            {
            comands cmd = comands_array[ip];
            ++ip;

            switch (cmd & !MASK)
                {
                case CPU_PUSH:
                    {
                    if (!(cmd & MASK)) // this is extra cheking for debug, cause GetArguments also checks mask
                        {
                        printf("Ebat, something wrong with argument for push\n");
                        return WRONG_ARGUMENT;
                        }
                    if (cmd & MEMORY_ARGUMENT)
                        {
                        printf("Dyrachok, push can't work with  RAM arguments");
                        return WRONG_ARGUMENT;
                        }

                    argument arg = GetArgumentForPush (program, cmd & MASK);
                
                    StackPush(stk_ptr, arg);

                    break;
                    }
                case CPU_POP:
                    {
                    if (!(cmd & MASK)) // this is extra cheking for debug, cause GetArguments also checks mask
                        {
                        printf("Ebat, something wrong with argument for pop\n");
                        return WRONG_ARGUMENT;
                        }

                    if (cmd & MEMORY_ARGUMENT)
                        {
                        bytes* RamPtr = GetArgumentForPop (program, cmd & MASK);
                        if (!RamPtr) 
                            {
                            printf("Ebat, wrong argument for pop\n");
                            return WRONG_ARGUMENT;
                            }
                        *RamPtr = StackPop(stk_ptr);
                        }
                    else 
                        {
                        if (cmd & REG_ARGUMENT)
                            {

                            }
                        }
                    break;
                    }
                case CPU_ADD:
                    {
                    printf("Stack top before POPING :): %zd (+1)\n\n", stk_ptr->top);
                    int first_summand  = StackPop(stk_ptr);
                    int second_summand = StackPop(stk_ptr);
                    //
                    printf("First  summand (last value in the stack): %d\n",   first_summand);
                    printf("Second summand (last value in the stack): %d\n\n", second_summand);
                    printf("CPU comand %zd: (%d) add (%d) = (%d)\n",
                        (ip), first_summand, second_summand, first_summand + second_summand);

                    printf("Stack top before: %zd (+1)\n", stk_ptr->top);
                    //fuckDump(&stk_ptr);
                    
                    StackPush(stk_ptr, first_summand + second_summand);

                    printf("Stack top after: %zd (+1)\n\n", stk_ptr->top);

                    //HEAP(&stk_ptr)
                    break;
                    }
                default:
                    {
                    printf("I don't know %d comans, go buy new CoreIArs for only 300$(bucks)\n", cmd);
                    return UNKNOWN_COMAND;

                    break;
                    }
                }

            ++ip;
            }

    return BIG_SUCCESS; // something to return
    }

argument GetArgumentForPush (ExeProgram* program, comands mask)
    {
    if (!program)    return 0;
    if (!mask)       return 0;
    //VerificateExe(program);

    argument arg = 0;

    if (mask & IMM_ARGUMENT)
        {
        arg = *((argument*)comands_array);
        ip += sizeof(argument);
        }
    
    if (mask & REG_ARGUMENT)
        {
        arg += reg_arr[comands_array[ip]]; // check RAM value
        ip += sizeof(argument);
        }

    return arg;    
    }

// bytes* GetArgumentForPop (ExeProgram* program, comands mask)
//     {
//     if (!program)    return NULL;
//     if (!mask)       return NULL;
//     //VerificateExe(program);

//     argument* arg = NULL;

//     if (mask & MEMORY_ARGUMENT)
//     if (mask & IMM_ARGUMENT)
//         {
//         arg = (argument*)comands_array;
//         ip += sizeof(argument);
//         }
    
//     if (mask & REG_ARGUMENT)
//         arg = ; // check RAM value

//     ip += sizeof(argument);

//     return arg;    
//     }

#undef comands_array
#undef number_of_comands   
#undef ip  
#undef stk_ptr 
#undef reg_arr         
#undef RAM 

size_t CheckSignature (FILE* CPU_comands)
    {
    if (!CPU_comands)
        return 0;
    
    IntelIArsSignature signature = {}; 

    size_t read_elements =  fread (&signature, sizeof(IntelIArsSignature), 1, CPU_comands);
    if (!read_elements)
        return 0;
        
    if (signature.version != SOFT_CPU_VERSION)
        return 0;

    return signature.number_of_comands;
    }
