/*
 * @Author: your name
 * @Date: 2020-05-30 08:54:21
 * @LastEditTime: 2020-06-03 15:39:01
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /kitc/src/container/iterator.h
 */ 

#ifndef _IT_H_
#define _IT_H_
#include "__iterator.h"
typedef iterator_t it;
/* iterator_t function */
#define IT_ref(iter) iterator_reference(iter)
#define IT_dref(iter) iterator_dereference(iter)
#define IT_move(it) iterator_move(iter, step)
#define IT_next(iter) iterator_next(iter)
#define IT_prev(iter) iterator_prev(iter)
#define IT_equal(iter1, iter2) iterator_equal(iter1, iter2)
#define IT_assign(from, to) iterator_assign(from, to)
#define IT_exchange(iter1, iter2) iterator_exchange(iter1, itert2)
//#define ivalid(iter) iterator_valid(iter)
#define IT_valid(it) _ivalid(it)
static inline 
int _ivalid(it iter) 
{
    it pos = iter;
    return iterator_valid(pos);
}
#endif