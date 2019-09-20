/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-19 16:06:57
 * @LastEditTime: 2019-09-20 19:39:38
 * @LastEditors: Please set LastEditors
 */
#include <stdlib.h>
#include "_set.h"

void init_set(set_t* set,int (compare)(type_value_t, type_value_t)) 
{
    init_list(&set->engine);
    init_adapter(&set->container, &set->engine, compare);
    return;
}

int set_insert(con_adapter_t* con, type_value_t data) 
{
    if (!has(con, data)) {
        return insert_tail(con, data);
    }
    return -1;
}
