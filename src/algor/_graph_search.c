/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-20 09:34:56
 * @LastEditTime: 2019-09-20 21:52:38
 * @LastEditors: Please set LastEditors
 */
#include "_graph_search.h"
#include "_mem_pool.h"


static void* _create_bfs_node() 
{

}

int bfs(graph_t* graph) {

    // 初始化所有节点。
    
    for(iterator_t first = container_first(&graph->vertexes); 
        !iterator_equal(first, container_tail(&graph->vertexes)); 
        first = iterator_next(first)) {
            
        bfs_node_t* pn = _create_bfs_node();

        graph_set_vertex_data(first, pn);
    }
    return 0;
}