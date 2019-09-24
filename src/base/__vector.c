/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-08 00:02:36
 * @LastEditTime: 2019-09-24 11:01:00
 * @LastEditors: Please set LastEditors
 */
#include <string.h>
#include "__vector.h"
#include "__iterator.h"
#include "__type_value.h"
#include "_mem_pool.h"

/** iterator function **/
static iterator_t _get_iter (void* refer, void* container);

static iterator_t _move (iterator_t it, int step) 
{
    type_value_t* pv = iterator_reference(it);

    //return _get_iter((pv + step), iterator_container(it));
    return iterator_set_reference(it, (pv+step));
}

static iterator_t _get_iter (void* refer, void* vec) {
    return get_iterator(refer, vec, _move);
}
/** iterator function **/

/** container function **/
static iterator_t _vector_first (container_t* container) 
{
    vector_t* vec = container;
    return _get_iter(vec->_data, vec);
}

static iterator_t _vector_last (container_t* container) 
{
    vector_t* vec = container;
    return _get_iter((vec->_data + vec->_size -1), vec);
}

static iterator_t _vector_search (container_t* container, iterator_t offset, type_value_t find, int (*compare)(type_value_t, type_value_t)) 
{
    
    iterator_t first = offset;
    iterator_t tail = container_tail(container);

    for(; !iterator_equal(first, tail); first=iterator_next(first)) {
        if (compare(iterator_dereference(first), find) == 0) return first;
    }
    // 返回边界的指针
    return first;
}

static int _vector_insert (container_t* container, iterator_t it, type_value_t data) 
{
    vector_t *vec = container;

    // 检测一下是否满水？
    if (vec->_size >= vec->_capacity){
        // 注水
        unsigned int require_size = vec->_size + VEC_ALLOC_CHUNK_SIZE;
        type_value_t *new_block = allocate(pool(0), require_size * sizeof(type_value_t));

        if (new_block == NULL) {
            return -1;
        }
        // 如果整个块要是重新malloc的，那么要重新计算it的位置。 
        // 隐藏的bug：地址的差值可能会超过 long 的最大值。
        long offset = ((char*)iterator_reference(it)) - ((char*)iterator_reference(container_head(vec)));
        // copy 旧数据到新的内存
        memcpy(new_block, vec->_data, vec->_size * sizeof(type_value_t));
        // 释放旧的内存
        deallocate(pool(0), vec->_data);
        // 把新内存挂上去
        vec->_data = new_block;
        // 容量值变大。
        vec->_capacity += VEC_ALLOC_CHUNK_SIZE;

        // 更新it的refer。
        void *new_refer = ((char *)iterator_reference(container_head(vec))) + offset;
        iterator_set_reference(it, new_refer);
    }

    // 继续做插入动作。
    iterator_t last = container_last(container);
    iterator_t it_prev = iterator_prev(it);

    // 挪位
    for (; !iterator_equal(last, it_prev); last = iterator_prev(last)){
        iterator_t next = iterator_next(last);
        iterator_assign(next, last);
    }
    // 插入
    type_value_t *pt = iterator_reference(it);
    *pt = data;
    vec->_size++;
    return 0;
}

static int _vector_remove (container_t* container, iterator_t it, type_value_t* rdata) 
{
    if (!iterator_is_boundary(it)){
        
        vector_t *vec = container;

        if (rdata){
            *rdata = iterator_dereference(it);
        }

        // 擦除
        for (it; !iterator_equal(it, container_last(vec)); it = iterator_next(it)){
            iterator_t it_next = iterator_next(it);
            iterator_assign(it, it_next);
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
    
    initialize_container(vector, _vector_first, _vector_last, _vector_search, _vector_insert, _vector_remove, _vector_size);
    vector->_size = 0;
    vector->_capacity = VEC_ALLOC_CHUNK_SIZE;
    // 先给水池注点水。
    vector->_data = allocate(pool(0), VEC_ALLOC_CHUNK_SIZE*sizeof(type_value_t));
    
    return;
}