/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-20 18:51:11
 * @LastEditTime: 2019-09-20 19:43:19
 * @LastEditors: Please set LastEditors
 */
#ifndef _CONTAINER_IMP_H_
#define _CONTAINER_IMP_H_
#include "__container.h"

typedef struct _con_adapter {

    container_t* _container;
    int (*_compare)(type_value_t, type_value_t);

} con_adapter_t;

extern void init_adapter(con_adapter_t* con, container_t* container, int (*compare)(type_value_t, type_value_t));
extern iterator_t first(con_adapter_t* con);
extern iterator_t last(con_adapter_t* con);
extern iterator_t head(con_adapter_t* con);
extern iterator_t tail(con_adapter_t* con);
extern iterator_t search(con_adapter_t* con, iterator_t offset, type_value_t find);
extern iterator_t find(con_adapter_t* con, type_value_t find);
extern int insert(con_adapter_t* con, iterator_t it, type_value_t data);
extern int insret_find(con_adapter_t* con, type_value_t find, type_value_t data);
extern int insert_first(con_adapter_t* con, type_value_t data);
extern int insert_tail(con_adapter_t* con, type_value_t data);
extern int remove(con_adapter_t* con, iterator_t it, type_value_t* rdata);
extern int remove_find(con_adapter_t* con, type_value_t find, type_value_t* rdata);
extern int remove_first(con_adapter_t* con, type_value_t* rdata);
extern int remove_last(con_adapter_t* con, type_value_t* rdata);
extern int has(con_adapter_t* con, type_value_t find);
extern unsigned int size(con_adapter_t* con);

#endif