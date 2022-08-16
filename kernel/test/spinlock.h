// spinlock
#ifndef SPINLOCK_H__
#define SPINLOCK_H__

#include <am.h>
#include <stdint.h>
typedef int spinlock_t;
#define SPIN_INIT() 0

void spin_lock(spinlock_t *lk);

void spin_unlock(spinlock_t *lk);

#endif