/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-19 16:06:51
 * @LastEditTime: 2020-06-03 13:46:12
 * @LastEditors: Please set LastEditors
 */
#ifndef _SET_H_
#define _SET_H_

#include "con.h"

typedef Container Set;

#define Set_init(set, compare) cinit(set, list, compare)
#define Set_free(set) cfree(set, list)
#define Set_rmTarget(set, target, rdata) crmFind(set, target, rdata)
#define Set_rmLast(set, rdata) crmLast(set, rdata)
int Set_insert(Set*, tv);

#endif