/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 19:09:26
 * @LastEditTime: 2019-09-21 02:45:43
 * @LastEditors: Please set LastEditors
 */
#include "_queue.h"

void init_queue(queue_t* q, int (*compare)(type_value_t, type_value_t)) {
    init_list(&q->engine);

    q->container._container = &q->engine;
    q->container._compare   = compare;
}

int en_queue (queue_t* q, type_value_t data) 
{
    return con_ins_tail(q,data);
}

int de_queue(queue_t* q, type_value_t* v) 
{
    return con_rm_first(q, v);
}
