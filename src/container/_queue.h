/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 19:09:21
 * @LastEditTime: 2019-09-24 12:15:30
 * @LastEditors: Please set LastEditors
 */
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "_con.h"
#include "__list.h"

typedef struct _queue 
{
    con_t container;
    list_t engine;
    
} queue_t;

extern void init_queue(queue_t*, int (*compare)(type_value_t, type_value_t));

// 尾部插入
extern int en_queue(queue_t*, type_value_t);

// 头部输出
extern int de_queue(queue_t*, type_value_t*);

#endif