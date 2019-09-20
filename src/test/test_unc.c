/*
 * @Description: test case for unc
 * @Author: your name
 * @Date: 2019-09-04 10:43:36
 * @LastEditTime: 2019-09-20 19:49:25
 * @LastEditors: Please set LastEditors
 */
#include <stdio.h>
#include <CUnit/Basic.h>
#include "_mem_pool.h"
#include "__type_value.h"
#include "__vector.h"
#include "__list.h"
#include "__rb_tree.h"

#define TEST_DATA_SIZE 10000

int suite_success_init(void) {
    return 0;
}

int suite_success_clean(void) {
    return 0;
}

static type_value_t test_data[TEST_DATA_SIZE];

static void init_test_data()
{
    for(int i=0; i<TEST_DATA_SIZE; ++i) {
        test_data[i] = int_type(rand() % 100000);
    }
    return;
}
static type_value_t get(int i) {
    return test_data[i];
}
void
test_mem_instance(void) {
    int ret = 0;
    pool_t * alloc = pool(&ret);
    CU_ASSERT(ret == 0);
    alloc = pool(&ret);
    CU_ASSERT(ret == 1);
}

void 
test_mem_attr(void) {
    CU_ASSERT(__FREELIST_SIZE == 16);

    printf("%d", __FREELIST_SIZE);
    printf("\n%d\n", POOL_ROUND_UP(9));
    printf("%d\n", POOL_ROUND_UP(97));
    printf("%d\n", POOL_ROUND_UP(3399));

    printf("\n%d\n", sizeof(char));
    printf("%d\n", sizeof(int));
    printf("%d\n", sizeof(float));
    
    printf("------------free-index--------------------\n");
    printf("%d\n", POOL_FREELIST_INDEX(1));
    printf("%d\n", POOL_FREELIST_INDEX(2));
    printf("%d\n", POOL_FREELIST_INDEX(8));
    printf("%d\n", POOL_FREELIST_INDEX(9));
    printf("%d\n", POOL_FREELIST_INDEX(16));
    printf("%d\n", POOL_FREELIST_INDEX(17));
    printf("%d\n", POOL_FREELIST_INDEX(23));
    printf("%d\n", POOL_FREELIST_INDEX(24));
    printf("%d\n", POOL_FREELIST_INDEX(27));
    printf("%d\n", POOL_FREELIST_INDEX(28));
    printf("%d\n", POOL_FREELIST_INDEX(30));
    printf("%d\n", POOL_FREELIST_INDEX(32));
    printf("%d\n", POOL_FREELIST_INDEX(39));
    printf("%d\n", POOL_FREELIST_INDEX(128));
    CU_ASSERT(POOL_ROUND_UP(19) == 24);
}

void test_mem_pool_inspect (void) {
    // 这个他妈的是戏肉啊。
    CU_ASSERT(1);
    pool_t pool;
    alloc_init(&pool);
    //inspect_pool(&pool);
    // char* test1 = allocate(&pool, 25);
    // char* test2 = allocate(&pool, 8);
    // char* test3 = allocate(&pool, 9);
    // char* test4 = allocate(&pool, 17);
    // char* test5 = allocate(&pool, 25);
    // char* test6 = allocate(&pool, 33);
    char* test7 = allocate(&pool, 2031);
    inspect_pool(&pool);

    // memset(test1, 0, 25);
    // memset(test2, 0, 8);
    // memset(test3, 0, 9);
    // memset(test4, 0, 17);
    // memset(test5, 0, 25);
    // memset(test6,0, 33);

    // deallocate(&pool, test1);
    // deallocate(&pool, test2);
    // deallocate(&pool, test3);
    // deallocate(&pool, test4);
    // deallocate(&pool, test5);
    // deallocate(&pool, test6);
    deallocate(&pool, test7);
    inspect_pool(&pool);
}

void 
test_mem_pool_maxslot (void)
{
    CU_ASSERT(1);
    printf("\n%ld\n", (unsigned int)__MAX_FREELIST_SIZE);
}

void test_vector (void) {
    vector_t vet;
    init_vector(&vet);
    

    for(int i=0; i<2; ++i) {
        container_insert(&vet, container_first(&vet), int_type((i+1)*10));
    }
    
    iterator_t first = container_first( &vet );
    iterator_t tail = iterator_next( container_last(&vet) );

    for(; !iterator_equal(first, tail); first = iterator_next(first)) {
        int v = type_int( iterator_dereference(first) );
        printf("\n %d \n", v);
    }
    
    CU_ASSERT(1);
}

void test_list (void) {
    list_t list;
    init_list(&list);
    for(int i=0; i<10; ++i) {
        container_insert(&list, container_first(&list), float_type(i*(-0.01)));
    }

    iterator_t tail = container_tail(&list);
    iterator_t first = container_first( &list );
    
    for(; !iterator_equal(first, tail); first = iterator_next(first)) {
        float fv = type_float( iterator_dereference(first) );
        printf("\n %f \n", fv);
    }

    iterator_t head = container_head(&list);
    iterator_t last = container_last(&list);

    for(;!iterator_equal(last, head); last = iterator_prev(last)) 
    {
        float fv = type_float( iterator_dereference(last) );
        printf("\n %f \n", fv);
    }
    CU_ASSERT(1);
}

void test_rb_tree(void) 
{
    rb_tree_t rbtree;
    init_rb_tree(&rbtree, compare_int);
    for(int i=0; i<TEST_DATA_SIZE; ++i) {
        container_insert(&rbtree, rb_tree_null(&rbtree), get(i));
    }

    /** 展示 **/
    printf("\n size of tree: %d ", rbtree._size);
    iterator_t first = container_first(&rbtree);
    iterator_t tail = iterator_next( container_last(&rbtree) );
    for(;!iterator_equal(first, tail); first = iterator_next(first))
    {
        int v = type_int( iterator_dereference(first) );
        printf("\n %d \n", v);
    }

    /** 删除 **/
    for(int i=0; i<TEST_DATA_SIZE/2; ++i) {
        
        iterator_t pos = container_find(&rbtree, get(i), compare_int);

        int data =  container_remove(&rbtree, pos, NULL);
        
        printf("\n delete %d \n", data);

    }

    /** 展示 **/
    printf("\n size of tree: %d ", rbtree._size);
    first = container_first(&rbtree);
    tail = iterator_next( container_last(&rbtree) );
    for(;!iterator_equal(first, tail); first = iterator_next(first))
    {
        int v = type_int( iterator_dereference(first) );
        printf("\n %d \n", v);
    }

    CU_ASSERT(1);
}

int main () 
{
    printf("test unc what ");
    init_test_data();

    CU_pSuite pSuite = NULL;
    if (CUE_SUCCESS != CU_initialize_registry()){
	    return CU_get_error();
    }

    pSuite = CU_add_suite("test_mem_pool", suite_success_init, suite_success_clean);

    if (NULL == pSuite){
      CU_cleanup_registry();
      return CU_get_error();
    } 

    
    /*
    if (NULL == CU_add_test(pSuite, "test_vector", test_vector) ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    */

    if (NULL == CU_add_test(pSuite, "test_rb_tree", test_rb_tree) ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /*
    if (NULL == CU_add_test(pSuite, "test_list", test_list) ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    */
    /*
    if (NULL == CU_add_test(pSuite, "test_mem_pool_maxslot", test_mem_pool_maxslot) ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    */
    /*
    if (NULL == CU_add_test(pSuite, "test_mem_pool_inspect", test_mem_pool_inspect) ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    */
    /* 
    if (NULL == CU_add_test(pSuite, "test_mem_instance", test_mem_instance) ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "test_mem_attr", test_mem_attr)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    */
   
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}