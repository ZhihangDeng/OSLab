#include <kernel.h>
#include <thread.h>

#include <pmm.h>

static void entry(int tid) { pmm->alloc(128); }
static void goodbye()      { printf("End.\n"); }

int main() {
  pmm->init();
  // for (int i = 0; i < 4; i++)
  //   create(entry);
  page_t *page = get_free_page(15999, 8, 0);
  printf("在 %p 得到page, slab大小为 %d.\n", page, page->slab_size);
  page_t *page_1 = get_free_page(2, 8, 0);
  printf("在 %p 得到page, slab大小为 %d.\n", page_1, page_1->slab_size);
  
  join(goodbye);
}