/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 19:09:26
 * @LastEditTime: 2019-09-20 10:37:25
 * @LastEditors: Please set LastEditors
 */
#include "_queue.h"

void init_queue(queue_t* q, container_t* container, int (compare)(type_value_t, type_value_t)) {
    q->container = container;
    q->compare = compare;
}

int en_queue (queue_t* q, type_value_t data) 
{
    return container_insert(q, container_tail(q), data);
}

int de_queue(queue_t* q, type_value_t* v) 
{
    return container_remove(q, container_first(q), v);
}
