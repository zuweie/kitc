/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-20 18:51:25
 * @LastEditTime: 2019-09-20 21:53:59
 * @LastEditors: Please set LastEditors
 */
#include "__container.h"
#include "_container_adapter.h"

void init_adapter(con_adapter_t* con, container_t* container, int (*compare)(type_value_t, type_value_t)) {
    con->_container = container;
    con->_compare   = compare;
    return;
}
iterator_t first(con_adapter_t* con) 
{
    return container_first(con->_container);
}

iterator_t last(con_adapter_t* con) 
{
    return container_last(con->_container);
}

iterator_t head(con_adapter_t* con)
{
    return container_head(con->_container);
}

iterator_t tail(con_adapter_t* con) 
{
    return container_tail(con->_container);
}

iterator_t search(con_adapter_t* con, iterator_t offset, type_value_t find)
{
    return container_search(con->_container, offset, find, con->_compare);
}

iterator_t find(con_adapter_t* con, type_value_t find)
{
    return container_find(con->_container, find, con->_compare);
}

int insert(con_adapter_t* con, iterator_t it, type_value_t data) 
{
    return container_insert(con->_container, it, data);
}

int insret_find(con_adapter_t* con, type_value_t find, type_value_t data)
{
    return container_insert_find(con->_container, find, data, con->_compare);
}

int insert_first(con_adapter_t* con, type_value_t data) 
{
    return container_insert_first(con->_container, data);
}

int insert_tail(con_adapter_t* con, type_value_t data) 
{
    return container_insert_tail(con->_container, data);
}

int remove(con_adapter_t* con, iterator_t it, type_value_t* rdata)
{
    return container_remove(con->_container, it, rdata);
}

int remove_find(con_adapter_t* con, type_value_t find, type_value_t* rdata) 
{
    return container_remove_find(con->_container, find, rdata, con->_compare);
}

int remove_first(con_adapter_t* con, type_value_t* rdata) 
{
    return container_remove_first(con->_container, rdata);
}

int remove_last(con_adapter_t* con, type_value_t* rdata)
{
    return container_remove_last(con->_container, rdata);
}
int has(con_adapter_t* con, type_value_t find)
{
    return container_has(con->_container, find, con->_compare);
}

unsigned int size(con_adapter_t* con) 
{
    return container_size(con->_container);
}