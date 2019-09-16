/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 10:14:04
 * @LastEditTime: 2019-09-16 19:01:16
 * @LastEditors: Please set LastEditors
 */
#include "_graph.h"
#include "_list.h"
#include "_mem_pool.h"

static int _find_vertex(type_value_t node, type_value_t find) {

    vertex_t* ver1 = type_pointer(node);
    int ver2 = type_int(find);    
    return !(ver1->vertex_id = ver2);
}

static int _find_adj (type_value_t node, type_value_t find) {
    adjacency_node_t* adj = type_pointer(node);
    vertex_t* ver         = type_pointer(find);
    return !(adj->to == ver);
}

static vertex_t* _create_vertex(int id) 
{
    vertex_t* v = allocate(pool(0), sizeof(vertex_t));
    v->vertex_id = id;
    init_list(&v->adjacency);
    return v;
}

static adjacency_node_t* _create_adjacency_node(vertex_t* to, float weight) 
{
    adjacency_node_t* node = allocate(pool(0), sizeof(adjacency_node_t));
    node->to = to;
    node->weight = weight;
    return node;
}

int init_graph(graph_t* graph) 
{
    init_list(&graph->vertexes);
}


int graph_add_vertex(graph_t* graph, int vertex) 
{
    vertex_t* v = _create_vertex(vertex);
    // 值插屁股
    return container_insert_tail(&v->adjacency, pointer_type(v));
}

int graph_add_edge(graph_t* graph, int from, int to, float weight)
{
    iterator_t it_from = container_find(&graph->vertexes, int_type(from), _find_vertex);
    iterator_t it_to   = container_find(&graph->vertexes, int_type(to), _find_vertex);

    if(iterator_valid(it_from) && iterator_valid(it_to)) {
        // 1 检查一下 from adj列表是否已经存在 to
        vertex_t* vertex_to   = type_pointer( iterator_dereference(it_to) );
        vertex_t* vertex_from = type_pointer( iterator_dereference(it_from) );

        iterator_t it_adj = container_find( &vertex_from->adjacency, pointer_type(vertex_to), _find_adj);

        if (!iterator_valid(it_adj)) {
            // 2 这个顶点没插过插一下。
            adjacency_node_t* node = _create_adjacency_node(vertex_to, weight);
            container_insert_tail(&vertex_from->adjacency, pointer_type(node));
            return 0;
        }
    }
    return -1;
}

int grath_del_vertex(graph_t* graph, int vertex)
{
    iterator_t it_vertext = container_find(&graph->vertexes, int_type(vertex), _find_vertex);
    
    if (iterator_valid(it_vertext)) {
        type_value_t r_vertex;
        container_remove(&graph->vertexes, it_vertext, &r_vertex);
        vertex_t* pv = type_pointer(r_vertex);

        // 循环删除list
        type_value_t r_adj;
        while( container_remove_last(&pv->adjacency, &r_adj) != -1) {
            adjacency_node_t* pa = type_pointer(r_adj);
            deallocate(pool(0), pa);
        }
        
        deallocate(pool(0), pv);
        return 0;
    }
    return -1;
}

int grath_del_edge(graph_t* graph, int from, int to)
{
    iterator_t it_from = container_find(&graph->vertexes, int_type(from), _find_vertex);
    iterator_t it_to   = container_find(&graph->vertexes, int_type(to), _find_vertex);

    if (iterator_valid(it_from) && iterator_valid(it_to)) {
        vertex_t* vertex_from = type_pointer(iterator_dereference(it_from));
        type_value_t adj;
        iterator_t it_adj = container_find(&vertex_from->adjacency, iterator_dereference(it_to), _find_adj);
        if (container_remove(&vertex_from->adjacency, it_adj, &adj) != -1) {
            adjacency_node_t* pa = type_pointer(adj);
            deallocate(pool(0), pa);
            return 0;
        }
    }
    return -1;
}
