#include "parser.h"


TokenList *TokenListInit(Allocator allocator, U64 capacity) {
  TokenList *list = Create(allocator, TokenList, NULL);
  list->tokens = Alloc(allocator, Token, capacity, NULL);
  list->allocator = allocator;
  list->capacity = capacity;
  
  return list;
}

void TokenListAppend(TokenList *list, TokenKind kind, Index start, Index end) {
  if (list->size + 1 > list->capacity) {
    list->tokens = Resize(list->allocator, Token, list->tokens, list->capacity, list->capacity * 2, NULL);
  }

  list->tokens[list->size] = (Token){
    .start = start,
    .end = end,
    .kind = kind,
  };
  list->size++;
  
}