/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 10:13:53
 * @LastEditTime: 2019-09-15 17:58:19
 * @LastEditors: Please set LastEditors
 */
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "_type_value.h"
#include "_list.h"
#include "_vector.h"

typedef struct _adjacency_node 
{
    vertex_t* to;
    float weigth;
    
} adjacency_node_t;

typedef struct _vertex 
{

    type_value_t node;
    list_t adjacency;

} vertex_t;

typedef struct _graph
{
    /* data */
    list_t vertexes;
    
} graph_t;

extern int init_graph(graph_t* graph);
extern int graph_add_vertex(graph_t* graph, type_value_t vertex);
extern int graph_add_edge(graph_t* graph, type_value_t from, type_value_t to, float weigth, int(compare_vertex)(type_value_t, type_value_t));
extern int grath_del_vertex(graph_t* graph, type_value_t vertex, int (compare_vertex)(type_value_t, type_value_t));
extern int grath_del_edge(graph_t* graph, type_value_t from, type_value_t to, int (compare_vertex)(type_value_t, type_value_t));
extern unsigned int graph_edges_count(graph_t* graph);

#endif