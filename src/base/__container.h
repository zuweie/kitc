/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-07 23:21:46
 * @LastEditTime: 2019-09-23 15:17:15
 * @LastEditors: Please set LastEditors
 */
#ifndef _CONTAINER_H_
#define _CONTAINER_H_


#include "__type_value.h"
#include "__iterator.h"

// 容器位置
#define container_first(container) (((container_t*)(container))->first((container_t*)(container)))
#define container_last(container) (((container_t*)(container))->last((container_t*)(container)))
#define container_head(container) iterator_prev(container_first(container))
#define container_tail(container) iterator_next(container_last(container))

// 容器搜索
#define container_search(container, offset, find, compare) (((container_t*)(container))->search(((container_t*)(container)), offset, find, compare))
#define container_find(container, find, compare) container_search(container, container_first(container), find, compare)

// 容器插入
#define container_insert(container, iter, data) (((container_t*)(container))->insert(((container_t*)(container)), iter, data))
#define container_insert_find(container, find, data, compare) container_insert(container, container_find(container, find, compare), data)
#define container_insert_first(container, data) container_insert(container, container_first(container), data)
#define container_insert_tail(container, data) container_insert(container, container_tail(container), data)

// 容器移除
#define container_remove(container, iter, rdata) (((container_t*)(container))->remove(((container_t*)(container)), iter, rdata))
#define container_remove_find(container, find, rdata, compare) container_remove(container, container_find(container, find, compare), rdata) 
#define container_remove_first(container, rdata) container_remove(container, container_first(container), rdata)
#define container_remove_last(container, rdata) container_remove(container, container_last(container), rdata)

// 容器测试
#define container_has(container, find, compare) (!iterator_is_boundary(container_find(container, find, compare)))

// 两个容器合并。
#define container_merge(container_1, container2) do { \
    container_t* c1 = (container_t*)(container_1);    \
    container_t* c2 = (container_t*)(container_2);    \
    iterator_t first2  = container_first(c2);         \
    iterator_t tail2   = container_tail(c2);          \
    for(; !iterator_equal(first2, tail2); first2 = iterator_next(first2)) { \
        type_value_t data = iterator_dereference(first2);                   \
        container_insert_tail(c1, data);                                    \
    }                                                                       \
}while(0)

#define container_size(container) (((container_t*)(container))->size(container))

#define initialize_container(container, __first, __last, __search, __insert, __remove, __size) do { \
    ((container_t*)(container))->first  = (__first);                                        \
    ((container_t*)(container))->last   = (__last);                                         \
    ((container_t*)(container))->search = (__search);                                       \
    ((container_t*)(container))->insert = (__insert);                                       \
    ((container_t*)(container))->remove = (__remove);                                       \
    ((container_t*)(container))->size   = (__size);                                         \
} while (0)

typedef struct _container container_t;
typedef struct _iterator iterator_t;
struct _container {
    iterator_t (*first) (container_t* container);   
    iterator_t (*last) (container_t * container);   
    iterator_t (*search) (container_t* container, iterator_t offset, type_value_t find, int (*compare)(type_value_t, type_value_t)); 
    int (*insert) (container_t* container, iterator_t iter, type_value_t data); 
    int (*remove) (container_t* container, iterator_t iter, type_value_t* rdata); 
    unsigned int (*size) (container_t*);
};

#endif