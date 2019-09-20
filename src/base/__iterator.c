/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-10 11:00:17
 * @LastEditTime: 2019-09-20 13:00:39
 * @LastEditors: Please set LastEditors
 */
#include "__iterator.h"

// 默认版本

static inline type_value_t __iterator_dereference (iterator_t it) 
{
    return *((type_value_t*)iterator_reference(it));
}

static inline int __iterator_equal (iterator_t t1, iterator_t t2) 
{
    return iterator_reference(t1) == iterator_reference(t2);    
}

static inline int __iterator_assign (iterator_t to, iterator_t from) 
{
    *((type_value_t*)iterator_reference(to)) = iterator_dereference(from);
    return 0;
}

static inline __iterator_exchange (iterator_t t1, iterator_t t2) 
{
    type_value_t tmp = iterator_dereference(t2);
    *((type_value_t*)iterator_reference(t2)) = iterator_dereference(t1);
    *((type_value_t*)iterator_reference(t1)) = tmp;
    return 0;
}

static inline __iterator_valid(iterator_t it) 
{
    return iterator_reference(it) != 0;
}

iterator_t get_iterator(void* __refer, void* __attach, iterator_t (*__move)(iterator_t, int)) {
        
        iterator_t it = {
            .dereference = __iterator_dereference,
            .move = __move,
            .valid = __iterator_valid,
            .equal = __iterator_equal,
            .assign = __iterator_assign,
            .exchange = __iterator_exchange,
            .reference = __refer,
            .attach = __attach,
        };

        return it;
}