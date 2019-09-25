/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-07 23:28:17
 * @LastEditTime: 2019-09-25 08:36:15
 * @LastEditors: Please set LastEditors
 */
#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "__container.h"
#include "__type_value.h"

#define VEC_ALLOC_CHUNK_SIZE 100

typedef struct _vector
{
   container_t container;
   type_value_t* _data;
   unsigned int _size;
   unsigned int _capacity;
   
} vector_t;

void init_vector(vector_t*);

#endif