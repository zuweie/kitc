/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 10:14:04
 * @LastEditTime: 2019-09-20 09:31:28
 * @LastEditors: Please set LastEditors
 */
#include "_graph.h"
#include "_list.h"
#include "_mem_pool.h"


int _find_vertex(type_value_t node, type_value_t find) {

    vertex_t* ver1 = type_pointer(node);
    int ver2 = type_int(find);    
    return !(ver1->vertex_id = ver2);
}

int _find_adj (type_value_t node, type_value_t find) {
    adjacency_node_t* adj = type_pointer(node);
    vertex_t* ver         = type_pointer(find);
    return !(adj->to == ver);
}

static vertex_t* _create_vertex(int id) 
{
    vertex_t* v = allocate(pool(0), sizeof(vertex_t));
    v->vertex_id = id;
    init_set(&v->adjacency);
    return v;
}

static adjacency_node_t* _create_adjacency_node(vertex_t* to, float weight) 
{
    adjacency_node_t* node = allocate(pool(0), sizeof(adjacency_node_t));
    node->to = to;
    node->weight = weight;
    return node;
}

int init_graph(graph_t* graph, int(*compare_vertex)(type_value_t, type_value_t), int(*compare_adjnode)(type_value_t, type_value_t)) 
{
    init_set(&graph->vertexes);
    graph->compare_vertex = compare_vertex;
    graph->compare_adjnode = compare_adjnode;
    return 0;
} 

int graph_add_vertex(graph_t* graph, int vertex) 
{
    vertex_t* v = _create_vertex(vertex);
    // 值插屁股
    return set_insert(&v->adjacency, pointer_type(v), graph->compare_vertex);
}

int graph_add_edge(graph_t* graph, int from, int to, float weight)
{
    iterator_t it_from = container_find(&graph->vertexes, int_type(from), graph->compare_vertex);
    iterator_t it_to   = container_find(&graph->vertexes, int_type(to), graph->compare_vertex);
    
    if (iterator_valid(it_from) && iterator_valid(it_to)) {
        vertex_t* v_from = type_pointer(iterator_dereference(it_from));
        vertex_t* v_to   = type_pointer(iterator_dereference(it_to));

        return set_insert(&v_from->adjacency, pointer_type(v_to), graph->compare_adjnode);
    }
    return -1;
}

int graph_del_vertex(graph_t* graph, int vertex)
{
    
    type_value_t r_vertext;
    if (container_remove_find(&graph->vertexes, int_type(vertex), &r_vertext, graph->compare_vertex) != -1) {
        vertex_t* pv = type_pointer(r_vertext);

        type_value_t r_adj;

        while( container_remove_last(&pv->adjacency, &r_adj) != -1 ) {
            deallocate(pool(0), type_pointer(r_adj));
        }

        deallocate(pool(0), pv);
        return 0;
    }
    return -1;
}

int graph_del_edge(graph_t* graph, int from, int to)
{
    iterator_t it_from = container_find(&graph->vertexes, int_type(from), graph->compare_vertex);
    iterator_t it_to   = container_find(&graph->vertexes, int_type(to), graph->compare_vertex);

    if (iterator_valid(it_from) && iterator_valid(it_to)) {

        vertex_t* v_from = type_pointer(iterator_dereference(it_from));
        vertex_t* v_to   = type_pointer(iterator_dereference(it_to));

        type_value_t r_adj;
        if (container_remove_find(&v_from->adjacency, pointer_type(v_to), &r_adj, graph->compare_adjnode) != -1) {
            deallocate(pool(0), type_pointer(r_adj));
            return 0;
        }
    }
    return -1;
}
