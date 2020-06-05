/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-20 09:34:56
 * @LastEditTime: 2020-06-05 23:05:54
 * @LastEditors: Please set LastEditors
 */
#include "graph_search.h"
#include "queue.h"
#include "tv.h"

static void _bind_bfs_node(it pos) 
{
    //bfs_node_t* pn = allocate(g_pool(0), sizeof(bfs_node_t));
    bfs_node_t* pn = (bfs_node_t*)malloc(sizeof(bfs_node_t));
    pn->color = _grp_whtie;
    pn->distance = -1;
    pn->pi = NULL;

    vertex_t* vertex = t2p(It_dref(pos));
    vertex->data = pn;
}

static void _bind_dfs_node(it pos) 
{
    //dfs_node_t* pn = allocate(g_pool(0), sizeof(dfs_node_t));
    dfs_node_t* pn = (dfs_node_t*) malloc (sizeof(dfs_node_t));
    pn->color = _grp_whtie;
    pn->pi = NULL;
    pn->d_time = -1;
    pn->f_time = -1;

    vertex_t* vertex = t2p(It_dref(pos));
    vertex->data = pn;
}

static void _del_fs_node (it pos) 
{
    vertex_t* vertex = t2p(It_dref(pos));
    //deallocate(g_pool(0), vertex->data);
    free (vertex->data);
    vertex->data = NULL;
}

// 广度优先算法
int bfs(Graph* graph, vertex_t* start) {

    CN_travel(&graph->vertexes, _bind_bfs_node);
    // 2 做广度优先遍历
    // 
    Queue queue;
    Queue_init(&queue, NULL);
    
    Queue_offer(&queue, p2t(start));
    tv rdata;
    while(Queue_poll(&queue,&rdata) != -1) {

        vertex_t* pu = t2p(rdata);
        bfs_node_t* pubfs = pu->data;

        // 遍历节点的邻居表。
        for(it first = CN_first(&pu->edges); 
            !It_equal(first, CN_tail(&pu->edges)); 
            first=It_next(first)) {

            edge_t* pv    = t2p(It_dref(first));
            bfs_node_t* pvbfs  = (pv->to->data);

            if (pvbfs->color == _grp_whtie) {
                pvbfs->color = _grp_gray;
                pvbfs->distance = pvbfs->distance + 1;
                pvbfs->pi = pu;
                Queue_offer(&queue, p2t(pv->to));
            }
        }
        pubfs->color = _grp_black;
    }
    Queue_free(&queue);
    return 0;
}

static int _dfs_visit(vertex_t* pu, int* time) 
{
    dfs_node_t* pudfs = pu->data;
    pudfs->color = _grp_gray;
    pudfs->d_time = *time + 1;
    // 访问邻接表
    for(it first=CN_first(&pu->edges); !It_equal(first, CN_tail(&pu->edges)); first=It_next(first)) {
        edge_t* pv   = t2p(It_dref(first));
        dfs_node_t* pvdfs = (dfs_node_t*)pv->to->data;

        if (pvdfs->color == _grp_whtie) {
            pvdfs->pi = pu;
            _dfs_visit(pv->to, time);
        }
    }
    pudfs->color = _grp_black;
    pudfs->f_time = ++(*time);
    return 0;
}

// 深度优先算法
int dfs(Graph* graph) 
{
    int time = 0;
    CN_travel(&graph->vertexes, _bind_dfs_node);

    for(it first=CN_first(&graph->vertexes); !It_equal(first, CN_tail(&graph->vertexes)); first=It_next(first)) {
        vertex_t*   pu = t2p(It_dref(first));
        dfs_node_t* pudfs = pu->data;
        if (pudfs->color == _grp_whtie) {
            _dfs_visit(pu, &time);
        }
    }
    return 0;
}

void grp_cleanup_search_info(Graph* graph) 
{
    CN_travel(&graph->vertexes, _del_fs_node);
}