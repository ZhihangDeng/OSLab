#ifndef PMM_H__
#define PMM_H__

#include <spinlock.h>

#define KiB       *1024
#define MiB       *1024 KiB
/* 每页设定为8KiB，页的头部具有256B元数据 */
#define HDR_SIZE  256
#define PAGE_SIZE (8 KiB)
#define HEAP_SIZE  (125 MiB)
#define PAGE_NUM  HEAP_SIZE/PAGE_SIZE    // 共16000页
/* 设定10种类型的slab */
#define SLAB_TYPE_NUM 10

typedef struct list_head {
    struct list_head *prev, *next;
}list_head;

/* 将进程地址空间以页为单位划分 */
typedef union page {
    /* 作为一块slab时，必须具有以下元数据 */
    struct {
        spinlock_t lk;  // 锁，用于串行化分配和并发的free
        int obj_cnt;    // 页面中已分配的对象数，减少到0时回收页面
        list_head list; // 属于同一个线程的缓存页面的链表
        int slab_size;  // 这一块缓存页面用于分配多大的slab
        uint8_t bitmap[128];
    };

    /* 通过以下结构体将page_t撑开 */
    struct {
        uint8_t header[HDR_SIZE];           // HDR_SIZE 256
        uint8_t data[PAGE_SIZE - HDR_SIZE]; // PAGE_SIZE - HDR_SIZE
    } __attribute__((packed));
} page_t;

/* 每个线程(CPU)具有独立的缓存 */
typedef struct kmem_cache {
    int cpu;
    list_head slab_list[SLAB_TYPE_NUM];     // 一共 SLAB_TYPE_NUM 个slabs
    list_head *freepage[SLAB_TYPE_NUM];     // 指向每个slab_list中具有空闲对象的page
}kmem_cache;

page_t *get_free_page(int num, int slab_size, int cpu);
void put_free_page(list_head *list, int num);

#endif
