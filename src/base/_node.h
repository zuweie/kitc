/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-03 13:29:13
 * @LastEditTime: 2019-09-07 23:24:18
 * @LastEditors: Please set LastEditors
 */

#ifndef _NODE_H_
#define _NODE_H_

typedef union _node
{
    
    /* key */
    int id;
    /* data */
    void* data;
} node_t;

// 
typedef int (*node_cmp_func)(void*, void*);

extern cmp_node_id (node_t*, node_t*);

#endif