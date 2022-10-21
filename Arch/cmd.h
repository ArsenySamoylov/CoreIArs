//! THIS IS SUPER MEGA FUTURE USELLESS TECHNOLOGIES
//! @note CPU_CMD(name, num, arg, {code} )

#include "dsl.h"

CPU_CMD(HLT, 0, 0,         
                    {  
                    printf("THSI HLT\n");
                    return 0; 
                    })

CPU_CMD(PUSH, 1, 1, 
                    {
                    data* argument = GET_ARG;

                    printf("Push argument: %d\n\n", *argument);
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

                    data temp = POP;
                    *argument = temp;

                    printf("Pop from stk: %d, to adress %p\n\n", temp, (void*)argument);    
                    } )

CPU_CMD(ADD, 3, 0,
                    {
                    printf("This is add\n");
                    PUSH(POP + POP);
                    } )

CPU_CMD(SUB, 4, 0,
                    {
                    printf("This is SUB\n");    
                    PUSH(POP - POP);
                    })

CPU_CMD(MUL, 5, 0,
                    {
                    printf("This is MUL\n");
                    PUSH(POP * POP);
                    })

CPU_CMD(DIV, 6, 0,)

CPU_CMD(OUT, 7, 0,
                    {
                    func_message("OUT: %d\n", POP);    
                    })

CPU_CMD(IN, 8, 0,
                    {
                    data in_val = 0;
                    func_message("Enter value: ");
                    scanf("%d", &in_val);
                    printf("\n");

                    PUSH(in_val);   
                    })

CPU_CMD(JMP, 9, 1,
                    {
                    data* argument = GET_ARG;
                    core->ip = *argument;
                    })

CPU_JMP(JA,  10, >)
CPU_JMP(JAE, 11, >=)

CPU_JMP(JB,  12, <)
CPU_JMP(JBE, 13, <=)

CPU_JMP(JE,  14, ==)
CPU_JMP(JNE, 15, !=)