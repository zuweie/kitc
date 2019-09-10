/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-08 00:02:36
 * @LastEditTime: 2019-09-10 11:10:31
 * @LastEditors: Please set LastEditors
 */
#include "_vector.h"
#include "_iterator.h"
#include "_type_value.h"

/** iterator function **/
static iterator_t get_iter (void* refer);

static type_value_t _dereference (iterator_t it) 
{
    type_value_t* pv = iterator_reference(it);
    return *pv;
}

static iterator_t _next (iterator_t it) 
{
    type_value_t* pv = iterator_reference(it);
    return get_iter( pv + 1 );
}

static iterator_t _prev (iterator_t it) 
{
    type_value_t* pv = iterator_reference(it);
    return get_iter( pv - 1 );
}

static iterator_t get_iter (void* refer) {
    iterator_t it =  get_iterator(refer, _dereference, _next, _prev);
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

static int vector_insert (container_t* container, iterator_t position, type_value_t data) 
{
    
    vector_t* vec = container;

    if (vec->_size < VEC_SIZE) {
        iterator_t last = container_last(container);
        iterator_t insert_pos_prev = iterator_prev(position);

        // 挪位
        for(; !iterator_equal(last, insert_pos_prev); last = iterator_prev(last)) 
        {
            iterator_t next = iterator_next(last);
            iterator_assign(last, next);
        }
        // 插入
        type_value_t* pt = iterator_reference(last);
        *pt = data;

        vec->_size++;
        return 0;
    }
    return -1;
}

static int vector_remove (container_t* container, iterator_t position, type_value_t* ret_data) 
{
    vector_t* vec = container;

    if (vec->_size >0) {
        iterator_t last = container_last(container);
        if (ret_data) {
            *ret_data = iterator_dereference(position);
        }
        // 擦除
        for(; !iterator_equal(position, last); position = iterator_next(position)) {
            iterator_t rm_next = iterator_next(position);
            iterator_assign(rm_next, position);
        }
        vec->_size--;
        return 0;
    }
    return -1;
}

void init_vector(vector_t* vector) {
    initialize_container(vector, vector_first, vector_last, vector_find, vector_insert, vector_remove);
    vector->_size = 0;
    return;
}