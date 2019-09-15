/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 10:14:04
 * @LastEditTime: 2019-09-15 18:05:57
 * @LastEditors: Please set LastEditors
 */
#include "_graph.h"
#include "_list.h"
#include "_mem_pool.h"

static vertex_t* _create_vertex(type_value_t node) 
{
    vertex_t* v = allocate(pool(0), sizeof(vertex_t));
    init_list(&v->adjacency);
    return v;
}

static adjacency_node_t* _create_adjacency_node(vertex_t* to, float weight) 
{

    adjacency_node_t* node = allocate(pool(0), sizeof(adjacency_node_t));
    node->to = to;
    node->weigth = weight;
    return node;
}

int init_graph(graph_t* graph) 
{
    init_list(&graph->vertexes);
}


int graph_add_vertex(graph_t* graph, type_value_t vertex) 
{
    vertex_t* v = _create_vertex(vertex);
    // 值插屁股
    return container_insert_tail(&v->adjacency, vertex);
}

int graph_add_edge(graph_t* graph, type_value_t from, type_value_t to, float weigth, int(compare_vertex)(type_value_t, type_value_t))
{
    iterator_t vertex_pos = container_find(&graph->vertexes, from, compare_vertex);
    if(iterator_valid(vertex_pos)) {
        vertex_t* vertex = type_pointer(iterator_dereference(vertex_pos));
        
    }
    return -1;
}

int grath_del_vertex(graph_t* graph, type_value_t vertex, int (compare_vertex)(type_value_t, type_value_t));
int grath_del_edge(graph_t* graph, type_value_t from, type_value_t to, int (compare_vertex)(type_value_t, type_value_t));
unsigned int grath_edegs_count(graph_t* graph);