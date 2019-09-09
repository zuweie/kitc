/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-07 23:21:54
 * @LastEditTime: 2019-09-09 23:21:17
 * @LastEditors: Please set LastEditors
 */
#ifndef _ITERATOR_H_
#define _ITERATOR_H_

#include "_container.h"
#include "_node.h"

//typedef struct _iterator iterator_t;
#define iterator_reference(iter) ((&iter)->reference)
#define iterator_next(iter) (&iter)->next(iter)
#define iterator_prev(iter) (&iter)->prev(iter)
#define iterator_equal(iter1, iter2) (&iter1)->equal(iter1, iter2)
#define iterator_assign(iter1, iter2) (&iter1)->assign(iter1, iter2)

#define initialize_iterator(iter, __refer, __next, __prev, __equal, __assign) do { \
    (&iter)->reference   = (__refer);          \
    (&iter)->next        = (__next);           \
    (&iter)->prev        = (__prev);           \
    (&iter)->equal       = (__equal);          \
    (&iter)->assign      = (__assign);         \
} while(0)

typedef struct _iterator iterator_t;

struct _iterator {
    iterator_t (*next)(iterator_t);
    iterator_t (*prev)(iterator_t);
    int (*equal) (iterator_t t1, iterator_t t2);
    int (*assign) (iterator_t t1, iterator_t t2);
    void* reference;
};

#endif