//! THIS IS SUPER MEGA FUTURE USELLESS TECHNOLOGIES
//! Copytoght (C) Automatic Research Systems (ARS), Inc.
//! @note CPU_CMD(name, num, arg, {code} )

#ifndef SOFT_CPU_VERSION
#define SOFT_CPU_VERSION  ( 2 )
#endif

//#pragma GCC diagnostic ignored "-Wfloat-conversion"

#include "dsl.h"

#define ACCURACY (REG_ARR[0])

CPU_CMD(HLT, 0, 0,         
                    {  
                    printf("THSI HLT\n");
                    return SUCCESS; 
                    })

CPU_CMD(PUSH, 1, 1, 
                    {
                    data* argument = GET_ARG;
                    PUSH(*argument);
                    })

CPU_CMD(POP, 2, 1,
                    {
                    if ( (cmd & IMM_ARGUMENT) && !(cmd & MEMORY_ARGUMENT) ) 
                        {
                        printf("Ebat, something wrong with argument for pop\n");
                        return WRONG_ARGUMENT;
                        }

                    data* argument = GET_ARG;

                    // printf("pop argument address %p\n", (void*) argument);
                    
                    data temp = POP;
                    *argument = temp;

                    // printf("Pop from stk: %d, to adress %p\n\n", temp, (void*)argument);    
                    } )

CPU_CMD(ADD, 3, 0,
                    {
                    //printf("This is add\n");
                    PUSH(POP + POP);
                    } )

CPU_CMD(SUB, 4, 0,
                    {
                    //printf("This is SUB\n");    
                    PUSH(POP - POP);
                    })

CPU_CMD(MUL, 5, 0,
                    {
                    //printf("This is MUL\n");
                    PUSH(POP * POP);
                    })

CPU_CMD(DIV, 6, 0,
                    {
                    PUSH( POP / POP);
                    })

CPU_CMD(OUT, 7, 0,
                    {
                    func_message("OUT: %lg\n", (double)(POP) );    
                    })

CPU_CMD(IN, 8, 0,
                    {
                    data in_val = 0;
                    func_message("Enter value: ");
                    scanf("%d", &in_val);
                    printf("\n");

                    PUSH(in_val);   
                    })

#define CPU_JMP(name, num, condition)  CPU_CMD(name, num, 1,                                \
                                                            {                               \
                                                            if (POP condition POP)          \
                                                                {                           \
                                                                data* argument = GET_ARG;   \
                                                                core->ip = *argument;       \
                                                                }                           \
                                                            else                            \
                                                                core->ip += sizeof(data);   \
                                                            })


#define COSTYLLL  || true ||

CPU_JMP(JMP, 9, || true ||)

CPU_JMP(JA,  10, >)
CPU_JMP(JAE, 11, >=)

CPU_JMP(JB,  12, <)
CPU_JMP(JBE, 13, <=)

CPU_JMP(JE,  14, ==)
CPU_JMP(JNE, 15, !=)

CPU_CMD(OUTS, 16, 0, 
                    {
                    PUTS;
                    } )
        
CPU_CMD(RET, 17, 0,
                    {
                    core->ip = POP_CALL;    
                    })

CPU_CMD(CALL, 18, 1,
                    {
                    data* argument = GET_ARG;

                    PUSH_CALL(core->ip);
                    core->ip = *argument;    
                    })

CPU_CMD(wait, 19, 0, 
                    {
                    printf("I am waiting for you, my master\n Press any key to punish me\n");
                    getchar();
                    })

CPU_CMD(FPUSH, 20, 1, 
                    {
                    data* argument = GET_ARG;

                    PUSH(*argument * ACCURACY);
                    })

//! @note lis' budy b' s' to change it (this function does the same thing as pop, so no need for extra command in CPU)
//! @note move to preproccessor
CPU_CMD(FPOP, 21, 1,
                    {
                    if ( (cmd & IMM_ARGUMENT) && !(cmd & MEMORY_ARGUMENT) ) 
                        {
                        printf("Ebat, something wrong with argument for fpop\n");
                        return WRONG_ARGUMENT;
                        }

                    data* argument = GET_ARG;

                    // printf("pop argument address %p\n", (void*) argument);

                    data temp = POP;
                    *argument = temp;    
                    })

CPU_CMD(FDIV, 22, 0,
                    {
                    double first =  POP;
                    double second = POP;

                    data result = (data) ((first / second) * ACCURACY);
                    PUSH(result);
                    })

CPU_CMD(FMUL, 23, 0,
                    {
                    PUSH( POP * POP / ACCURACY);
                    })   

CPU_CMD(FOUT, 24, 0,
                    {
                    func_message("Fout: %lg\n", (POP * 1.0)/ ACCURACY);
                    })

CPU_CMD(FIN, 25, 0,
                    {
                    double in_val = 0;
                    func_message("Enter double value: ");
                    scanf("%lg", &in_val);
                    printf("\n");

                    PUSH( (data)(in_val * ACCURACY));
                    })

CPU_CMD(SQRT, 26, 0, 
                    {
                    double val = (double) POP / ACCURACY;
                    val = sqrt(val); 

                    PUSH( data(val * ACCURACY) );
                    })
CPU_CMD(DUMP, 27, 0,
                    {
                    $D    
                    })
CPU_CMD(POW, 28, 0,
                    {
                    double power = (double) POP / ACCURACY;
                    // printf("POWER: %lg\n", power);
                    double base  = (double) POP / ACCURACY;

                    // printf ("Power %lg, base %lg\n", power, base);

                    PUSH( (data) (pow(base, power) * ACCURACY));
                    })

CPU_CMD(RAM, 29, 0,
                    {
                    for (int i = 0; i < 10; i++)
                        printf("[%d] = %d (%p)\n", i, core->RAM[i], core->RAM + i);
                    })

CPU_CMD(SIN, 30, 0, {
                    double value = (double) POP / ACCURACY;
                    printf("Sin(%lg)\n", value);
                    PUSH( (data) (sin(value) * ACCURACY));
                    })

CPU_CMD(COS, 31, 0, {
                    double value = (double) POP / ACCURACY;
                    
                    PUSH( (data) (sin(value) * ACCURACY));
                    })
