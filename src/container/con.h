/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-20 18:51:11
 * @LastEditTime: 2020-06-02 16:21:09
 * @LastEditors: Please set LastEditors
 */
#ifndef _CON_H_
#define _CON_H_
#include "__container.h"
#include "it.h"


/* container function */
#define cc(con) (((Container*)con)->_container)
#define ccmp(con) (((Container*)con)->_compare)
//#define setCmp(con, cmp) ((Cmp(con)=cmp)?con:con)

#define cfirst(con) container_first(cc(con))
#define clast(con) container_last(cc(con))
#define chead(con) container_head(cc(con))
#define ctail(con) container_tail(cc(con))

#define csearch(con, offset, find) container_search(cc(con), offset, find, ccmp(con))
#define cfind(con, find) container_find(cc(con),find, ccmp(con))

#define cinsert(con, it, data) container_insert(cc(con), it, data)
#define cadd(con, data) cinsert(cc(con), cfirst(cc(con)), data)
#define cpush(con, data) cinsert(cc(con), ctail(cc(con)), data)

#define crm(con, it, rdata) container_remove(cc(con), it, rdata)
#define cpoll(con, rdata) crm(cc(con), cfirst(cc(con)), rdata)
#define cpop(con, rdata) crm(cc(con), clast(cc(con)), rdata)

#define chas(con, find) container_has(cc(con), find, ccmp(con))
#define csize(con) container_size(cc(con))
#define csort(con, cmp) container_sort(cc(con), cmp)

#define cnew(con, label, cmp) do {       \
    cc(con) = container_create(lable);   \
    ccmp(con) = cmp;                     \
}while(0)

#define cfree(con, label) do {         \
    container_destroy(lable, cc(con)); \
    ccmp(con) = NULL;                  \
}while(0)

// 遍历容器，
#define con_travel(con, func) do {        \
    for(it first = cfirst(con);      \
        !iequal(first, ctail(con));  \
        first = inext(first) ) func(first) ; \
}while(0)


typedef struct _con{
    
    container_t* _container;
    int (*_compare)(type_value_t, type_value_t);

} Container;


#endif