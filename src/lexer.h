#ifndef pebble_lexer_h
#define pebble_lexer_h

#include <stdlib.h>

typedef enum {
  TOKEN_INTEGER = 0,
  TOKEN_EOF,
  TOKEN_TYPE_DECLARATION,
  TOKEN_IDENTIFIER,
  TOKEN_COLON,
  TOKEN_CONST_DECLARATION,
  TOKEN_MUT_DECLARATION,

  TOKEN_ILLEGAL,
  // Operators
  TOKEN_ASSIGN,
  TOKEN_PLUS,

} TokenType;

typedef struct {
  TokenType type;
  int offset;
  size_t length;
  size_t line;
} Token;

typedef struct {
  TokenType type;
  int offset;
  size_t length;
  size_t line;
  char *message;
} ErrorToken;

typedef struct Lexer {
  const char *start;
  const char *current;
  const char *startOfSource;
  int line;
} Lexer;

char *tokenTypeToString(TokenType type);

Lexer initLexer(const char *source);

Token nextToken(Lexer *lexer);

#endif
