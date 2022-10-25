
#define GET_ARG     GetArgument (core, cmd & MASK);         \
                    CHECK_PTR_RET(argument, return FAILURE);


#define POP               StackPop (stk_ptr)
#define PUSH(push_arg)    StackPush(stk_ptr, push_arg)

#define PUSH_CALL(ret_ip)  StackPush (call_stk_ptr, ret_ip)   
#define POP_CALL           StackPop (call_stk_ptr)

#define PUTS            \
        {               \
        data ch = POP;  \
        while (ch)      \
            {           \
            putchar(ch);\
            ch = POP;   \
            }           \
        }



                              
