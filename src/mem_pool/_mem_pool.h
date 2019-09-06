/*
 * @Description: 一个简单的内存池模型
 * @Author: zuweie
 * @Date: 2019-09-03 17:13:11
 * @LastEditTime: 2019-09-06 08:29:37
 * @LastEditors: Please set LastEditors
 */
#ifndef _MEM_POOL_H_
#define _MEM_POOL_H_

#include <stdlib.h>

#define ALLOC_DEBUG 1

#define __ALIGN 8
#define __MAX_BYTES 128

#define __NODE_INFO_BYTES 1
#define __REFILL_CHUNK_SIZE 20

#define POOL_FREELIST_SIZE (__MAX_BYTES) / (__ALIGN)
#define POOL_ROUND_UP(x) (((x) + __ALIGN - 1) & ~(__ALIGN - 1))
#define POOL_FREELIST_INDEX(x) (((x) + __ALIGN - 1) / __ALIGN - 1)

#define POOL_ATTACH_INFO_SIZE(x) (x + __NODE_INFO_BYTES)
#define POOL_DETACH_INFO_SIZE(X) (x - __NODE_INFO_BYTES)

#define POOL_EXPORT_POINTER(p) ((char *)p + __NODE_INFO_BYTES)
#define POOL_RECOVER_POINTER(p) ((char *)p - __NODE_INFO_BYTES)
#define pool(x) instance(x)

typedef union _pool_node 
{
	// 这个鬼指向下一个node
	union _pool_node *free_list_link;
	// 指向用户的可以使用的内存
	char client_data[1];
	//  保留一个字节做
	unsigned char slot;

} pool_node_t;

typedef struct _pool
{
	char *start_free;
	char *end_free;
	size_t heap_size;
	pool_node_t *volatile free_list[POOL_FREELIST_SIZE];

} pool_t;

extern int alloc_init(pool_t *);
extern void *allocate(pool_t *, size_t n);
extern void deallocate(pool_t *, void *p);
extern pool_t *instance(int *);

#if ALLOC_DEBUG
extern size_t freelist_size(pool_t *, size_t n);
extern void inspect_pool(pool_t *);
extern size_t size_of_slot(int slot);

#endif

#endif
