/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-19 16:06:51
 * @LastEditTime: 2019-09-20 12:34:19
 * @LastEditors: Please set LastEditors
 */
#ifndef _SET_H_
#define _SET_H_

#include "__list.h"

typedef struct _set {
    list_t _engine;
    int (*compare) (type_value_t node, type_value_t find)
} set_t;

extern void init_set(set_t*,int(*compare)(type_value_t, type_value_t));
extern int set_is_member(set_t*, type_value_t);
extern iterator_t set_find(set_t*, type_value_t);
extern int set_insert(set_t*, type_value_t);
extern int set_remove_find(set_t*, type_value_t, type_value_t*);
extern int set_remove_last(set_t*, type_value_t*);

#endif