#ifndef PARSER_H
#define PARSER_H

#include "../allocator.h"
#include "tokenizer.h"


typedef struct ParseResult ParseResult;
struct ParseResult {
  U32 something;
};

typedef struct Parser Parser;
struct Parser {
  Allocator allocator;
  TokenList *list;
  Index current;
};


typedef U32 AstNodeKind;
enum {
  AstNodeKind_File,
  AstNodeKind_Numeric,
  AstNodeKind_OpAdd,

  AstNodeKind_OpMul,
};





typedef struct FnProtoData FnProtoData;
struct FnProtoData {
  // params
  U16 count;
  // return type
  //
};

typedef struct FnCallData FnCallData;
struct FnCallData {
  U16 count;
};

typedef struct AstNode AstNode;
struct AstNode {
  union {
    AstNode *lhs; // for binary operators
    FnProtoData *fnProto;
    FnCallData *fnCall;
  };
  AstNode *rhs;
  AstNodeKind kind;
  Index mainToken;
};

Parser *ParserInit(Allocator allocator, TokenList *tokenList);
AstNode *ParseExpression(Allocator allocator, TokenLocation *loc);
void AstDebugPrint(AstNode *root);


#endif // PARSER_H
