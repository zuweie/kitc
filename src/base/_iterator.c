/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-10 11:00:17
 * @LastEditTime: 2019-09-11 15:56:25
 * @LastEditors: Please set LastEditors
 */
#include "_iterator.h"

// 默认版本

static inline type_value_t __iterator_dereference (iterator_t it) 
{
    return *((type_value_t*)iterator_reference(it));
}

static inline int __iterator_equal (iterator_t t1, iterator_t t2) 
{
    return iterator_reference(t1) == iterator_reference(t2);    
}

static inline int __iterator_assign (iterator_t t1, iterator_t t2) 
{
    *((type_value_t*)iterator_reference(t2)) = iterator_dereference(t1);
    return 0;
}

static inline __iterator_exchange (iterator_t t1, iterator_t t2) 
{
    type_value_t tmp = iterator_dereference(t2);
    *((type_value_t*)iterator_reference(t2)) = iterator_dereference(t1);
    *((type_value_t*)iterator_reference(t1)) = tmp;
    return 0;
}

iterator_t get_iterator(void* __refer,
    void* __attach,
    iterator_t (*__next)(iterator_t),
    iterator_t (*__prev)(iterator_t)) {
        
        iterator_t it = {
            .reference = __refer,
            .attach = __attach,  
            .dereference = __iterator_dereference,
            .next = __next,
            .prev = __prev,
            .equal = __iterator_equal,
            .assign = __iterator_assign,
            .exchange = __iterator_exchange
        };

        return it;
}