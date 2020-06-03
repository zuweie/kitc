/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 19:09:21
 * @LastEditTime: 2020-06-03 14:11:58
 * @LastEditors: Please set LastEditors
 */
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "con.h"

typedef Container Queue;

#define Queue_init(queue, compare) cinit(queue, list, compare)
#define Queue_free(queue) cfree(queue, list)

// 尾部插入
#define Queue_offer(queue, tv) caddTail(queue, tv)

// 头部输出
#define Queue_poll(queue, rdata) crmFirst(queue, rdata)

#endif