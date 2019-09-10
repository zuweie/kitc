/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-03 13:29:13
 * @LastEditTime: 2019-09-10 09:41:28
 * @LastEditors: Please set LastEditors
 */

#ifndef _TYPE_VALUE_H_
#define _TYPE_VALUE_H_

typedef unsigned int type_value_size;

typedef union _type_value
{
   unsigned char type_value[sizeof(type_value_size)];
} type_value_t;

extern inline type_value_t int_type(int);
extern inline type_value_t float_type(float);
extern inline type_value_t pointer_type(void*);

extern inline int type_int(type_value_t);
extern inline float type_float(type_value_t);
extern inline void* type_pointer(type_value_t);

#endif