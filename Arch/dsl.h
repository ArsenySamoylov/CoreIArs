
#define GET_ARG     GetArgument (core, cmd & MASK);         \
                    CHECK_PTR_RET(argument, return FAILURE);

#define POP               StackPop(stk_ptr)

#define PUSH(push_arg)    StackPush(stk_ptr, push_arg)

#define CPU_JMP(name, num, condition)  CPU_CMD(name, num, 1,                                \
                                                            {                               \
                                                            if (POP condition POP)          \
                                                                {                           \
                                                                data* argument = GET_ARG;   \
                                                                core->ip = *argument;       \
                                                                }                           \
                                                            })
                              
