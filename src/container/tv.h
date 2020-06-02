/*
 * @Author: your name
 * @Date: 2020-06-02 06:50:22
 * @LastEditTime: 2020-06-02 07:20:10
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /kitc/src/container/tv.h
 */ 

#ifndef _TV_H_
#define _TV_H_

#include "__type_value.h"

typedef type_value_t tv;

#define ty(t) type_int(t)
#define tyf(t) type_float(t)
#define tyd(t) type_double(t)
#define typ(t) type_pointer(t)

#define ity(v) int_type(v)
#define fty(v) float_type(v)
#define dty(v) double_type(v)
#define pty(v) pointer_type(v)

#define cmpi(tv1, tv2) compare_int(tv1, tv2)
#define cmpf(tv1, tv2) compare_float(tv1, tv2)
#define cmpd(tv1, tv2) compare_double(tv1, tv2)
#define cmpp(tv1, tv2) compare_pointer(tv1, tv2)

#endif