/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-19 16:06:57
 * @LastEditTime: 2020-06-02 16:51:27
 * @LastEditors: Please set LastEditors
 */
#include <stdlib.h>
#include "set.h"
#include "tv.h"

void initSet(Set* set,int (compare)(tv, tv)) 
{
    cnew(set, list, compare);
}

void uninitSet(Set* set) 
{
    cfree(set, list);
}

int insertSet(Set* set, tv data) 
{
    if (!chas(set, data)) {
        return cpush(set, data);
    }
    return -1;
}
