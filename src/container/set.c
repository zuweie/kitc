/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-19 16:06:57
 * @LastEditTime: 2020-06-04 18:46:45
 * @LastEditors: Please set LastEditors
 */
#include <stdlib.h>
#include "set.h"
#include "tv.h"

int Set_insert(Set* set, tv data) 
{
    if (!Set_has(set, data)) {
        return Set_add(set, data);
    }
    return -1;
}
