/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 23:08:03
 * @LastEditTime: 2019-09-15 07:50:07
 * @LastEditors: Please set LastEditors
 */
#ifndef _STACK_H_
#define _STACK_H_

#include "_list.h"

typedef list_t stack_t;

extern void init_stack(stack_t*);
extern int push(stack_t*, type_value_t);
extern int pop(stack_t*, type_value_t*);

#endif 