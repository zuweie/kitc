/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-20 18:51:11
 * @LastEditTime: 2020-06-03 15:09:02
 * @LastEditors: Please set LastEditors
 */
#ifndef _CON_H_
#define _CON_H_
#include "__container.h"
#include "it.h"
#include "tv.h"

/* container function */
#define cc(con) (((Container*)con)->_container)
#define ccmp(con) (((Container*)con)->_compare)
//#define setCmp(con, cmp) ((Cmp(con)=cmp)?con:con)

#define cfirst(con) container_first(cc(con))
#define clast(con) container_last(cc(con))
#define chead(con) container_head(cc(con))
#define ctail(con) container_tail(cc(con))

#define csearch(con,offset,find) container_search(cc(con), offset, find, ccmp(con))
#define cfind(con,find) csearch(cc(con), cfirst(cc(con)), find)

#define cinsert(con, it, data) container_insert(cc(con), it, data)
// 头部插入
#define caddFirst(con, data) cinsert(cc(con), cfirst(cc(con)), data)
// 尾部插入
#define caddTail(con, data) cinsert(cc(con), ctail(cc(con)), data)

#define cremove(con, it, rdata) container_remove(cc(con), it, rdata)
// 头部移除
#define crmFirst(con, rdata) cremove(cc(con), cfirst(cc(con)), rdata)
// 尾部移除
#define crmLast(con, rdata) cremove(cc(con), clast(cc(con)), rdata)

//#define chas(con, find) container_has(cc(con), find, ccmp(con))
#define csize(con) container_size(cc(con))
#define csort(con, cmp) container_sort(cc(con), cmp)

#define crmFind(con, find, ret) _crmfind(con, find, ret)
#define caddFind(con, find, data) _caddfind(con, find, data)

#define cinit(con, label, cmp) do {       \
    cc(con) = container_create(label);   \
    ccmp(con) = cmp;                     \
}while(0)

#define cfree(con, label) do {         \
    container_destroy(label, cc(con)); \
    ccmp(con) = NULL;                  \
    cc(con) = NULL;                    \
}while(0)

// 遍历容器，
#define ctravel(con, handle) do {           \
    for(it first = cfirst(con);              \
        !iequal(first, ctail(con));          \
        first = inext(first) ){handle(first);} \
}while(0)

typedef struct _con{
    
    container_t* _container;
    int (*_compare)(type_value_t, type_value_t);

} Container;
static inline
int _crmfind (Container* con, tv find, tv* ret) 
{
    it pos = cfind(con, find);
    if (ivalid(pos)) {
        return cremove(con, pos, ret);
    }else {
        return -1;
    }
}

static inline 
int _caddfind (Container* con, tv find, tv data) 
{
    it pos = cfind (con, find);
    if (ivalid(pos)) {
        return cinsert(con, pos, data);
    }else {
        return -1;
    }
}

#endif