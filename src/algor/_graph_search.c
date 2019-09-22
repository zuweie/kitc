/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-20 09:34:56
 * @LastEditTime: 2019-09-22 09:27:50
 * @LastEditors: Please set LastEditors
 */
#include "_graph_search.h"
#include "_queue.h"
#include "_mem_pool.h"


static void* _bind_bfs_node(vertex_t* v) 
{
    bfs_node_t* pn = allocate(pool(0), sizeof(bfs_node_t));
    pn->color = _gph_white;
    pn->distance = -1;
    pn->parent = NULL;

    v->data = pn;
}

int bfs(graph_t* graph, vertex_t* start) {

    con_travel(&graph->vertexes, _bind_bfs_node);
    // 2 做广度优先遍历
    // 
    queue_t queue;
    init_queue(&queue, graph->compare_vertex);
    
    en_queue(&queue, pointer_type(start));

    while(con_size(&en_queue) != 0) {
        type_value_t rdata;
        if (de_queue(&queue, &rdata)) {
            
        }
    }
    return 0;
}