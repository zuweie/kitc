/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-03 13:29:13
 * @LastEditTime: 2019-09-25 08:46:09
 * @LastEditors: Please set LastEditors
 */

#ifndef _TYPE_VALUE_H_
#define _TYPE_VALUE_H_

#define set_type_val(t, v) (((*((v_type*)t.type_value))=(*((v_type*)(&(v)))))?t:t)
#define set_type_ptr(t, p) ((t.pointer=p)?t:t)

#define type_int(t) (*((int*)t.type_value))
#define type_float(t) (*((float*)t.type_value))
#define type_pointer(t) (t.pointer)

#define int_type(v) _int_type(v)
#define float_type(v) _flt_type(v)
#define pointer_type(v) _ptr_type(v)

#define cmp_int(t1, t2) ((type_int(t1)==type_int(t2))?0:((type_int(t1)>type_int(t2)))?1:-1)
#define cmp_flt(t1, t2) ((type_int(t1)==type_int(t2))?0:((type_float(t1)>type_float(t2))?1:-1))
#define cmp_ptr(t1, t2) (!(type_pointer(t1)==type_pointer(t2)))

typedef unsigned int v_type;
typedef union _type_value
{
   void* pointer;
   unsigned char type_value[sizeof(v_type)];
} type_value_t;

static inline 
type_value_t _int_type(int v)
{
   type_value_t tv;                                
   return set_type_val(tv, v);
}

static inline 
type_value_t _flt_type(float v)
{
   type_value_t tv;
   return set_type_val(tv, v);
}

static inline 
type_value_t _ptr_type(void* p)
{
   type_value_t tv;
   return set_type_ptr(tv, p);
}


static inline 
int compare_int(type_value_t t1, type_value_t t2) 
{
   return cmp_int(t1, t2);
}

static inline 
int compare_float(type_value_t t1, type_value_t t2) 
{
   return cmp_flt(t1, t2);
}

static inline 
int compare_pointer(type_value_t t1, type_value_t t2) 
{
   return cmp_ptr(t1, t2);
}

#endif