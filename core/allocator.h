#ifndef CORE_ALLOCATOR_H
#define CORE_ALLOCATOR_H


#include "types.h"


typedef U8 AllocationKind;
enum {
  AllocationKind_Alloc,
  AllocationKind_Resize,
  AllocationKind_Free,
  AllocationKind_FreeAll,
};

typedef U8 AllocationError;
enum {
  AllocationError_None,
  AllocationError_OutOfMemory,
  AllocationError_NotImplemented
};


typedef void *(*AllocatorFn)(
  void *ctx,
  AllocationKind allocKind, 
  U64  size,
  void *oldMemory, 
  U64 oldSize,
  AllocationError *error
);


typedef struct Allocator Allocator;
struct Allocator {
  AllocatorFn func;
  void *ctx;
};


void *AllocatorAllocNoZero(Allocator allocator, U64 size, AllocationError *error);
void *AllocatorAlloc(Allocator allocator, U64 size, AllocationError *error);
void *AllocatorResize(Allocator allocator, void *oldMemory, U64 oldSize, U64 newSize, AllocationError *error)

#define Create(allocator, type, error) (type*)AllocatorAlloc(allocator, sizeof(type), error)
#define CreateNoZero(allocator, type, error) (type*)AllocatorAllocNoZero(allocator, sizeof(type), error)
#define Alloc(allocator, type, count, error) (type*)AllocatorAlloc(allocator, sizeof(type) * (count), error)
#define AllocNoZero(allocator, type, count, error) (type*)AllocatorAllocNoZero(allocator, sizeof(type) * (count), error)
#define Resize(allocator, type, oldMemory, oldSize, newSize, error) (type*)AllocatorResize(allocator, oldMemory, sizeof(type)*(oldSize), sizeof(type)*newSize, error)

#endif // CORE_ALLOCATOR_H