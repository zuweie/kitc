/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-03 17:13:11
 * @LastEditTime: 2019-09-03 19:38:11
 * @LastEditors: Please set LastEditors
 */
#ifndef MEM_H
#define MEM_H
#include <stdlib.h>

#define ALLOC_DEBUG 1

#define __ALIGN 8
#define __MAX_BYTES 128

#define FREELIST_SIZE  (__MAX_BYTES)/(__ALIGN)
#define ROUND_UP(x) (((x) +  __ALIGN-1) & ~(__ALIGN - 1))
#define FREELIST_INDEX(x) (((x) + __ALIGN-1)/__ALIGN -1)
#define alloc instance()

typedef union _pool_node
{
	union node_t* free_list_link;
	char client_data[1];
} pool_node_t;


typedef struct _alloc
{
	char * start_free;
	char * end_free;
	size_t heap_size;
	pool_node_t * volatile free_list[FREELIST_SIZE];

} alloc_t;

extern void  alloc_init (alloc_t* );
extern void* allocate (alloc_t* , size_t n);
extern void  deallocate(alloc_t* , void* p, size_t n);
extern alloc_t* instance();

#if ALLOC_DEBUG
extern size_t oz_freelist_size (alloc_t* , size_t n);
#endif

#endif

