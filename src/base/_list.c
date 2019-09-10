/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-03 15:07:45
 * @LastEditTime: 2019-09-10 11:14:00
 * @LastEditors: Please set LastEditors
 */

#include <stdlib.h>

#include "_type_value.h"
#include "_iterator.h"
#include "_container.h"

#include "_list.h"
#include "_mem_pool.h"


static iterator_t get_iter (void* refer);

static iterator_t _dereference(iterator_t it) 
{
    
}

static iterator_t _next (iterator_t it) 
{

}

static iterator_t _prev (iterator_t it)
{
    
}

list_node_t* list_search(list_t* list, void* target) 
{
    list_node_t* first = list_first(list);

    for(;first != list_tail(list); first = first->next) {
        /*
        if (cmp(first, target) == 0) {
            return first;
        }
        */
    }
    return NULL;
}

int list_insert(list_t* list, node_t node, list_node_t* before) 
{

    if (before)
    {
        int ret;
        list_node_t *list_node = NULL; //(list_node_t *)allocate(pool(&ret), sizeof(list_node_t));
        list_node->node = node;

        list_node->prve = before->prve;
        list_node->next = before;

        before->prve->next = list_node;
        before->prve = list_node;

        return ++list->size;
    }
    return -1;
}

int list_delete(list_t* list, list_node_t* del_node) 
{
    if (del_node) 
    {
        del_node->prve->next = del_node->next;
        del_node->next->prve = del_node->prve;

        
        
        //deallocate(pool(NULL), del_node, sizeof(list_node_t));

        return --list->size;
    }
    return -1;
}