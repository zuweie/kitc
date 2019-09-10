/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-07 23:21:54
 * @LastEditTime: 2019-09-10 13:23:45
 * @LastEditors: Please set LastEditors
 */
#ifndef _ITERATOR_H_
#define _ITERATOR_H_

#include "_container.h"
#include "_type_value.h"

#define iterator_reference(iter) (iter.reference)
#define iterator_dereference(iter) (iter.dereference(iter))
#define iterator_next(iter) (iter.next(iter))
#define iterator_prev(iter) (iter.prev((iter)))
#define iterator_equal(iter1, iter2) (iter1.equal(iter1, iter2))
#define iterator_assign(iter1, iter2) (iter1.assign(iter1, iter2))



typedef struct _iterator iterator_t;

struct _iterator {
    type_value_t (*dereference) (iterator_t);
    iterator_t (*next)(iterator_t);
    iterator_t (*prev)(iterator_t);
    int (*equal) (iterator_t t1, iterator_t t2);
    int (*assign) (iterator_t t1, iterator_t t2);
    void* reference;
};

extern inline iterator_t get_iterator(void*, type_value_t (*) (iterator_t), iterator_t (*)(iterator_t), iterator_t (*)(iterator_t));

#endif