/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 19:09:26
 * @LastEditTime: 2020-06-02 16:20:41
 * @LastEditors: Please set LastEditors
 */
#include "queue.h"
#include "tv.h"

void initQueue(Queue* q, int (*compare)(tv, tv)) {
    cnew(q, list, compare);
}
void uninitQueue (Queue* q) {
   cfree(q, list);
}
int enQueue (Queue* q, tv data) 
{
    return cadd(q,data);
}

int deQueue(Queue* q, tv* rdata) 
{
    return cpop(q, rdata);
}
