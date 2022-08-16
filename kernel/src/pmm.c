#include <common.h>
#include <pmm.h>

const int SLAB_TYPE[SLAB_TYPE_NUM] = {8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096};
/* 进程地址空间的全局大锁 */
spinlock_t global_lk;
/* 从进程地址空间取空闲页 */
page_t *get_free_page(int num, int slab_size, int cpu) {
  spin_lock(&global_lk);
  page_t *new_page = (page_t *)heap.start;
  page_t *first_page = NULL;
  int i = 0;
  while((uintptr_t)new_page != (uintptr_t)heap.end && i < num) {
      if(new_page->slab_size > 0) {
          new_page++;
          continue;
      }
      /* 初始化新页 */
      new_page->lk = SPIN_INIT();
      new_page->list.next = NULL;
      new_page->list.prev = NULL;
      new_page->obj_cnt = 0;
      new_page->slab_size = slab_size;

      if(first_page == NULL)      // 新页直接作为第一页
          first_page = new_page;
      else {                      // 新页采用头插法插入
          new_page->list.next = &first_page->list;
          first_page->list.prev = &new_page->list;
          first_page = new_page;
      }
      new_page++;
      i++;
  }
  spin_unlock(&global_lk);
  if((uintptr_t)new_page == (uintptr_t)heap.end && i < num) {
      printf("需要申请 %d 张新页, 但只找到 %d 张空闲页, 返回NULL\n", num, i);
      return NULL;
  }
  return first_page;
}
/* 得到链表节点入口 */
static inline page_t *get_list_entry(list_head *list) {
  return (page_t *)((intptr_t)list - (uintptr_t)(&((page_t *)0)->list));
}
/* 将空闲页放回进程地址空间 */
void put_free_page(list_head *list, int num) {
  spin_lock(&global_lk);
  
  spin_unlock(&global_lk);
}

static void *kalloc(size_t size) {
  return NULL;
}

static void kfree(void *ptr) {
}

#ifndef TEST
// 框架代码中的 pmm_init (在 AbstractMachine 中运行)
static void pmm_init() {
  uintptr_t pmsize = ((uintptr_t)heap.end - (uintptr_t)heap.start);
  printf("Got %d MiB heap: [%p, %p)\n", pmsize >> 20, heap.start, heap.end);
}
#else
// 测试代码的 pmm_init ()
static void pmm_init() {
  char *ptr  = malloc(HEAP_SIZE);
  heap.start = ptr;
  heap.end   = ptr + HEAP_SIZE;
  printf("Got %d MiB heap: [%p, %p)\n", HEAP_SIZE >> 20, heap.start, heap.end);
}
#endif

MODULE_DEF(pmm) = {
  .init  = pmm_init,
  .alloc = kalloc,
  .free  = kfree,
};

