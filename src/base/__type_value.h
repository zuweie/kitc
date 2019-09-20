/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-03 13:29:13
 * @LastEditTime: 2019-09-20 20:26:49
 * @LastEditors: Please set LastEditors
 */

#ifndef _TYPE_VALUE_H_
#define _TYPE_VALUE_H_

typedef unsigned int type_value_size;

typedef union _type_value
{
   void* pointer;
   unsigned char type_value[sizeof(type_value_size)];
} type_value_t;

extern type_value_t int_type(int);
extern type_value_t float_type(float);
extern type_value_t pointer_type(void*);

extern int type_int(type_value_t);
extern float type_float(type_value_t);
extern void* type_pointer(type_value_t);

extern int compare_int(type_value_t, type_value_t);
extern int compare_float(type_value_t, type_value_t);
extern int compare_pointer(type_value_t, type_value_t);

#endif