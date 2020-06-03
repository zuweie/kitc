/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-19 16:06:51
 * @LastEditTime: 2020-06-03 18:49:58
 * @LastEditors: Please set LastEditors
 */
#ifndef _SET_H_
#define _SET_H_

#include "con.h"

typedef Container Set;

#define Set_init(set, compare) CN_init(set, list, compare)
#define Set_free(set) CN_free(set, list)
#define Set_rm_target(set, target, rdata) CN_rm_target(set, target, rdata)
#define Set_rm_last(set, rdata) CN_rm_last(set, rdata)
#define Set_add(set, data) CN_add_tail(set, data)
#define Set_find(set, find) CN_find(set, find)
int Set_insert(Set*, tv);

#endif