#ifndef CORE_MEM_H
#define CORE_MEM_H

#include "types.h"

#define CoreSimpleFn static inline
#define CoreFn       static

CoreSimpleFn U64 U64AlignBackward(U64 x, U64 align) {
  return x & ~(align - 1);
}

CoreSimpleFn U64 U64AlignForward(U64 x, U64 align) {
  return U64AlignBackward(x + (align - 1), align);
} 

CoreSimpleFn void MemZero(void *ptr, U64 size) {
  char *p = (char*)ptr;
  while (p < p + size) *p++ = 0;
}
#endif