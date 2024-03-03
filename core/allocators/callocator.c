#include "callocator.h"

#include <stdlib.h>

Allocator CAllocatorInit(void) {
  Allocator allocator = {.ctx = NULL, .func = CAllocatorFn};
  return allocator;
}

void *CAllocatorFn(
  void *ctx,
  AllocationKind allocKind, 
  U64  size,
  void *oldMemory, 
  U64 oldSize,
  AllocationError *error
) {
  switch (allocKind) {
    case AllocationKind_Alloc: {
      void *result = malloc(size);
      if (error) {
        if (result) *error = AllocationError_None;
        else *error = AllocationError_OutOfMemory;
      } 
      return result;
      
    } break;
    
    case AllocationKind_Resize: {
      void *result = realloc(oldMemory, size);
      if (error) {
        if (result) *error = AllocationError_None;
        else *error = AllocationError_OutOfMemory;
      } 
      return result;
    } break;
    
    case AllocationKind_Free: {
      free(oldMemory);
      if (error) *error = AllocationError_None;

    } break;

    case AllocationKind_FreeAll:
      break;
    
    default: {

      if (error) *error = AllocationError_NotImplemented;
      return NULL;
    } break;
  }

  return NULL;
}