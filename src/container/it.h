/*
 * @Author: your name
 * @Date: 2020-05-30 08:54:21
 * @LastEditTime: 2020-06-03 15:09:55
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /kitc/src/container/iterator.h
 */ 

#ifndef _IT_H_
#define _IT_H_
#include "__iterator.h"
typedef iterator_t it;
/* iterator_t function */
#define iref(iter) iterator_reference(iter)
#define idref(iter) iterator_dereference(iter)
#define imove(it) iterator_move(iter, step)
#define inext(iter) iterator_next(iter)
#define iprev(iter) iterator_prev(iter)
#define iequal(iter1, iter2) iterator_equal(iter1, iter2)
#define iassign(from, to) iterator_assign(from, to)
#define iexchange(iter1, iter2) iterator_exchange(iter1, itert2)
//#define ivalid(iter) iterator_valid(iter)
#define ivalid(it) _ivalid(it)
static inline 
int _ivalid(it iter) 
{
    it pos = iter;
    return iterator_valid(pos);
}
#endif