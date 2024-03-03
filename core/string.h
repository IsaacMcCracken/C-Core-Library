#ifndef STRING_H
#define STRING_H

#include "allocator.h"

typedef struct String String;
struct String {
  U8 *ptr;
  U64 len;
};

typedef struct StringNode StringNode;
struct StringNode {
  String str;
  StringNode *next;
};

typedef struct StringList StringList;
struct StringList {
  StringNode *first;
  StringNode *last;
  U64 len;
};






#endif