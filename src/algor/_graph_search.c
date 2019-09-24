/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-20 09:34:56
 * @LastEditTime: 2019-09-24 13:49:11
 * @LastEditors: Please set LastEditors
 */
#include "_graph_search.h"
#include "_queue.h"
#include "_mem_pool.h"


static void _bind_bfs_node(it_t it) 
{
    bfs_node_t* pn = allocate(pool(0), sizeof(bfs_node_t));
    pn->color = _grp_whtie;
    pn->distance = -1;
    pn->parent = NULL;

    vertex_t* vertex = type_pointer(it_derefer(it));
    vertex->data = pn;
}

static void _bind_dfs_node(it_t it) 
{
    dfs_node_t* pn = allocate(pool(0), sizeof(dfs_node_t));
    pn->color = _grp_whtie;
    pn->parent = NULL;
    pn->d_time = -1;
    pn->f_time = -1;

    vertex_t* vertex = type_pointer(it_derefer(it));
    vertex->data = pn;
}

static void _del_fs_node (it_t it) 
{
    vertex_t* vertex = type_pointer(it_derefer(it));
    deallocate(pool(0), vertex->data);
    vertex->data = NULL;
}

int bfs(graph_t* graph, vertex_t* start) {

    con_travel(&graph->vertexes, _bind_bfs_node);
    // 2 做广度优先遍历
    // 
    queue_t queue;
    init_queue(&queue, graph->compare_vertex);
    
    en_queue(&queue, pointer_type(start));
    type_value_t rdata;
    while(de_queue(&queue,&rdata) != -1) {

        vertex_t* pv = type_pointer(rdata);
        bfs_node_t* pvbfs = pv->data;

        // 遍历节点的邻居表。
        for(it_t first = con_first(&pv->adjacency); 
            !it_equal(first, con_tail(&pv->adjacency)); 
            first=it_next(first)) {

            adjacency_node_t* pa = type_pointer(it_derefer(first));
            bfs_node_t* pabfs     = (pa->to->data);

            if (pabfs->color == _grp_whtie) {
                pabfs->color = _grp_gray;
                pabfs->distance = pvbfs->distance + 1;
                pabfs->parent = pv;
            }
        }
        pvbfs->color = _grp_black;
    }
    return 0;
}

static int _dfs_visit(vertex_t* v, int* time) 
{
    dfs_node_t* pvdfs = v->data;
    pvdfs->color = _grp_gray;
    pvdfs->d_time = *time + 1;
    // 访问邻接表
    for(it_t first=con_first(&v->adjacency); !it_equal(first, con_tail(&v->adjacency)); first=it_next(first)) {
        adjacency_node_t* pa = type_pointer(it_derefer(first));
        dfs_node_t*       padfs = pa->to->data;
        if (padfs->color == _grp_whtie) {
            padfs->parent = v;
            _dfs_visit(pa->to, time);
        }
    }
    pvdfs->color = _grp_black;
    pvdfs->f_time = ++(*time);
    return 0;
}

int dfs(graph_t* graph, vertex_t* start) 
{
    int time = 0;
    con_travel(&graph->vertexes, _bind_dfs_node);
    for(it_t first=con_first(&graph->vertexes); !it_equal(first, con_tail(&graph->vertexes)); first=it_next(first)) {
        vertex_t*   pv = type_pointer(it_derefer(first));
        dfs_node_t* pvdfs = pv->data;
        if (pvdfs->color == _grp_whtie) {
            _dfs_visit(pv, &time);
        }
    }
    return 0;
}