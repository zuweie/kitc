/*
 * @Description: node
 * @Author: zuweie
 * @Date: 2019-09-03 13:29:23
 * @LastEditTime: 2019-09-10 19:25:01
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
    tv.pointer = v;
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
    return tv.pointer;
}

int compare_int(type_value_t v1, type_value_t v2) 
{

    int vv1 = type_int(v1);
    int vv2 = type_int(v2);
    
    if (vv1 == vv2) return 0;
    else if (vv1 > vv2) return 1;
    else return -1;
}

int compare_float(type_value_t v1, type_value_t v2)
{
    if (type_int(v1) == type_int(v2)) return 0;
    else if (type_float(v1) > type_float(v2)) return 1;
    else return -1;
}

int compare_pointer(type_value_t v1, type_value_t v2){
    void* p1 = type_pointer(v1);
    void* p2 = type_pointer(v2);
    return p1 == p2;
}