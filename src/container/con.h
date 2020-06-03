/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-20 18:51:11
 * @LastEditTime: 2020-06-03 15:52:26
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

#define CN_first(con) container_first(cc(con))
#define CN_last(con) container_last(cc(con))
#define CN_head(con) container_head(cc(con))
#define CN_tail(con) container_tail(cc(con))

#define CN_search(con,offset,find) container_search(cc(con), offset, find, ccmp(con))
#define CN_find(con,find) CN_search(cc(con), CN_first(cc(con)), find)

#define CN_insert(con, it, data) container_insert(cc(con), it, data)
// 头部插入
#define CN_add_first(con, data) CN_insert(cc(con), CN_first(cc(con)), data)
// 尾部插入
#define CN_add_tail(con, data) cinsert(cc(con), ctail(cc(con)), data)

#define CN_remove(con, it, rdata) container_remove(cc(con), it, rdata)
// 头部移除
#define CN_rm_first(con, rdata) cremove(cc(con), cfirst(cc(con)), rdata)
// 尾部移除
#define CN_rm_last(con, rdata) cremove(cc(con), clast(cc(con)), rdata)

//#define chas(con, find) container_has(cc(con), find, ccmp(con))
#define CN_size(con) container_size(cc(con))
#define CN_sort(con, cmp) container_sort(cc(con), cmp)

#define CN_rm_find(con, find, ret) _crmfind(con, find, ret)
#define CN_add_find(con, find, data) _caddfind(con, find, data)

#define CN_init(con, label, cmp) do {       \
    cc(con) = container_create(label);   \
    ccmp(con) = cmp;                     \
}while(0)

#define CN_free(con, label) do {         \
    container_destroy(label, cc(con)); \
    ccmp(con) = NULL;                  \
    cc(con) = NULL;                    \
}while(0)

// 遍历容器，
#define CN_travel(con, handle) do {           \
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
    it pos = CN_find(con, find);
    if (ivalid(pos)) {
        return CN_remove(con, pos, ret);
    }else {
        return -1;
    }
}

static inline 
int _caddfind (Container* con, tv find, tv data) 
{
    it pos = CN_find (con, find);
    if (ivalid(pos)) {
        return CN_insert(con, pos, data);
    }else {
        return -1;
    }
}

#endif