/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 19:09:21
 * @LastEditTime: 2019-09-20 20:27:10
 * @LastEditors: Please set LastEditors
 */
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "__container.h"

typedef struct _queue 
{
    container_t* container;
    int (*compare) (type_value_t, type_value_t);
} queue_t;

extern void init_queue(queue_t*, container_t*, int (*compare)(type_value_t, type_value_t));

// 尾部插入
extern int en_queue(queue_t*, type_value_t);

// 头部输出
extern int de_queue(queue_t*, type_value_t*);

#endif