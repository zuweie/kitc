/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 10:14:04
 * @LastEditTime: 2020-06-03 18:57:02
 * @LastEditors: Please set LastEditors
 */
#include "graph.h"
#include "con.h"
#include "tv.h"
//#include "__mem_pool.h"

static vertex_t* _create_vertex(Graph* graph, tv vertex) 
{
    // 生成一个顶点
    vertex_t* v =(vertex_t*) malloc (sizeof (vertex_t));
    v->vertex = vertex;
    Set_init(&v->adjacency, graph->compare_adjnode);
    return v;
}
static int _free_vertex(vertex_t* vertex) {
    Set_free(&vertex->adjacency);
    free(vertex);
    return 0;
}
static adjacency_node_t* _create_adjacency_node(vertex_t* to, float weight) 
{
    // 生成邻接表的节点
    adjacency_node_t* node = (adjacency_node_t*) malloc (sizeof(adjacency_node_t)); 
    node->to = to;
    node->weight = weight;
    return node;
}
static int _free_adjacency_node (adjacency_node_t* pnode) 
{
    free(pnode);
}

int Graph_init(Graph* graph, int(*compare_vertex)(tv, tv), int(*compare_adjnode)(tv, tv)) 
{
    // 初始化图
    Set_init(&graph->vertexes, compare_vertex);
    graph->compare_adjnode = compare_adjnode;
    graph->compare_vertex  = compare_vertex;
    return 0;
} 

int Graph_free(Graph* graph) 
{
    Set_free(&graph->vertexes);
    graph->compare_adjnode = NULL;
    graph->compare_vertex = NULL;
    return 0;
}

int Graph_addVertex(Graph* graph, tv vertex) 
{
    // 生成一个定点加入图中
    vertex_t* v = _create_vertex(graph, vertex);
    return Set_insert(&v->adjacency, pointer_type(v));
}

int Graph_addEdge(Graph* graph, tv from, tv to, float weight)
{
    // 首先得找一下 开始点 到 终结点 是不是在图中。
    it ifrom = Set_find(&graph->vertexes, from);
    it ito   = Set_find(&graph->vertexes, to);
    
    if (It_valid(ifrom) && It_valid(ito)) {
        
        vertex_t* v_from = t2p(It_dref(ifrom));
        vertex_t* v_to   = t2p(It_dref(ito));

        return Set_insert(&v_from->adjacency, p2t(v_to));
    }
    return -1;
}

int Graph_delVertex(Graph* graph, tv vertex)
{
    
    tv r_vertext;
    if ( Set_rm_target(&graph->vertexes, vertex, &r_vertext) != -1) {
        vertex_t* pv = t2p(r_vertext);

        tv r_adj;

        while( Set_rm_last(&pv->adjacency, &r_adj) != -1 ) {
            //deallocate(g_pool(0), type_pointer(r_adj));
            _free_adjacency_node(t2p(r_adj));
        }

        _free_vertex(pv);
        return 0;
    }
    return -1;
}

int Graph_delEdge(Graph* graph, tv from, tv to)
{
    it ifrom = Set_find(&graph->vertexes, from);
    it ito   = Set_find(&graph->vertexes, to);

    if (It_valid(ifrom) && It_valid(ito)) {

        vertex_t* v_from = t2p(It_dref(ifrom));
        vertex_t* v_to   = t2p(It_dref(ito));

        tv r_adj;
        if (Set_rm_target(&v_from->adjacency, p2t(v_to), &r_adj) != -1) {
            //deallocate(g_pool(0), type_pointer(r_adj));
            _free_adjacency_node(t2p(r_adj));
            return 0;
        }
    }
    return -1;
}

void graph_set_vertex_data(it pos, void* data) 
{
    vertex_t* vertex = t2p(It_dref(pos));
    vertex->data = data;
    return;
}

void* graph_get_vertex_data(it pos) 
{
    vertex_t* vertex = t2p(It_dref(pos));
    return vertex->data;
}
