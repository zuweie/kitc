/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 10:13:53
 * @LastEditTime: 2019-09-20 09:38:29
 * @LastEditors: Please set LastEditors
 */
#ifndef _GRAPH_H_
#define _GRAPH_H_


#include "_type_value.h"
#include "_set.h"

typedef struct _vertex 
{
    /* vertex id */
    int vertex_id;
    /* other data here */
    void* attach;
    set_t adjacency;

} vertex_t;

typedef struct _adjacency_node 
{
    vertex_t* to;
    float weight;
    
} adjacency_node_t;

typedef struct _graph
{
    /* data */
    set_t vertexes;
    int (*compare_vertex)(type_value_t node, type_value_t find);
    int (*compare_adjnode)(type_value_t node, type_value_t find);
    
} graph_t;

extern int init_graph(graph_t* graph, int(*)(type_value_t, type_value_t), int(*)(type_value_t, type_value_t));
extern int graph_add_vertex(graph_t* graph, int vertex);
extern int graph_add_edge(graph_t* graph, int from, int to, float weigth);
extern int graph_del_vertex(graph_t* graph, int vertex);
extern int graph_del_edge(graph_t* graph, int from, int to);

#endif