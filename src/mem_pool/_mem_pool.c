/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-03 17:13:19
 * @LastEditTime: 2019-09-06 12:05:27
 * @LastEditors: Please set LastEditors
 */
#include <stdio.h>
#include <string.h>
#include "_mem_pool.h"

static int _refill(pool_t *palloc, size_t n);
static char *_chunk_alloc(pool_t *palloc, size_t size, int *nobjs);

// 全局的 pool变量。
static pool_t POOL_INSTANCE;

extern pool_t *instance(int *ret)
{

	ret ? *ret = 1 : 0;
	static pool_t *p_instance = NULL;
	if (p_instance == NULL)
	{
		ret ? *ret = 0 : 0;
		alloc_init(&POOL_INSTANCE);
		p_instance = &POOL_INSTANCE;
	}

	return p_instance;
}

extern int alloc_init(pool_t *palloc)
{
	memset(palloc->free_list, 0, sizeof(palloc->free_list));
	palloc->start_free = 0;
	palloc->end_free = 0;
	palloc->heap_size = 0;
	return 0;
}

extern void *allocate(pool_t *palloc, size_t x)
{
	// 多加一个info的空位放置块信息。
	//x += __NODE_INFO_BYTES;

	if ( POOL_FREELIST_INDEX(POOL_ATTACH_INFO_SIZE(x)) < POOL_FREELIST_SIZE)
	{

		pool_node_t *volatile *my_free_list;
		pool_node_t *result;

		my_free_list = palloc->free_list + POOL_FREELIST_INDEX(POOL_ATTACH_INFO_SIZE(x));
		result = *my_free_list;

		if (result == 0)
		{
			// 重新填充 free list
			return (_refill(palloc, POOL_ROUND_UP(POOL_ATTACH_INFO_SIZE(x))) == 0) ? allocate(palloc, x) : result;
		}
		else
		{
			// 把slot第一个指针指向下个块，这个块就返回出去。给用户用了
			*my_free_list = result->free_list_link;
			//result->slot = POOL_FREELIST_INDEX(POOL_ATTACH_INFO_SIZE(x));
			set_node_header_slot(result, POOL_FREELIST_INDEX(POOL_ATTACH_INFO_SIZE(x)));
			return POOL_EXPORT_POINTER(result);
		}
	}
	return NULL;
}

extern void deallocate(pool_t *palloc, void *p)
{
	pool_node_t *q = (pool_node_t *)POOL_RECOVER_POINTER(p);
	size_t slot = get_node_header_slot(q);
	if (slot < POOL_FREELIST_SIZE)
	{
		// 这里是头部插入。
		pool_node_t *volatile *my_free_list;
		my_free_list = palloc->free_list + slot;
		q->free_list_link = *my_free_list;
		*my_free_list = q;
	}
}

#if ALLOC_DEBUG
extern size_t freelist_size(pool_t *palloc, size_t n)
{
	pool_node_t *volatile *my_free_list = palloc->free_list + POOL_FREELIST_INDEX(n);
	pool_node_t *current_obj;
	current_obj = *my_free_list;
	size_t count = 0;
	while (0 != current_obj && current_obj->free_list_link != 0)
	{
		current_obj = current_obj->free_list_link;
		++count;
	}
	return count;
}

extern void inspect_pool(pool_t *pool)
{
	printf("\n***************** Inspect Pool ***********************\n");
	printf(" Pool Heap size : %d \n", pool->heap_size);
	printf(" Pool size : %d \n", (pool->end_free - pool->start_free));
	printf(" Pool start at : %p \n", pool->start_free);
	printf(" Pool end at : %p \n", pool->end_free);
	printf("\n\n");
	printf("----------------- Inspect Free List -----------------\n\n");
	int i;
	for (i = 0; i < POOL_FREELIST_SIZE; ++i)
	{
		pool_node_t *volatile *my_free_list = pool->free_list + i;
		pool_node_t *first = *my_free_list;
		if (first)
		{
			printf("------------- slot %02d for size %d --------------\n", i, size_of_slot(i));
			int j = 0;
			for (j = 0, first; first != 0; first = first->free_list_link, ++j)
			{
				printf(" %d node at %p\n", j, first);
			}
			printf(" slot %02d has %d nodes\n\n ", i, j);
		}
	}
	printf("\n*********************************************************\n");
}

extern size_t size_of_slot(int slot)
{
	return (slot + 1) * __ALIGN;
}
#endif

extern void set_node_slot(pool_node_t* p, unsigned int slot)
{
	
	for (int i=__SLOT_INFO_BYTES-1, j=0; i>=0; --i, ++j) 
	{
		p->slot[i] = (unsigned char)(slot>>j*8);
	}
	return;
}

extern unsigned int get_node_slot(pool_node_t* p){
	unsigned int slot = 0;
	for (int i=0,j=__SLOT_INFO_BYTES-1; i<__SLOT_INFO_BYTES; ++i, --j) 
	{
		slot |= (unsigned int)(p->slot[i]<<j*8);
	}
	return slot;
}

static int _refill(pool_t *palloc, size_t n)
{
	int nobjs = __REFILL_CHUNK_SIZE;

	// chunk 是 nobjs 个大小为 n 的block。
	// _chunk_alloc 后返回 nobjs 是获得块的个数。

	char *chunk = _chunk_alloc(palloc, n, &nobjs);
	if (0 == chunk)
	{
		// 拿不到任何内存
		return -1;
	}

	pool_node_t *volatile *my_free_list;
	pool_node_t *current_obj;
	pool_node_t *next_obj;
	my_free_list = palloc->free_list + POOL_FREELIST_INDEX(n);

	// 直接切豆腐，放入对应的篮中
	*my_free_list = next_obj = (pool_node_t *)chunk;

	// 拿到的chunk开始切豆腐。切成对应的solt大小的快编入连表中。
	int i;
	for (i = 1; i <= nobjs; ++i)
	{
		current_obj = next_obj;
		// next_obj + n 是指将一个块完整的内存块，每个size个大小就切开来。
		//  这个n 可能是 8 16 24 32 。。。128
		next_obj = (pool_node_t *)((char *)next_obj + n);
		if (nobjs == i)
		{
			// 最后一块，尾巴收0
			current_obj->free_list_link = 0;
			break;
		}
		else
		{
			current_obj->free_list_link = next_obj;
		}
	}
	return (0);
}

/**
 *  整个思路就是
 *  1 看看mempool 中有没有适合的内存块，有即返回
 *  2 没有即给自己的内存池加水，加完了，递归调用自己看看mempool够不够返回，
 *  3 若是向系统申请失败了，内存没有内存了。向其他freelist借，有即将freelist的node还给mempool
 *  4 再递归调用自己看看内存池还有没有。
 */

static char *_chunk_alloc(pool_t *palloc, size_t size, int *nobjs)
{
	char *result;
	size_t total_bytes = size * (*nobjs);
	size_t bytes_left = palloc->end_free - palloc->start_free;

	if (bytes_left >= total_bytes)
	{
		// bytes_left 比中共要申请的内存都多。
		result = palloc->start_free;
		palloc->start_free = palloc->start_free + total_bytes;
		return (result);
	}
	else if (bytes_left > size)
	{
		// bytes_left > size  && < total_bytes
		// 这里计算一下能够给出多少个obj
		*nobjs = bytes_left / size;
		total_bytes = size * (*nobjs);
		result = palloc->start_free;
		palloc->start_free += total_bytes;
		return (result);
	}
	else
	{
		// 水池剩下的内存比一块size的都要少。
		size_t bytes_to_get = 2 * total_bytes + POOL_ROUND_UP(palloc->heap_size >> 4);

		// 着堆代码是什么鬼意思呢
		if (bytes_left > 0)
		{
			// 这里butes_left最小的值都为8。因为上面的申请是以8的倍数申请的。
			// 然后以8的倍数减去的。
			// 所以插回去是不用害怕的。

			// my_free_list是第 FREELIST_INDEX(bytes_left)个槽的指向第一个块的指针。
			// 这里注意要将期编入free list

			pool_node_t *volatile *my_free_list = palloc->free_list + POOL_FREELIST_INDEX(bytes_left);

			// 分析说明：
			// 1 ((pool_node_t *) (palloc->start_free)) 这个其实就是将水池剩下的chunk变成(pool_node_t)
			// TODO: 在每个内存快的头加入slot的信息，说明是第几个块的。

			// 2 *my_free_list 原来是第一个 pool_node_t 对象的。现在赋值给新来的 chunk了。
			// 也就是新来的chunk的next指针(free_list_link) 指向了原来旧的chunk
			((pool_node_t *)(palloc->start_free))->free_list_link = *my_free_list;

			// 2 *my_free_list 的值改变了。变成了指向这个新来的chunk了。
			// 结论：将新来的chunk插在对应的slot的freelist的头部。
			*my_free_list = (pool_node_t *)(palloc->start_free);
		}
		// 收编完了就开始向系统申请加水，将水加在内存池里面。然后再递归调用。返回适合的chunk

		palloc->start_free = (char *)malloc(bytes_to_get);

		if (0 == palloc->start_free)
		{
			// 当想系统申请内存失败的时候，将freelist其他还未用的内存拿回来，然后看看能不能组成一块，返回给用户。
			int i;
			pool_node_t *volatile *my_free_list, *p;
			for (i = size; i < __MAX_BYTES; i += __ALIGN)
			{
				my_free_list = palloc->free_list + POOL_FREELIST_INDEX(i);
				p = *my_free_list;
				// 以下代码其实跟allocate中 free_list 不为0时返回的结果一样。
				// 但是这里是当前的slot没有的话就去找下一个更加大的slot，
				// 将下一个slot放入内存池中。然后在使用内存池到free_list的算法生成适合的freelist。
				if (0 != p)
				{
					// my_free_list 值向下一个这个，当前这个被归入内存池中。
					*my_free_list = p->free_list_link;
					palloc->start_free = (char *)p;
					palloc->end_free = palloc->start_free + i;
					// 释放完了，继续调用自己看看，mem pool 里面够不够内存返回。
					return (_chunk_alloc(palloc, size, nobjs));
				}
			}
			//到了这里一点内存也没有了。只能返回空null
			palloc->end_free = 0;
			return (char *)0;
		}

		// 申请到内存,下次多申请一点
		palloc->heap_size += bytes_to_get;
		palloc->end_free = palloc->start_free + bytes_to_get;
		return (_chunk_alloc(palloc, size, nobjs));
	}
}
