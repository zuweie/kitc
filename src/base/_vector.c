/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-08 00:02:36
 * @LastEditTime: 2019-09-09 23:20:24
 * @LastEditors: Please set LastEditors
 */
#include "_vector.h"
#include "_iterator.h"

/** iterator function **/
static iterator_t _next (iterator_t it) 
{
    node_t* pnode = iterator_reference(it);
    return get_iter( pnode + 1 );
}

static iterator_t _prev (iterator_t it) 
{
    node_t* pnode = iterator_reference(it);
    return get_iter( pnode - 1 );
}

static int _equal(iterator_t t1, iterator_t t2) 
{
    return iterator_reference(t1) = iterator_reference(t2);
}

static int _assign(iterator_t t1, iterator_t t2) 
{
    node_t* p1 = iterator_reference(t1);
    node_t* p2 = iterator_reference(t2);
    *p2 = *p1;
    return 0;
}

static iterator_t get_iter (void* refer) {
    iterator_t it;
    initialize_iterator(it, refer, _next, _prev, _equal, _assign);
    return it;
}

static iterator_t vector_first (container_t* container) 
{
    vector_t* vec = container;
    return get_iter(&vec->_data[0]);
}

static iterator_t vector_last (container_t* container) 
{
    vector_t* vec = container;
    return get_iter(vec->_data + vec->_size-1);
}

static iterator_t vector_find (container_t* container, void* data, int (*compare)(void*, void*)) 
{
    
    iterator_t first = container_first(container);
    iterator_t last = container_last(container);
    for(;iterator_equal(first, last);

        first = iterator_next(first)) {
        if (compare(iterator_reference(first), data) == 0) 
        {
            return first;
        }
    }

    return get_iter((void*)0);
}

static int vector_insert (container_t* container, iterator_t position, void* data) 
{
    
    vector_t* vec = container;

    if (vec->_size < VEC_SIZE) {
        iterator_t last = container_last(container);
        iterator_t insert_pos_prev = iterator_prev(position);

        // 挪位
        for(; iterator_equal(last, insert_pos_prev) == 0; last = iterator_prev(last)) 
        {
            iterator_t next = iterator_next(last);
            iterator_assign(last, next);
        }
        // 插入
        node_t* pnode = iterator_reference(last);
        *pnode = *((node_t*)data);
        vec->_size++;
        return 0;
    }
    return -1;
}

static int vector_remove (container_t* container, iterator_t position) 
{
    vector_t* vec = container;

    if (vec->_size >0) {
        iterator_t last = container_last(container);

        for(; iterator_equal(position, last); position = iterator_next(position)) {
            iterator_t rm_next = iterator_next(position);
            iterator_assign(rm_next, position);
        }
        vec->_size--;
        return 0;
    }
    return -1;
}

extern void init_vector(vector_t* vector) {
    initialize_container(vector, vector_first, vector_last, vector_find, vector_insert, vector_remove);
    return vector;
}