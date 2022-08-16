#ifndef AM_H__
#define AM_H__
#include <stddef.h>

typedef struct {
	void *start, *end;
} Area;
Area heap;

int atomic_xchg(volatile int *addr, int newval);

void putch(char ch);

int cpu_current(void);

#endif