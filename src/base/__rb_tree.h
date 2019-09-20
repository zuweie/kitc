/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-11 10:07:38
 * @LastEditTime: 2019-09-20 10:30:17
 * @LastEditors: Please set LastEditors
 */
#ifndef _RB_TREE_H_
#define _RB_TREE_H_

#include "__type_value.h"
#include "__container.h"

#define _red 0
#define _black 1

#define _null(prb) (&((prb)->_null))

typedef struct _rb_tree_node rb_tree_node_t;
struct _rb_tree_node {
    type_value_t node;
    unsigned char color;
    rb_tree_node_t* parent;
    rb_tree_node_t* left;
    rb_tree_node_t* right;
};

typedef struct _rb_tree {
    container_t container;
    rb_tree_node_t* _root;
    rb_tree_node_t _null;
    unsigned int _size;
    int (*_insert_compare) (type_value_t, type_value_t);
}rb_tree_t;

extern void init_rb_tree(rb_tree_t*, int(*insert_compare)(type_value_t, type_value_t));
extern iterator_t rb_tree_root(rb_tree_t*);
extern iterator_t rb_tree_null(rb_tree_t*);
#endif