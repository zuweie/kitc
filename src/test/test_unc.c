/*
 * @Description: test case for unc
 * @Author: your name
 * @Date: 2019-09-04 10:43:36
 * @LastEditTime: 2019-09-06 08:22:55
 * @LastEditors: Please set LastEditors
 */
#include <stdio.h>
#include <CUnit/Basic.h>
#include <_mem_pool.h>

int suite_success_init(void) {
    return 0;
}

int suite_success_clean(void) {
    return 0;
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
    CU_ASSERT(POOL_FREELIST_SIZE == 16);

    printf("%d", POOL_FREELIST_SIZE);
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
    char* test1 = allocate(&pool, 25);
    char* test2 = allocate(&pool, 8);
    char* test3 = allocate(&pool, 9);
    char* test4 = allocate(&pool, 17);
    char* test5 = allocate(&pool, 25);
    char* test6 = allocate(&pool, 33);
    
    inspect_pool(&pool);

    memset(test1, 0, 25);
    memset(test2, 0, 8);
    memset(test3, 0, 9);
    memset(test4, 0, 17);
    memset(test5, 0, 25);
    memset(test6,0, 33);

    deallocate(&pool, test1);
    deallocate(&pool, test2);
    deallocate(&pool, test3);
    deallocate(&pool, test4);
    deallocate(&pool, test5);
    deallocate(&pool, test6);
    inspect_pool(&pool);
}

int main () 
{
    printf("test unc what ");
    

    CU_pSuite pSuite = NULL;
    if (CUE_SUCCESS != CU_initialize_registry()){
	    return CU_get_error();
    }

    pSuite = CU_add_suite("test_mem_pool", suite_success_init, suite_success_clean);

    if (NULL == pSuite){
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "test_mem_pool_inspect", test_mem_pool_inspect) ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

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