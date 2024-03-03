#include "allocator.h"

#include <string.h> //TODO in future rely on core/mem.h for memzero

void *AllocatorAllocNoZero(Allocator allocator, U64 size, AllocationError *error) {
  return allocator.func(allocator.ctx, AllocationKind_Alloc, size, 0, 0, error);
}

void *AllocatorAlloc(Allocator allocator, U64 size, AllocationError *error) {
  void* result = allocator.func(allocator.ctx, AllocationKind_Alloc, size, 0, 0, error);
  memset(result, 0, size);
  return result;
}

void *AllocatorResize(Allocator allocator, void *oldMemory, U64 oldSize, U64 newSize, AllocationError *error) {
  void *result = allocator.func(allocator.ctx, AllocationKind_Resize, newSize, oldMemory, oldSize, error);
  if (newSize > oldSize)
    memset((char*)oldMemory + oldSize, 0, newSize - newSize);

  return result;
}