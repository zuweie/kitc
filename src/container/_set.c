/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-19 16:06:57
 * @LastEditTime: 2019-09-21 01:00:33
 * @LastEditors: Please set LastEditors
 */
#include <stdlib.h>
#include "_set.h"

void init_set(set_t* set,int (compare)(type_value_t, type_value_t)) 
{
    init_list(&set->engine);
    set->container._container = &set->engine;
    set->container._compare   = compare;
    return;
}

int set_insert(con_t* con, type_value_t data) 
{
    if (!con_has(con, data)) {
        return con_ins_tail(con, data);
    }
    return -1;
}
