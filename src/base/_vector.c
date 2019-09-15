/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-08 00:02:36
 * @LastEditTime: 2019-09-15 17:38:49
 * @LastEditors: Please set LastEditors
 */
#include <string.h>
#include "_vector.h"
#include "_iterator.h"
#include "_type_value.h"
#include "_mem_pool.h"

/** iterator function **/
static iterator_t _get_iter (void* refer);

static iterator_t _next (iterator_t it) 
{
    type_value_t* pv = (type_value_t*) iterator_reference(it);
    return _get_iter( pv + 1 );
}

static iterator_t _prev (iterator_t it) 
{
    type_value_t* pv = (type_value_t*) iterator_reference(it);
    return _get_iter( pv - 1 );
}

static iterator_t _get_iter (void* refer) {
    return get_iterator(refer, 0, _next, _prev);
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
    return _get_iter(vec->_data + vec->_size -1 );
}

static iterator_t _vector_find (container_t* container, type_value_t find, int (*compare)(type_value_t, type_value_t)) 
{
    
    iterator_t first = container_first(container);
    iterator_t tail = iterator_next( container_last(container) );
    for(; !iterator_equal(first, tail); first=iterator_next(first)) {
        if (compare(iterator_dereference(first), find) == 0) 
            return first;
    }
    // 返回空指针。
    return _get_iter((void*)0);
}

static int _vector_insert (container_t* container, iterator_t pos, type_value_t data) 
{
    if (iterator_valid(pos)) {
        
        vector_t *vec = container;

        // 检测一下是否满水？
        if (vec->_size >= vec->_capacity){
            // 注水
            unsigned int require_size = vec->_size + ALLOC_CHUNK_SIZE;
            type_value_t *new_block = allocate(pool(0), require_size);

            if (new_block){
                // copy 旧数据到新的内存
                memcpy(new_block, vec->_data, vec->_size * sizeof(type_value_t));
                // 释放旧的内存
                deallocate(pool(0), vec->_data);
                // 把新内存挂上去
                vec->_data = new_block;
                // 容量值变大。
                vec->_capacity += ALLOC_CHUNK_SIZE;
            }else{
                return -1;
            }
        }

        // 继续做插入动作。
        iterator_t last = container_last(container);
        iterator_t pos_prev = iterator_prev(pos);

        // 挪位
        for (; !iterator_equal(last, pos_prev); last = iterator_prev(last)){
            iterator_t next = iterator_next(last);
            iterator_assign(last, next);
        }
        // 插入
        type_value_t *pt = iterator_reference(pos);
        *pt = data;

        vec->_size++;
        return 0;
    }
    return -;
}

static int _vector_remove (container_t* container, iterator_t pos, type_value_t* rdata) 
{
    if (iterator_valid(pos)){
        
        vector_t *vec = container;
        type_value_t *pv = iterator_reference(pos);
        type_value_t *head = iterator_reference(container_head(vec));
        type_value_t *tail = iterator_reference(container_tail(vec));
        iterator_t last = container_last(container);

        if (rdata)
        {
            *rdata = iterator_dereference(pos);
        }

        // 擦除
        for (; !iterator_equal(pos, last); pos = iterator_next(pos))
        {
            iterator_t pos_next = iterator_next(pos);
            iterator_assign(pos_next, pos);
        }
        vec->_size--;
        return 0;
    }
    return -1;
}

static unsigned int _vector_size (container_t* container) 
{
    return ((vector_t*)container)->_size;
}
/** container **/

void init_vector(vector_t* vector) {
    initialize_container(vector, _vector_first, _vector_last, _vector_find, _vector_insert, _vector_remove, _vector_size);
    vector->_size = 0;
    vector->_capacity = 0;
    return;
}