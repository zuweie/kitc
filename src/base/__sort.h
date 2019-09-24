/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-24 23:50:36
 * @LastEditTime: 2019-09-25 00:44:22
 * @LastEditors: Please set LastEditors
 */
#ifndef _SORT_H_
#define _SORT_H_
#include "__container.h"
#include "__type_value.h"

int quick_sort(iterator_t, iterator_t, int(*compare)(type_value_t, type_value_t));

#endif