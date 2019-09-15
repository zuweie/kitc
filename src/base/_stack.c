/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-15 03:50:15
 * @LastEditTime: 2019-09-15 03:59:56
 * @LastEditors: Please set LastEditors
 */
#include "_stack.h"

void init_stack(stack_t* stack) {
    return init_list(stack);
}

int push(stack_t* stack, type_value_t v ) 
{
    return container_insert(stack, container_first(stack), v);
}

int pop(stack_t* stack, type_value_t* v)
{
    return container_remove(stack, container_first(stack), v);
}