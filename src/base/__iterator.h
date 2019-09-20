/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-07 23:21:54
 * @LastEditTime: 2019-09-20 13:01:55
 * @LastEditors: Please set LastEditors
 */
#ifndef _ITERATOR_H_
#define _ITERATOR_H_

#include "__container.h"
#include "__type_value.h"

#define iterator_reference(iter) (iter.reference)
#define iterator_attach(iter) (iter.attach)
#define iterator_dereference(iter) (iter.dereference(iter))
#define iterator_move(iter, step) (iter.move(iter, step))
#define iterator_next(iter) iterator_move(iter, 1)
#define iterator_prev(iter) iterator_move(iter, -1)
#define iterator_equal(iter1, iter2) (iter1.equal(iter1, iter2))
#define iterator_assign(from, to) (from.assign(to, from))
#define iterator_exchange(iter1, itert2) (iter1.exchange(iter1, iter2))
#define iterator_valid(iter) (iter.valid(iter))

typedef struct _iterator iterator_t;
struct _iterator {
    type_value_t (*dereference) (iterator_t);
    iterator_t (*move)(iterator_t, int step);
    int (*valid) (iterator_t);
    int (*equal) (iterator_t t1, iterator_t t2);
    int (*assign) (iterator_t t1, iterator_t t2);
    int (*exchange) (iterator_t t1, iterator_t t2);
    void* reference;
    void* attach;
};

extern iterator_t get_iterator(void* __refer, void* __attach, iterator_t (*__move)(iterator_t, int));

#endif