/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 10:13:53
 * @LastEditTime: 2020-06-05 23:13:47
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
    Set edges;
} vertex_t;

typedef struct _edge
{
    vertex_t* to;
    float weight;
    
} edge_t;

typedef struct _graph
{
    /* data */
    Set vertexes;
    int (*compare_edge)(tv node, tv find);
    int (*compare_vertex) (tv node, tv find);
} Graph;

int Graph_init(Graph* graph, int(*find_vertex)(tv, tv), int(*find_link)(tv, tv));
int Graph_free(Graph* graph);
int Graph_addVertex(Graph* graph, tv vertex);
int Graph_addEdge(Graph* graph, vertex_t* from, vertex_t* to, float weigth);
int Graph_delVertex(vertex_t* vertex);
int Graph_delEdge(vertex_t* from, vertex_t* edge);
vertex_t* Graph_getVertex(Graph* graph, tv vertex_id);
edge_t* Graph_getEdge(vertex_t* from, tv to_id);
#endif