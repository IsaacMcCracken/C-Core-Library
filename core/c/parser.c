#include "parser.h"

#include <stdio.h>

#define Internal static inline 

static U32 nodeCount = 0;



Parser *ParserInit(Allocator allocator, TokenList *tokenList) {
  Parser *parser = CreateNoZero(allocator , Parser, NULL);
  parser->allocator = allocator;
  parser->current = 0; 
  parser->list = tokenList;

  return parser;
}

Internal Token ParserGetCurrentToken(Parser *parser) {
  return parser->list->tokens[parser->current];
}

Internal U32 TokenGetPrecedence(TokenLocation *loc) {
  Token token = loc->list->tokens[loc->index];
  switch (token.kind) {
    case TokenKind_Minus: 
    case TokenKind_Plus: {
      return 1;
    } break;

    case TokenKind_Slash: 
    case TokenKind_Star: {
      return 2;
    } break;

    
    default:
      break;
  }


  return 0;
}


Internal B32 IsEOF(TokenLocation *loc) {
  return loc->list->tokens[loc->index].kind == TokenKind_EOF;
}



AstNode *ParseBinaryOp(Allocator allocator, TokenLocation *loc, AstNode *lhs, AstNode *rhs) {
  AstNode *result = Create(allocator, AstNode, NULL);

  switch (loc->list->tokens[loc->index].kind) {
    case TokenKind_Plus: {
      result->kind = AstNodeKind_OpAdd;
      result->mainToken = loc->index;
      } break;

    case TokenKind_Star: {
      result->mainToken = AstNodeKind_OpMul;
      result->mainToken = loc->index;
    } break;
    
    // all other binary operations

    default: {
      // error handling
      printf("No please dont\n");
    } break;
  }

  result->lhs = lhs;
  result->rhs = rhs;
  nodeCount++;

  return result;
}


AstNode *ParseSingular(Allocator allocator, TokenLocation *loc) {
  AstNode *result = Create(allocator, AstNode, NULL);
  switch (loc->list->tokens[loc->index].kind) {
    case TokenKind_Numeric: {
        result->kind = AstNodeKind_Numeric;
        return result;
    }
    default:
        fprintf(stderr, "We were parsing and some stuff got fucked up.");
        return NULL;
  }
}


Internal B32 TokenIsBinaryOperator(TokenLocation *loc) {
  Token token = TokenLocationToken(loc);
  return token.kind >= TokenKind_Plus && token.kind <= TokenKind_Slash;
}

Internal U32 TokenBinaryOperatorPrecedence(TokenLocation *loc) {
  const Token token = TokenLocationToken(loc);

  switch (token.kind)
  {
  case TokenKind_Plus:
  case TokenKind_Minus: {
    return 1;
  }
  case TokenKind_Star:
  case TokenKind_Slash: {
    return 2;
  }
    
  
  default:
    fprintf(stderr, "There was an unexpected token and it sucked");
    break;
  }


  return 0;
}


AstNode ParseFunctionProto(
  Allocator allocator, 
) {
  
}

AstNode *ParseExpressionEx(
  Allocator allocator,
  TokenLocation *loc,
  AstNode *lhs,
  U32 minPrecedence
) {
  TokenLocationAdvance(loc);

  while (TokenIsBinaryOperator(loc) && TokenBinaryOperatorPrecedence(loc) >= minPrecedence) {
    TokenLocation operator = *loc;

    TokenLocationAdvance(loc);
    AstNode *rhs = ParseSingular(allocator, loc);
    TokenLocationAdvance(loc);
    while (TokenIsBinaryOperator(loc) && TokenBinaryOperatorPrecedence(loc) > TokenBinaryOperatorPrecedence(&operator)) {
      rhs = ParseExpressionEx(allocator, loc, rhs, TokenBinaryOperatorPrecedence(&operator));
      TokenLocationAdvance(loc);
    }
    

    lhs = ParseBinaryOp(allocator, &operator, lhs, rhs);
  }

  return lhs;
  
}

AstNode *ParseExpression(Allocator allocator, TokenLocation *loc) {
  return ParseExpressionEx(allocator, loc, ParseSingular(allocator, loc), 0);   
}


void AstDebugPrintEx(AstNode *node, U64 level) {
  for (U64 i = 0; i < level; i++) putchar(' ');

  switch (node->kind) {
    case AstNodeKind_Numeric: {
        printf("NUM:");

    } break;

    case AstNodeKind_OpAdd: {
      printf("add: +");
    } break;
    
    default:
      printf("AHHHH");  


      break;
  }
  putchar('\n');

  if (node->lhs)
    AstDebugPrintEx(node->lhs, level  + 1);

  if (node->rhs)
    AstDebugPrintEx(node->rhs, level  + 1);

}

void AstDebugPrint(AstNode *root) {
  printf("\nNode Count: %lu\n", nodeCount);
  AstDebugPrintEx(root, 0);
}

