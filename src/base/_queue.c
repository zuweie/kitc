/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 19:09:26
 * @LastEditTime: 2019-09-15 03:59:15
 * @LastEditors: Please set LastEditors
 */
#include "_list.h"
#include "_queue.h"

void init_queue(queue_t* q) {
    return init_list(q);
}

int enqueue (queue_t* q, type_value_t data) 
{
    return container_insert(q, container_tail(q), data);
}

int dequeue(queue_t* q, type_value_t* v) 
{
    return container_remove(q, container_first(q), v);
}
