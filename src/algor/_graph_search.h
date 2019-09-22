/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-20 09:44:49
 * @LastEditTime: 2019-09-22 09:00:40
 * @LastEditors: Please set LastEditors
 */
#ifndef _GRAPH_SEARCH_H_
#define _GRAPH_SEARCH_H_
#include "_graph.h"
#include "__iterator.h"

#define _gph_white 0
#define _gph_gray  1
#define _gph_black 2

typedef struct _bfs_node {
    int distance;
    unsigned char color;
    vertex_t* parent;
}bfs_node_t; 

extern int bfs(graph_t* graph, vertex_t* start);
#endif