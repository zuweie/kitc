/*
 * @Author: your name
 * @Date: 2020-06-07 12:36:10
 * @LastEditTime: 2020-06-07 13:05:46
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /kitc/src/container/list.h
 */ 

#ifndef _LINK_ARRAY_H_
#define _LINK_ARRAY_H_

#include "cn.h"

typedef Container LinkArray;

#define LinkArr_init(la, compare) CN_init(la, list, compare)
#define LinkArr_free(la) CN_free(la, list)

#define LinkArr_add(la,tv) CN_add_tail(la, tv)

#endif