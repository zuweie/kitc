/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 10:13:53
 * @LastEditTime: 2020-06-04 11:37:16
 * @LastEditors: Please set LastEditors
 */
#ifndef _GRAPH_H_
#define _GRAPH_H_


#include "tv.h"
#include "set.h"

typedef struct _vertex 
{
    /* vertex id */
    tv vertex_id;
    /* other data here */
    void* data;
    Set links;
} vertex_t;

typedef struct _link_node 
{
    vertex_t* to;
    float weight;
    
} link_node_t;

typedef struct _graph
{
    /* data */
    Set vertexes;
    int (*compare_linknode)(tv node, tv find);
    int (*compare_vertex) (tv node, tv find);
} Graph;

int Graph_init(Graph* graph, int(*)(tv, tv), int(*)(tv, tv));
int Graph_free(Graph* graph);
int Graph_addVertex(Graph* graph, tv vertex);
int Graph_addEdge(Graph* graph, vertex_t* from, vertex_t* to, float weigth);
int Graph_delVertex(vertex_t* vertex);
int Graph_delEdge(vertex_t* from, vertex_t* to);
#endif