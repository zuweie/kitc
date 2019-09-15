/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-07 23:21:54
 * @LastEditTime: 2019-09-15 17:35:44
 * @LastEditors: Please set LastEditors
 */
#ifndef _ITERATOR_H_
#define _ITERATOR_H_

#include "_container.h"
#include "_type_value.h"

#define iterator_reference(iter) (iter.reference)
#define iterator_attach(iter) (iter.attach)
#define iterator_dereference(iter) (iter.dereference(iter))
#define iterator_next(iter) (iter.next(iter))
#define iterator_prev(iter) (iter.prev((iter)))
#define iterator_equal(iter1, iter2) (iter1.equal(iter1, iter2))
#define iterator_assign(from, to) (from.assign(to, from))
#define iterator_exchange(iter1, itert2) (iter1.exchange(iter1, iter2))
#define iterator_valid(iter) (iter.valid(iter))

typedef struct _iterator iterator_t;
struct _iterator {
    type_value_t (*dereference) (iterator_t);
    iterator_t (*next)(iterator_t);
    iterator_t (*prev)(iterator_t);
    int (*valid) (iterator_t);
    int (*equal) (iterator_t t1, iterator_t t2);
    int (*assign) (iterator_t t1, iterator_t t2);
    int (*exchange) (iterator_t t1, iterator_t t2);
    void* reference;
    void* attach;
};

extern iterator_t get_iterator(void* __refer, void* __attach, iterator_t (*__next)(iterator_t), iterator_t (*__prev)(iterator_t));

#endif