/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 10:13:53
 * @LastEditTime: 2019-09-16 08:43:57
 * @LastEditors: Please set LastEditors
 */
#ifndef _GRAPH_H_
#define _GRAPH_H_


#include "_type_value.h"
#include "_list.h"
#include "_vector.h"

typedef struct _vertex 
{
    /* vertex id */
    int vertex_id;
    /* other data here */
    list_t adjacency;

} vertex_t;

typedef struct _adjacency_node 
{
    vertex_t* to;
    float weight;
    
} adjacency_node_t;

typedef struct _graph
{
    /* data */
    list_t vertexes;
    
} graph_t;

extern int init_graph(graph_t* graph);
extern int graph_add_vertex(graph_t* graph, int vertex);
extern int graph_add_edge(graph_t* graph, int from, int to, float weigth);
extern int grath_del_vertex(graph_t* graph, int vertex);
extern int grath_del_edge(graph_t* graph, int from, int to);
extern unsigned int graph_edges_count(graph_t* graph);

#endif