/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-08 00:02:36
 * @LastEditTime: 2019-09-10 13:32:12
 * @LastEditors: Please set LastEditors
 */
#include "_vector.h"
#include "_iterator.h"
#include "_type_value.h"

/** iterator function **/
static iterator_t _get_iter (void* refer);

static type_value_t _dereference (iterator_t it) 
{
    type_value_t* pv = iterator_reference(it);
    return *pv;
}

static iterator_t _next (iterator_t it) 
{
    type_value_t* pv = iterator_reference(it);
    return _get_iter( pv + 1 );
}

static iterator_t _prev (iterator_t it) 
{
    type_value_t* pv = iterator_reference(it);
    return _get_iter( pv - 1 );
}

static iterator_t _get_iter (void* refer) {
    iterator_t it =  get_iterator(refer, _dereference, _next, _prev);
    return it;
}
/** iterator function **/

/** container function **/
static iterator_t _vector_first (container_t* container) 
{
    vector_t* vec = container;
    return _get_iter(vec->_data);
}

static iterator_t _vector_last (container_t* container) 
{
    vector_t* vec = container;
    return _get_iter(vec->_data + vec->_size-1);
}

static iterator_t _vector_find (container_t* container, type_value_t find, int (*compare)(type_value_t, type_value_t)) 
{
    
    iterator_t first = container_first(container);
    iterator_t tail = iterator_next( container_last(container) );
    for(; !iterator_equal(first, tail); first=iterator_next(first)) {
        if (compare(iterator_dereference(first), find) == 0) 
            return first;
    }

    return _get_iter((void*)0);
}

static int _vector_insert (container_t* container, iterator_t pos, type_value_t data) 
{
    
    vector_t* vec = container;

    if (vec->_size < VEC_SIZE) {
        iterator_t last = container_last(container);
        iterator_t pos_prev = iterator_prev(pos);

        // 挪位
        for(; !iterator_equal(last, pos_prev); last = iterator_prev(last)) 
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

static int _vector_remove (container_t* container, iterator_t pos, type_value_t* ret_data) 
{
    vector_t* vec = container;

    if (vec->_size >0) {
        iterator_t last = container_last(container);
        if (ret_data) {
            *ret_data = iterator_dereference(pos);
        }
        // 擦除
        for(; !iterator_equal(pos, last); pos = iterator_next(pos)) {
            iterator_t pos_next = iterator_next(pos);
            iterator_assign(pos_next, pos);
        }
        vec->_size--;
        return 0;
    }
    return -1;
}
/** container **/

void init_vector(vector_t* vector) {
    initialize_container(vector, _vector_first, _vector_last, _vector_find, _vector_insert, _vector_remove);
    vector->_size = 0;
    return;
}