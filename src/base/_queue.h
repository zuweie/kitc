/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 19:09:21
 * @LastEditTime: 2019-09-20 09:19:59
 * @LastEditors: Please set LastEditors
 */
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "_list.h"

typedef list_t queue_t;

void init_queue(queue_t*);

// 尾部插入
extern int en_queue(queue_t*, type_value_t);

// 头部输出
extern int de_queue(queue_t*, type_value_t*);

#endif