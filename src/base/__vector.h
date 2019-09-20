/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-07 23:28:17
 * @LastEditTime: 2019-09-14 18:56:31
 * @LastEditors: Please set LastEditors
 */
#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "__container.h"
#include "__type_value.h"

#define ALLOC_CHUNK_SIZE 10

typedef struct _vector
{
   container_t container;
   type_value_t* _data;
   unsigned int _size;
   unsigned int _capacity;
   
} vector_t;

extern void init_vector(vector_t*);

#endif