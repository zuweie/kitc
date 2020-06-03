/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-20 09:44:49
 * @LastEditTime: 2020-06-03 12:34:09
 * @LastEditors: Please set LastEditors
 */
#ifndef _GRAPH_SEARCH_H_
#define _GRAPH_SEARCH_H_
#include "graph.h"
#include "it.h"

typedef enum _grp_color {
    _grp_whtie = 0,
    _grp_gray  = 1,
    _grp_black = 2
} grp_color_t;

typedef struct _bfs_node {
    int distance;
    grp_color_t color;
    vertex_t* parent;
}bfs_node_t; 

typedef struct _dfs_node {
    int d_time;
    int f_time;
    grp_color_t color;
    vertex_t* parent;
} dfs_node_t;

int grp_bfs(Graph* graph, vertex_t* start);
int grp_dfs(Graph* graph);
void grp_cleanup_search_info(Graph* graph);

#endif