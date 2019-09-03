/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-03 15:07:45
 * @LastEditTime: 2019-09-03 19:41:06
 * @LastEditors: Please set LastEditors
 */

#include <stdlib.h>
#include "_list.h"
#include "mem_pool/_mem_pool.h"

extern list_node_t* list_search(list_t* list, void* target, node_cmp_func cmp) 
{
    list_node_t* first = list_first(list);

    for(;first != list_tail(list); first = first->next) {
        if (cmp(first, target) == 0) {
            return first;
        }
    }
    return NULL;
}

extern int list_insert(list_t* list, node_t node, list_node_t* before) 
{

    if (before)
    {
        
        list_node_t *list_node = (list_node_t *)allocate(alloc, sizeof(list_node_t));
        list_node->node = node;

        list_node->prve = before->prve;
        list_node->next = before;

        before->prve->next = list_node;
        before->prve = list_node;

        return ++list->size;
        return 0;
    }
    return -1;
}

extern int list_delete(list_t* list, list_node_t* del_node) 
{
    if (del_node) 
    {
        del_node->prve->next = del_node->next;
        del_node->next->prve = del_node->prve;

        if ( del_node->node.clean) {
            del_node->node.clean(&(del_node->node));
        }

        deallocate(alloc, del_node, sizeof(del_node));

        return --list->size;
    }
    return -1;
}