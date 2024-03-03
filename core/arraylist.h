#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "allocator.h"

typedef struct ArrayList ArrayList;
struct ArrayList {
  U64 capacity;
  U64 len;
  U64 size;
  Allocator allocator;
};


void *ArrayListInit(Allocator allocator, U64 capacity);
U64 ArrayListLen(void *array);
U64 ArrayListCapacity(void *array);
B32 ArrayListAppendBytes(void *array, U64 size);

#define ArrayListAppend(array, item)  



#endif