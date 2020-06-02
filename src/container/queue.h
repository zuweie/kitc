/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 19:09:21
 * @LastEditTime: 2020-06-02 15:59:53
 * @LastEditors: Please set LastEditors
 */
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "con.h"
#include "tv.h"

typedef Container Queue;

void initQueue(Queue*, int (*compare)(tv, tv));
void uninitQueue(Queue*);

// 尾部插入
int enQueue(Queue*, tv);

// 头部输出
int deQueue(Queue*, tv*);

#endif