#include <stdio.h>

int atomic_xchg(volatile int *addr, int newval) {
  int result;
  asm volatile ("lock xchg %0, %1":
    "+m"(*addr), "=a"(result) : "1"(newval) : "memory");
  return result;
}

void putch(char ch) {
  putchar(ch);
}

int cpu_current(void) {
  return 0;
}