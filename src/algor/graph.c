/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 10:14:04
 * @LastEditTime: 2020-06-04 11:38:24
 * @LastEditors: Please set LastEditors
 */
#include "graph.h"
#include "con.h"
#include "tv.h"

static vertex_t* _create_vertex(Graph* graph, tv vertex) 
{
    // 生成一个顶点
    vertex_t* v =(vertex_t*) malloc (sizeof (vertex_t));
    v->vertex_id = vertex;
    // 这个找
    Set_init(&v->links, graph->compare_linknode);
    return v;
}
static int _free_vertex(vertex_t* vertex) {
    Set_free(&vertex->links);
    free(vertex);
    return 0;
}
static link_node_t* _create_link_node(vertex_t* to, float weight) 
{
    // 生成邻接表的节点
    link_node_t* node = (link_node_t*) malloc (sizeof(link_node_t)); 
    node->to = to;
    node->weight = weight;
    return node;
}
static int _free_link_node (link_node_t* pnode) 
{
    free(pnode);
}

int Graph_init(Graph* graph, int(*compare_vertex)(tv, tv), int(*compare_linknode)(tv, tv)) 
{
    // 初始化图
    Set_init(&graph->vertexes, compare_vertex);
    graph->compare_linknode = compare_linknode;
    graph->compare_vertex  = compare_vertex;
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
    graph->compare_linknode = NULL;
    graph->compare_vertex = NULL;
    return 0;
}

int Graph_addVertex(Graph* graph, tv vertex) 
{
    // 生成一个定点加入图中
    vertex_t* v = _create_vertex(graph, vertex);
    return Set_insert(&graph->vertexes, p2t(v));
}

int Graph_addEdge(Graph* graph, vertex_t* from, vertex_t* to, float weight)
{
    // 首先得找一下 开始点 到 终结点 是不是在图中。
    link_node_t *plinknode = _create_link_node(to, weight);
    return Set_insert(&from->links, p2t(plinknode));
}

int Graph_delVertex(vertex_t* vertex)
{
    tv rnode;
    while (Set_rm_last(&vertex->links, &rnode) != -1)
    {
        _free_link_node(t2p(rnode));
    }

    _free_vertex(vertex);
    return 0;
}

int Graph_delEdge(vertex_t* from, vertex_t* to)
{
    tv rnode;
    if (Set_rm_target(&from->links, p2t(to), &rnode) != -1)
    {
        _free_link_node(t2p(rnode));
    }
    return 0;
}
