/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 10:13:53
 * @LastEditTime: 2019-09-23 07:28:28
 * @LastEditors: Please set LastEditors
 */
#ifndef _GRAPH_H_
#define _GRAPH_H_


#include "__type_value.h"
#include "_set.h"

typedef struct _vertex 
{
    /* vertex id */
    type_value_t vertex;
    /* other data here */
    void* data;
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
    int (*compare_adjnode)(type_value_t node, type_value_t find);
    int (*compare_vertex) (type_value_t node, type_value_t find);
} graph_t;

extern int init_graph(graph_t* graph, int(*)(type_value_t, type_value_t), int(*)(type_value_t, type_value_t));
extern int graph_add_vertex(graph_t* graph, type_value_t vertex);
extern int graph_add_edge(graph_t* graph, type_value_t from, type_value_t to, float weigth);
extern int graph_del_vertex(graph_t* graph, type_value_t vertex);
extern int graph_del_edge(graph_t* graph, type_value_t from, type_value_t to);

extern void graph_set_vertex_data(iterator_t it, void* data);
extern void* graph_get_vertex_data(iterator_t it);
#endif