/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-03 15:07:40
 * @LastEditTime: 2019-09-10 11:15:36
 * @LastEditors: Please set LastEditors
 */

#ifndef _LIST_H_
#define _LIST_H_
#include "_type_value.h"
#include "_container.h"

#define list_head(list) (&((list)->sentinel))
#define list_tail(list) (&((list)->sentinel))
#define list_first(list) (list_head(list)->next)
#define list_last(list)  (list_tail(list)->prev)

#define list_init(list) do{             \
    list->size = 0;                     \
    list_first(list) = list_head(list); \
    list_last(list) = list_tail(list); \
}while(0)

typedef struct _list_node list_node_t;
typedef struct _list_node
{
    /* data */
    struct list_node_t* prve;
    struct list_node_t* next;
    type_value_t data;

};

typedef struct _list 
{
    container_t container;
    list_node_t sentinel;
    unsigned int size;
} list_t;

extern void init_list(list_t*);

#endif
