/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-19 16:06:51
 * @LastEditTime: 2019-09-21 00:38:07
 * @LastEditors: Please set LastEditors
 */
#ifndef _SET_H_
#define _SET_H_

#include "__list.h"
#include "_con.h"

typedef struct _set {
    con_t container;
    list_t engine;
} set_t;

extern void init_set(set_t*,int(*compare)(type_value_t, type_value_t));
extern int set_insert(con_t*, type_value_t);

#endif