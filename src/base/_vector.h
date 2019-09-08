/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-07 23:28:17
 * @LastEditTime: 2019-09-08 22:28:19
 * @LastEditors: Please set LastEditors
 */
#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "_container.h"
#include "_node.h"
#define VEC_SIZE 100

typedef struct _vector_iterator {
   iterator_t iterator;
   unsigned int position;

} vector_iterator_t;

typedef struct _vector
{
   container_t container;
   node_t data[VEC_SIZE];
   unsigned int _index;
   unsigned int _size;
   
} vector_t;

extern void init_vector(vector_t*);

#endif