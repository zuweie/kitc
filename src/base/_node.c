/*
 * @Description: node
 * @Author: zuweie
 * @Date: 2019-09-03 13:29:23
 * @LastEditTime: 2019-09-03 18:36:50
 * @LastEditors: Please set LastEditors
 */

#include "_node.h"

extern int cmp_node (void* e1, void* e2) 
{
    if (((node_t*)e1)->id > ((node_t*)e2)->id) return 1;
    else if (((node_t*)e1)->id < ((node_t*)e2)->id) return -1;
    else return 0;
}