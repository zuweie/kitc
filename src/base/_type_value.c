/*
 * @Description: node
 * @Author: zuweie
 * @Date: 2019-09-03 13:29:23
 * @LastEditTime: 2019-09-10 09:58:21
 * @LastEditors: Please set LastEditors
 */

#include "_type_value.h"

type_value_t int_type(int v) 
{
    type_value_t tv;                                
    type_value_size* pv = (type_value_size*)(&(v));   
    *((type_value_size*)tv.type_value) = *pv;       
    return tv;                                      
}
type_value_t float_type(float v)
{
    type_value_t tv;                                
    type_value_size* pv = (type_value_size*)(&(v));   
    *((type_value_size*)tv.type_value) = *pv;       
    return tv;
}
type_value_t pointer_type(void* v) 
{
    type_value_t tv;
    type_value_size pv = (type_value_size)v;
    *((type_value_size*)tv.type_value) = pv;
    return tv;
}

int type_int(type_value_t tv)
{
    return *((int*)(tv.type_value));
}

float type_float(type_value_t tv) 
{
    return *((float*)(tv.type_value));
}

void* type_pointer(type_value_t tv) 
{
    return (void*)(*((type_value_size*)(tv.type_value)));
}