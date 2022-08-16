#include <am.h>

#define MODULE(mod) \
  typedef struct mod_##mod##_t mod_##mod##_t; \
  extern mod_##mod##_t *mod; \
  struct mod_##mod##_t

#define MODULE_DEF(mod) \
  extern mod_##mod##_t __##mod##_obj; \
  mod_##mod##_t *mod = &__##mod##_obj; \
  mod_##mod##_t __##mod##_obj


/* os模块声明
 * typedef struct mod_os_t mod_os_t; 
 * extern mod_os_t *os; 
 * struct mod_os_t {
 *  void (*init)();
 *  void (*run)();
 * };
*/
MODULE(os) {
  void (*init)();
  void (*run)();
};
/* pmm模块声明
 * typedef struct mod_pmm_t mod_pmm_t; 
 * extern mod_pmm_t *pmm; 
 * struct mod_pmm_t {
 *  void (*init)();
 *  void *(*alloc)(size_t size);
 *  void (*free)(void *ptr);
 * }; 
*/
MODULE(pmm) {
  void  (*init)();
  void *(*alloc)(size_t size);
  void  (*free)(void *ptr);
};
