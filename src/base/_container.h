/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-07 23:21:46
 * @LastEditTime: 2019-09-08 18:34:27
 * @LastEditors: Please set LastEditors
 */
#ifndef _CONTAINER_H_
#define _CONTAINER_H_
#include "_iterator.h"

#define current(container) ((container_t*)container)->current(container)
#define first(container) ((container_t*)container)->first(container)
#define last(container) ((container_t*)container)->last(container)
#define find(container, data) ((container_t*)container)->find(container, data)
#define insert(container, node, data) ((container_t*)container)->insert(container, node, data)
#define remove(container, data) ((container_t*)container)->remove(container, data)
#define length(container) ((container_t*)container)->length

#define initialize_container(container, curr, first, last, find, insert, remove) do { \
    container->current = curr;                                        \
    container->first = first;                                         \
    container->last = last;                                           \
    container->find = find;                                           \
    container->insert = insert;                                       \
    container->remove = remove;                                       \
    container->iterator = container;                                  \
} while (0)

typedef struct _container {
    
    iterator_t (*current) (void* container); 
    iterator_t (*first) (void* container);   
    iterator_t (*last) (void * container);   
    iterator_t (*find) (void* container, void* data); 
    int (*insert) (void* container, iterator_t index, void* data); 
    int (*remove) (void* container, iterator_t index); 

} container_t;

#endif