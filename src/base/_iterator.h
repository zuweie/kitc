/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-07 23:21:54
 * @LastEditTime: 2019-09-08 18:32:03
 * @LastEditors: Please set LastEditors
 */
#ifndef _ITERATOR_H_
#define _ITERATOR_H_

#include "_container.h"
#include "_node.h"

#define dereference(iter) (&iter)->dereference(iter)
#define next(iter) (&iter)->next(iter)
#define forward(iter) (&iter)->forward(iter)
#define has_next(iter) (&iter)->has_next(iter)
#define compare(iter1, iter2) (&iter)->compare(iter1, iter2)

#define initialize_iterator (iter, dereference, next, forward, has_next, compare) do { \
    iter->dereference = dereference;    \
    iter->next = next;                  \
    iter->forward = forward;            \
    iter->has_next = has_next;          \
    iter->compare = compare;            \
} while(0)

typedef struct _iterator {
    void* (*dereference)(struct _iterator);
    struct _iterator (*next)(struct _iteractor);
    struct _iterator (*forward)(struct _iteractor);
    unsigned char (*has_next)(struct _iteractor);
    int (*compare)(struct _iterator, struct _iterator);
} iterator_t;

#endif