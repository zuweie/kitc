/*
 * @Description: test case for unc
 * @Author: your name
 * @Date: 2019-09-04 10:43:36
 * @LastEditTime: 2020-06-02 15:33:24
 * @LastEditors: Please set LastEditors
 */
#include <stdio.h>
#include <CUnit/Basic.h>
#include "__mem_pool.h"
#include "__type_value.h"
#include "__vector.h"
#include "__list.h"
#include "__rb_tree.h"
#include "__sort.h"
#include "set.h"

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
/*
void
test_mem_instance(void) {
    int ret = 0;
    pool_t * alloc = g_pool(&ret);
    CU_ASSERT(ret == 0);
    alloc = g_pool(&ret);
    CU_ASSERT(ret == 1);
}
*/
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
    pool_t* pool = alloc_create(0);
    //alloc_init(&pool);
    //inspect_pool(&pool);
    // char* test1 = allocate(&pool, 25);
    // char* test2 = allocate(&pool, 8);
    // char* test3 = allocate(&pool, 9);
    // char* test4 = allocate(&pool, 17);
    // char* test5 = allocate(&pool, 25);
    // char* test6 = allocate(&pool, 33);
    char* test7 = allocate(pool, 2031);
    inspect_pool(pool);

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
    deallocate(pool, test7);
    inspect_pool(pool);
    alloc_destroy(pool);
}

void 
test_mem_pool_maxslot (void)
{
    CU_ASSERT(1);
    printf("\n%ld\n", (unsigned int)__MAX_FREELIST_SIZE);
}

void test_vector (void) {
    vector_t* vet = container_create(vector);

    container_insert(vet, container_tail(vet), int_type(1));
    container_insert(vet, container_tail(vet), int_type(2));
    
    for(iterator_t first = container_first(vet); 
        !iterator_equal(first, container_tail(vet)); 
        first=iterator_next(first)) {

            printf("%d ", type_int(iterator_dereference(first)));

    }
    
    printf("\n***********************\n");
    
    container_insert_find(vet, int_type(2), int_type(3), compare_int);
    container_insert_find(vet, int_type(3), int_type(4), compare_int);
    container_insert_find(vet, int_type(5), int_type(9), compare_int);
    container_insert_find(vet, int_type(78), int_type(3), compare_int);
    for(iterator_t first = container_first(vet); 
        !iterator_equal(first, container_tail(vet)); 
        first=iterator_next(first)) {

            printf("%d ", type_int(iterator_dereference(first)));

    }
    printf("\n***********************\n");
    int result = container_remove(vet, container_tail(vet), NULL);
    
    
    for(iterator_t first = container_first(vet); 
        !iterator_equal(first, container_tail(vet)); 
        first=iterator_next(first)) {

            printf("%d ", type_int(iterator_dereference(first)));

    }

    CU_ASSERT((result == -1));
    printf("\n***********************\n");
    result = container_remove_find(vet, int_type(3), NULL, compare_int);
    for(iterator_t first = container_first(vet); 
        !iterator_equal(first, container_tail(vet)); 
        first=iterator_next(first)) {

            printf("%d ", type_int(iterator_dereference(first)));

    }
    CU_ASSERT((result == 0));
    printf("\n***********************\n");
    result = container_remove_find(vet, int_type(10), NULL, compare_int);
    for(iterator_t first = container_first(vet); 
        !iterator_equal(first, container_tail(vet)); 
        first=iterator_next(first)) {

            printf("%d ", type_int(iterator_dereference(first)));

    }
    container_destroy(vector, vet);
    CU_ASSERT((result == 0));

}

void test_list (void) {

    list_t* list = container_create(list);
    //init_list(list, g_pool(0));

    printf("\n********** size fo type_value_t %d *********************\n", sizeof(type_value_t));

    for(int i=0; i<40; ++i) {
        container_insert(list, container_first(list), get(i));
    }

    iterator_t tail = container_tail(list);
    iterator_t first = container_first(list);
    
    printf("\n********* before sort ***********\n");
    for(; !iterator_equal(first, tail); first = iterator_next(first)) {
        int v = type_int( iterator_dereference(first) );
        printf("%d ", v);
    }

    //quick_sort(container_first(list), container_last(list), compare_int);
    container_sort(list, compare_int);
    
    tail = container_tail(list);
    first = container_first(list);
    printf("\n******** after sort ***************\n");
    for(; !iterator_equal(first, tail); first = iterator_next(first)) {
        int v = type_int( iterator_dereference(first) );
        printf("%d ", v);
    }
    printf("\n************ inspact pool *******************\n");
    inspect_pool(container_mem_pool(list));
    
    container_destroy(list, list);
    CU_ASSERT(1);
}

void test_rb_tree(void) 
{
    rb_tree_t* rbtree = container_create(rb_tree, compare_int);
    
    //init_rb_tree(rbtree, compare_int, g_pool(0));
    for(int i=0; i<TEST_DATA_SIZE; ++i) {
        container_insert(rbtree, rb_tree_null(rbtree), get(i));
    }

    /** 展示 **/
    printf("\n size of tree: %d ", rbtree->_size);
    iterator_t first = container_first(rbtree);
    iterator_t tail = iterator_next( container_last(rbtree) );
    for(;!iterator_equal(first, tail); first = iterator_next(first))
    {
        int v = type_int( iterator_dereference(first) );
        printf("\n %d \n", v);
    }

    /** 删除 **/
    for(int i=0; i<TEST_DATA_SIZE/2; ++i) {
        
        iterator_t pos = container_find(rbtree, get(i), compare_int);

        int data =  container_remove(rbtree, pos, NULL);
        
        printf("\n delete %d \n", data);

    }

    /** 展示 **/
    printf("\n size of tree: %d ", container_size(rbtree));
    first = container_first(rbtree);
    tail = iterator_next( container_last(rbtree) );
    for(;!iterator_equal(first, tail); first = iterator_next(first))
    {
        int v = type_int( iterator_dereference(first) );
        printf("\n %d \n", v);
    }
    container_destroy(rb_tree, rbtree);
    CU_ASSERT(1);
}

void test_set(void) {
    /*
    set_t set;
    init_set(&set, compare_int);

    for(int i=0; i<10; ++i) {
        if (con_ins_first(&set, get(i)) == 0) {
            printf(" insert %d into set \n", type_int(get(i)));
        }else{
            printf(" insert %d fail \n", type_int(get(i)));
        }
    }    

    printf("*************** print set memebers ****************************\n");

    for(iterator_t it = con_first(&set); !iterator_equal(it, con_last(&set)); it = iterator_next(it)) {
        printf(" %d \n", type_int(iterator_dereference(it)));
    }
    
    type_value_t rdata;
    printf("removing %d \n", type_int(get(1)));
    con_rm_find(&set, get(1), &rdata);
    printf("removed %d \n", type_int(rdata));

    printf("removing %d \n", type_int(get(3)));
    con_rm_find(&set, get(3), &rdata);
    printf("removed %d \n", type_int(rdata));

    printf("removing %d \n", type_int(get(7)));
    con_rm_find(&set, get(7), &rdata);
    printf("removed %d \n", type_int(rdata));
    
    
    printf("removing %d \n", type_int(get(9)));
    con_rm_find(&set, get(9), &rdata);
    printf("removed %d \n", type_int(rdata));
    
    printf("*************** print set memebers 2 ****************************\n");

    for(iterator_t it = con_first(&set); !iterator_equal(it, con_last(&set)); it = iterator_next(it)) {
        printf(" %d \n", type_int(iterator_dereference(it)));
    }
    */
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
    /*
    if (NULL == CU_add_test(pSuite, "test_rb_tree", test_rb_tree) ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    */
    /*
    if (NULL == CU_add_test(pSuite, "test_set", test_set) ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    */
    
    if (NULL == CU_add_test(pSuite, "test_list", test_list) ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
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