#ifndef C_TOKENIZER_H
#define C_TOKENIZER_H

#include "../allocator.h"


typedef U32 Index;

typedef U32 TokenKind;
enum {
  TokenKind_Error,

  TokenKind_EOF,
  TokenKind_Numeric,
  TokenKind_Plus,

  // Literals

  // operators
  TokenKind_Minus,
  TokenKind_Star,
  TokenKind_Slash,

  // assignments

  // punctuation
  TokenKind_ParenL,
  TokenKind_ParenR,
  TokenKind_BraceL,
  TokenKind_BraceR,
  TokenKind_BracketL,
  TokenKind_BracketR,

};

typedef struct Token Token;
struct Token {
  Index start;
  Index end;
  TokenKind kind;
  U32 reserved;
};

typedef struct TokenList TokenList;
struct TokenList {
  Allocator allocator;
  Token *tokens;
  U32 capacity;
  U32 size;
};

TokenList *TokenListInit(Allocator allocator, U64 capacity);




#endif