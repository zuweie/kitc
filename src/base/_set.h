/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-19 16:06:51
 * @LastEditTime: 2019-09-20 19:39:18
 * @LastEditors: Please set LastEditors
 */
#ifndef _SET_H_
#define _SET_H_

#include "__list.h"
#include "_container_adapter.h"

typedef struct _set {
    con_adapter_t container;
    list_t engine;
} set_t;

extern void init_set(set_t*,int(*compare)(type_value_t, type_value_t));
extern int set_insert(con_adapter_t*, type_value_t);

#endif