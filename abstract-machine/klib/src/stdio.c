#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>


#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

static void printint(int xx, int base, int sgn)
{
  static char digits[] = "0123456789ABCDEF";
  char buf[16];
  int i, neg;
  unsigned int x;

  neg = 0;
  if(sgn && xx < 0){
    neg = 1;
    x = -xx;
  } else {
    x = xx;
  }

  i = 0;
  do{
    buf[i++] = digits[x % base];
  }while((x /= base) != 0);
  if(neg)
    buf[i++] = '-';

  while(--i >= 0)
    putch(buf[i]);
}

int printf(const char *fmt, ...) {
  char *s;
  int c, i, state;
  va_list ap;

  state = 0;
  va_start(ap, fmt);
  for(i = 0; fmt[i]; i++){
    c = fmt[i] & 0xff;
    if(state == 0){
      if(c == '%'){
        state = '%';
      } else {
        putch(c);
      }
    } else if(state == '%'){
      if(c == 'd'){
        printint(va_arg(ap, int), 10, 1);
      } else if(c == 'x' || c == 'p'){
        printint(va_arg(ap, int), 16, 0);
      } else if(c == 's'){
        s = va_arg(ap, char *);
        if(s == 0)
          s = "(null)";
        while(*s != 0){
          putch(*s);
          s++;
        }
      } else if(c == 'c'){
        putch(va_arg(ap, int));
      } else if(c == '%'){
        putch(c);
      } else {
        // Unknown % sequence.  Print it to draw attention.
        putch('%');
        putch(c);
      }
      state = 0;
    }
  }
  return 0;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  panic("Not implemented");
}

int sprintf(char *out, const char *fmt, ...) {
  panic("Not implemented");
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
