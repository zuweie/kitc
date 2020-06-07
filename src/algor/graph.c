/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 10:14:04
 * @LastEditTime: 2020-06-06 10:21:06
 * @LastEditors: Please set LastEditors
 */
#include "graph.h"
#include "cn.h"
#include "tv.h"

static vertex_t* _create_vertex(Graph* graph, tv vertex) 
{
    // 生成一个顶点
    vertex_t* v =(vertex_t*) malloc (sizeof (vertex_t));
    v->vertex_id = vertex;
    // 这个找
    Set_init(&v->edges, graph->compare_edge);
    return v;
}
static int _free_vertex(vertex_t* vertex) {
    Set_free(&vertex->edges);
    free(vertex);
    return 0;
}
static edge_t* _create_edge(vertex_t* to, float weight) 
{
    // 生成邻接表的节点
    edge_t* node = (edge_t*) malloc (sizeof(edge_t)); 
    node->to = to;
    node->weight = weight;
    return node;
}
static int _free_edge (edge_t* pnode) 
{
    free(pnode);
}

int Graph_init(Graph* graph, int(*find_vertex)(tv, tv), int(*find_link)(tv, tv)) 
{
    // 初始化图
    Set_init(&graph->vertexes, find_vertex);
    graph->compare_edge = find_link;
    graph->compare_vertex   = find_vertex;
    return 0;
} 


int Graph_free(Graph* graph) 
{
    // 把图给干掉了
    
    // 把定点删了。
    for (it first = CN_first(&graph->vertexes); 
        !It_equal(first, CN_tail(&graph->vertexes)); 
        first = It_next(first)) {

            vertex_t* pv = t2p(It_dref(first));

            Graph_delVertex(pv);
    }
    Set_free(&graph->vertexes);
    graph->compare_edge   = NULL;
    graph->compare_vertex = NULL;
    return 0;
}

int Graph_addVertex(Graph* graph, tv vertex) 
{
    vertex_t* v = _create_vertex(graph, vertex);
    return Set_insert(&graph->vertexes, p2t(v));
}

int Graph_addEdge(Graph* graph, vertex_t* from, vertex_t* to, float weight)
{
    // 首先得找一下 开始点 到 终结点 是不是在图中。
    edge_t *p = _create_edge(to, weight);
    return Set_insert(&from->edges, p2t(p));
}

int Graph_delVertex(vertex_t* vertex)
{
    tv rnode;
    while (Set_rm_last(&vertex->edges, &rnode) != -1)
    {
        _free_edge(t2p(rnode));
    }

    _free_vertex(vertex);
    return 0;
}

int Graph_delEdge(vertex_t* from, vertex_t* to)
{
    tv rnode;
    if (Set_rm_target(&from->edges, to->vertex_id, &rnode) != -1)
    {
        _free_edge(t2p(rnode));
    }
    return 0;
}

vertex_t* Graph_getVertex(Graph* graph, tv vertex_id) 
{
    it i = Set_find(&graph->vertexes, vertex_id);
    return It_valid(i) ? It_getptr(i) : NULL;
}

edge_t* Graph_getEdge(vertex_t* from, tv to_id) {
    it i = Set_find(&from->edges, to_id);
    return It_valid(i) ? It_getptr(i) : NULL;
}