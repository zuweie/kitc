/*
 * @Description: 一个简单的内存池模型
 * @Author: zuweie
 * @Date: 2019-09-03 17:13:11
 * @LastEditTime: 2019-09-27 00:00:09
 * @LastEditors: Please set LastEditors
 */
#ifndef _MEM_POOL_H_
#define _MEM_POOL_H_

#include <stdlib.h>

#define ALLOC_DEBUG 1
#define ENABLE_ALLOC 1

// 申请内存最少为8个byte。
#define __ALIGN 8

// 每次重新装到freelist时的内存块数量
#define __REFILL_CHUNK_SIZE 2

// 存放内存槽信息的位数
#define __SLOT_INFO_BYTES 1

//此宏求i个byte的最大无符号值。
// 例如 i=1，最大值为255
//     i=2, 最大值为65535
//     i=...,  最大值为...
// 
// i 为 1 时的计算过程：
//     1 << 8            => 0000 0000 1000 0000
// - (1 << 8)            => 1111 1111 1000 0000
// ~ (-(1<<8))           => 0000 0000 0111 1111
// (1<<8) | (~(-(1<<8))) => 0000 0000 1111 1111
#define __MAX_VAL_OF_BYTES(i) ((1<<(8*i-1)) | ~(-(1<<(8*i-1))))

#define __MAX_FREELIST_SIZE __MAX_VAL_OF_BYTES(__SLOT_INFO_BYTES)

// 保留一位用作内存数超出最大size的标志位
#define __MAX_BYTES ( (__MAX_FREELIST_SIZE - 1) * __ALIGN )

#define __FREELIST_SIZE (__MAX_BYTES) / (__ALIGN)

#define POOL_ROUND_UP(x) (((x) + __ALIGN - 1) & ~(__ALIGN - 1))
#define POOL_FREELIST_INDEX(x) (((x) + __ALIGN - 1) / __ALIGN - 1)

#define POOL_ATTACH_SLOT_INFO_SIZE(x) (x + __SLOT_INFO_BYTES)
#define POOL_DETACH_SLOT_INFO_SIZE(X) (x - __SLOT_INFO_BYTES)

#define POOL_EXPORT_POINTER(p) ((char *)p + __SLOT_INFO_BYTES)
#define POOL_RECOVER_POINTER(p) ((char *)p - __SLOT_INFO_BYTES)

#define pool(x) instance(x)

typedef union _pool_node 
{
	// 这个鬼指向下一个node
	union _pool_node *free_list_link;
	// 指向用户的可以使用的内存
	char client_data[1];
	//  保留一个字节做SLOT的info 
	unsigned char slot[__SLOT_INFO_BYTES];

} pool_node_t;

typedef struct _pool
{
	char *start_free;
	char *end_free;
	size_t heap_size;
	pool_node_t *volatile free_list[__FREELIST_SIZE];

} pool_t;

int alloc_init(pool_t *);
void *allocate(pool_t *, size_t n);
void deallocate(pool_t *, void *p);
pool_t *instance(int *);
void set_node_slot(pool_node_t* node, unsigned int);
unsigned int get_node_slot(pool_node_t* p);

#if ALLOC_DEBUG
void inspect_pool(pool_t *);
size_t size_of_slot(int slot);
#endif

#endif
