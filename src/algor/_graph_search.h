/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-20 09:44:49
 * @LastEditTime: 2019-09-24 13:51:36
 * @LastEditors: Please set LastEditors
 */
#ifndef _GRAPH_SEARCH_H_
#define _GRAPH_SEARCH_H_
#include "_graph.h"
#include "__iterator.h"

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

extern int grp_bfs(graph_t* graph, vertex_t* start);
extern int grp_dfs(graph_t* graph, vertex_t* start);
extern int grp_clean_search_info(graph_t* graph);
#endif