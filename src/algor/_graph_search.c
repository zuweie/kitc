/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-20 09:34:56
 * @LastEditTime: 2019-10-09 11:15:03
 * @LastEditors: Please set LastEditors
 */
#include "_graph_search.h"
#include "_queue.h"
#include "__mem_pool.h"


static void _bind_bfs_node(it_t it) 
{
    bfs_node_t* pn = allocate(g_pool(0), sizeof(bfs_node_t));
    pn->color = _grp_whtie;
    pn->distance = -1;
    pn->parent = NULL;

    vertex_t* vertex = type_pointer(it_derefer(it));
    vertex->data = pn;
}

static void _bind_dfs_node(it_t it) 
{
    dfs_node_t* pn = allocate(g_pool(0), sizeof(dfs_node_t));
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
    deallocate(g_pool(0), vertex->data);
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

        vertex_t* pu = type_pointer(rdata);
        bfs_node_t* pubfs = pu->data;

        // 遍历节点的邻居表。
        for(it_t first = con_first(&pu->adjacency); 
            !it_equal(first, con_tail(&pu->adjacency)); 
            first=it_next(first)) {

            adjacency_node_t* pv = type_pointer(it_derefer(first));
            bfs_node_t* pvbfs     = (pv->to->data);

            if (pvbfs->color == _grp_whtie) {
                pvbfs->color = _grp_gray;
                pvbfs->distance = pvbfs->distance + 1;
                pvbfs->parent = pu;
                en_queue(&queue, pointer_type(pv->to));
            }
        }
        pubfs->color = _grp_black;
    }
    return 0;
}

static int _dfs_visit(vertex_t* pu, int* time) 
{
    dfs_node_t* pudfs = pu->data;
    pudfs->color = _grp_gray;
    pudfs->d_time = *time + 1;
    // 访问邻接表
    for(it_t first=con_first(&pu->adjacency); !it_equal(first, con_tail(&pu->adjacency)); first=it_next(first)) {
        adjacency_node_t* pv = type_pointer(it_derefer(first));
        dfs_node_t*       pvdfs = pv->to->data;
        if (pvdfs->color == _grp_whtie) {
            pvdfs->parent = pu;
            _dfs_visit(pv->to, time);
        }
    }
    pudfs->color = _grp_black;
    pudfs->f_time = ++(*time);
    return 0;
}

int dfs(graph_t* graph) 
{
    int time = 0;
    con_travel(&graph->vertexes, _bind_dfs_node);

    for(it_t first=con_first(&graph->vertexes); !it_equal(first, con_tail(&graph->vertexes)); first=it_next(first)) {
        vertex_t*   pu = type_pointer(it_derefer(first));
        dfs_node_t* pudfs = pu->data;
        if (pudfs->color == _grp_whtie) {
            _dfs_visit(pu, &time);
        }
    }
    return 0;
}

void grp_cleanup_search_info(graph_t* graph) 
{
    con_travel(&graph->vertexes, _del_fs_node);
}