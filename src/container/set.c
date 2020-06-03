/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-19 16:06:57
 * @LastEditTime: 2020-06-03 14:01:18
 * @LastEditors: Please set LastEditors
 */
#include <stdlib.h>
#include "set.h"
#include "tv.h"

int Set_insert(Set* set, tv data) 
{
    // 保证只有一个 data
    if (!ivalid(cfind(set, data))) {
        return caddFirst(set, data);
    }
    return -1;
}
