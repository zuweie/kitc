/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-19 16:06:57
 * @LastEditTime: 2019-09-20 12:33:46
 * @LastEditors: Please set LastEditors
 */
#include <stdlib.h>
#include "__container.h"
#include "_set.h"

void init_set(set_t* set,int (compare)(type_value_t, type_value_t)) 
{
    init_list(&set->_engine);
    set->compare = compare;
}

int set_is_member(set_t* set, type_value_t find){
    return container_has(&set->_engine, find, set->compare);
}

iterator_t set_find(set_t* set, type_value_t find) {
    return container_find(&set->_engine, find, set->compare);
}

int set_insert(set_t* set, type_value_t data) 
{
    if (!set_is_member(set, data)) {
        return container_insert_tail(&set->_engine, data);
    }
    return -1;
}

int set_remove_find(set_t* set, type_value_t find, type_value_t* rdata) 
{
    return container_remove_find(&set->_engine, find, rdata, set->compare);
}

int set_remove_last (set_t* set, type_value_t* rdata) {
    return container_remove_last(&set->_engine, rdata);
}
