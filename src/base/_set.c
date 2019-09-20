/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-19 16:06:57
 * @LastEditTime: 2019-09-20 09:19:25
 * @LastEditors: Please set LastEditors
 */
#include <stdlib.h>
#include "_set.h"

void init_set(set_t* set) 
{
    init_list(set);
}

int set_is_member(set_t* set, type_value_t find, int(compare)(type_value_t node, type_value_t find)){
    return container_has(set, find, compare);
}

int set_insert(set_t* set, type_value_t data, int (compare)(type_value_t node, type_value_t find)) 
{
    if (!set_is_member(set, data, compare)) {
        return container_insert_tail(set, data);
    }
    return -1;
}
