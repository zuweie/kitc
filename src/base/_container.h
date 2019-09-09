/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-07 23:21:46
 * @LastEditTime: 2019-09-09 23:18:19
 * @LastEditors: Please set LastEditors
 */
#ifndef _CONTAINER_H_
#define _CONTAINER_H_
#include "_iterator.h"

#define container_first(container) ((container_t*)container)->first(container)
#define container_last(container) ((container_t*)container)->last(container)
#define container_find(container, data, compare) ((container_t*)container)->find(container, data, compare)
#define container_insert(container, iter, data) ((container_t*)container)->insert(container, iter, data)
#define container_remove(container, iter) ((container_t*)container)->remove(container, iter)

#define initialize_container(container, __first, __last, __find, __insert, __remove) do { \
    ((container_t*)container)->first = __first;                                         \
    ((container_t*)container)->last = __last;                                           \
    ((container_t*)container)->find = __find;                                           \
    ((container_t*)container)->insert = __insert;                                       \
    ((container_t*)container)->remove = __remove;                                       \
} while (0)

typedef struct _container {
    
    iterator_t (*first) (container_t* container);   
    iterator_t (*last) (container_t * container);   
    iterator_t (*find) (container_t* container, void* data, int (*compare)(void*, void*)); 
    int (*insert) (container_t* container, iterator_t iter, void* data); 
    int (*remove) (container_t* container, iterator_t iter); 
} container_t;

#endif