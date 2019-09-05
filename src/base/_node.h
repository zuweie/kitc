/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-03 13:29:13
 * @LastEditTime: 2019-09-03 18:29:55
 * @LastEditors: Please set LastEditors
 */

#ifndef _node_h_
#define _node_h_

typedef struct _node
{
    /* key */
    int id;
    /* data */
    void* data;
    /* clean up function */
    int (*clean)(void*);

} node_t;

// 
typedef int (*node_cmp_func)(void*, void*);

extern cmp_node_id (node_t*, node_t*);

#endif