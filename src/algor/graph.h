/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 10:13:53
 * @LastEditTime: 2020-06-02 16:31:36
 * @LastEditors: Please set LastEditors
 */
#ifndef _GRAPH_H_
#define _GRAPH_H_


#include "tv.h"
#include "set.h"

typedef struct _vertex 
{
    /* vertex id */
    tv vertex;
    /* other data here */
    void* data;
    Set adjacency;
} vertex_t;

typedef struct _adjacency_node 
{
    vertex_t* to;
    float weight;
    
} adjacency_node_t;

typedef struct _graph
{
    /* data */
    Set vertexes;
    int (*compare_adjnode)(tv node, tv find);
    int (*compare_vertex) (tv node, tv find);
} Graph;

int Graph_init(Graph* graph, int(*)(tv, tv), int(*)(tv, tv));
int Graph_addVertex(Graph* graph, tv vertex);
int Graph_addEdge(Graph* graph, tv from, tv to, float weigth);
int Graph_delVertex(Graph* graph, tv vertex);
int Graph_delEdge(Graph* graph, tv from, tv to);

void graph_set_vertex_data(iterator_t it, void* data);
void* graph_get_vertex_data(iterator_t it);
#endif