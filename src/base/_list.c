/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-03 15:07:45
 * @LastEditTime: 2019-09-17 13:41:37
 * @LastEditors: Please set LastEditors
 */

#include <stdlib.h>

#include "_list.h"
#include "_type_value.h"
#include "_iterator.h"
#include "_container.h"
#include "_mem_pool.h"

/** iter function **/
static iterator_t _get_iter (void* refer);

// static type_value_t _dereference(iterator_t it) 
// {
//     list_node_t* pnode = iterator_reference(it);
//     return pnode->data;
// }

static iterator_t _next (iterator_t it) 
{
    list_node_t* pnode = iterator_reference(it);
    return _get_iter(pnode->next);
}

static iterator_t _prev (iterator_t it)
{
    list_node_t* pnode = iterator_reference(it);
    return _get_iter(pnode->prev);
}

static iterator_t _get_iter(void *refer) 
{
    return get_iterator(refer, 0, _next, _prev);
}
/** iter function **/

/** container function **/

static iterator_t _list_first (container_t* container)
{
    list_t* plist = container;
    return _get_iter(list_first(plist));
}

static iterator_t _list_last (container_t* container)
{
    list_t* plist = container;
    return _get_iter(list_last(plist));
}

static iterator_t _list_search (container_t* container, iterator_t offset, type_value_t find, int(compare)(type_value_t data1, type_value_t data2))
{
    iterator_t first = offset;
    iterator_t tail  = container_tail(container);
    for(;iterator_equal(first, tail); first = iterator_next(first)) {
        if (compare(iterator_dereference(first), find) == 0) {
            return first;
        }
    }
    // 找不到返回空指针
    return _get_iter((void*)0);
}

static int _list_insert(container_t* container, iterator_t pos, type_value_t data)
{
    if (iterator_valid(pos)){
        
        list_node_t *pnode = iterator_reference(pos);
        list_node_t *pnew = allocate(pool(0), sizeof(list_node_t));
        // 赋值 和 插入

        pnew->data = data;
        pnew->prev = pnode->prev;
        pnew->next = pnode;

        pnode->prev->next = pnew;
        pnode->prev = pnew;

        list_t *plist = container;
        plist->_size++;
        return 0;
    }

    return -1;

}

static int _list_remove(container_t* container, iterator_t pos, type_value_t* rdata)
{
    // 删除
    if (iterator_valid(pos)){

        list_t* list = container;
        list_node_t* pnode = iterator_reference(pos);
        
        pnode->prev->next = pnode->next;
        pnode->next->prev = pnode->prev;

        if (rdata) {
            *rdata = iterator_dereference(pos);
        }
        
        // 回收
        deallocate(pool(0), pnode);
        list->_size--;
        return 0;
    }

    return -1;
}

static unsigned int _list_size(container_t* container) 
{
    return ((list_t*)container)->_size;
}

void init_list(list_t* list) {
    
    initialize_container(list, _list_first, _list_last, _list_search, _list_insert, _list_remove, _list_size);
    list_first(list) = list_head(list);
    list_last(list) = list_tail(list);
    list->_size = 0;
    list->_sentinel.data = int_type(111);      
    return;
}

