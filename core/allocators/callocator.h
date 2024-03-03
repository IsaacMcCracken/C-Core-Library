#ifndef CALLOCATOR_H
#define CALLOCATOR_H

#include "../allocator.h"

Allocator CAllocatorInit(void); // change this to CAllocator(void)

void *CAllocatorFn(
  void *ctx,
  AllocationKind allocKind, 
  U64  size,
  void *oldMemory, 
  U64 oldSize,
  AllocationError *error
);

#endif