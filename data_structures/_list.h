/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-03 15:07:40
 * @LastEditTime: 2019-09-03 19:42:52
 * @LastEditors: Please set LastEditors
 */

#ifndef _list_h_
#define _list_h_
#include "_node.h"

#define list_head(list) (&((list)->sentinel))
#define list_tail(list) (&((list)->sentinel))
#define list_first(list) list_head(list)->next
#define list_last(list)  list_tail(list)->prev

#define list_init(list) do{             \
    list->size = 0;                     \
    list_first(list) = list_head(list); \
    list_last(list) = list_tail(list); \
}while(0)

typedef struct _list_node
{
    /* data */
    list_node_t* prve;
    list_node_t* next;
    node_t node;

} list_node_t;

typedef struct _list 
{
    list_node_t sentinel;
    unsigned int size;

} list_t;

extern list_node_t* list_search (list_t*, void*, node_cmp_func);

extern int list_insert (list_t*, node_t, list_node_t*);

extern int list_delete (list_t*, list_node_t*);

/*
extern int list_insert_head(list_t*, node_t);

extern int list_insert_tail(list_t*, node_t);

extern list_node_t* list_pull (list_t*, list_node_t*);

extern list_node_t* list_pull_head(list_t*);

extern list_node_t* list_pull_tail(list_t*);

*/
#endif
