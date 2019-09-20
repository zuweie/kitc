/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-20 09:44:49
 * @LastEditTime: 2019-09-20 14:58:03
 * @LastEditors: Please set LastEditors
 */
#ifndef _GRAPH_SEARCH_H_
#define _GRAPH_SEARCH_H_
#include "_graph.h"
#include "__iterator.h"

typedef struct _bfs_node {
    int distance;
    unsigned char color;
    vertex_t* parent;
}bfs_node_t; 

extern int bfs(graph_t* graph);
#endif