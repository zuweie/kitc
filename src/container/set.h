/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-19 16:06:51
 * @LastEditTime: 2020-06-02 15:57:39
 * @LastEditors: Please set LastEditors
 */
#ifndef _SET_H_
#define _SET_H_

#include "con.h"

typedef Container Set;

void initSet(Set*,int(*compare)(tv, tv));
void uninitSet();
int insertSet(Set*, tv);

#endif