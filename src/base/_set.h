/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-19 16:06:51
 * @LastEditTime: 2019-09-20 09:17:48
 * @LastEditors: Please set LastEditors
 */
#ifndef _SET_H_
#define _SET_H_

#include "_list.h"
#include "_type_value.h"

typedef list_t set_t;

extern void init_set(set_t*);
extern int set_is_member(set_t*, type_value_t, int(compare)(type_value_t node, type_value_t find));
extern int set_insert(set_t*, type_value_t, int (compare)(type_value_t, type_value_t));

#endif