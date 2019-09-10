/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-07 23:28:17
 * @LastEditTime: 2019-09-10 10:00:00
 * @LastEditors: Please set LastEditors
 */
#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "_container.h"
#include "_type_value.h"
#define VEC_SIZE 100

typedef struct _vector
{
   container_t container;
   type_value_t _data[VEC_SIZE];
   unsigned int _size;
   
} vector_t;

extern void init_vector(vector_t*);

#endif