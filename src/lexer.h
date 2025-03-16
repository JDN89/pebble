#ifndef pebble_lexer_h
#define pebble_lexer_h

#include <stdlib.h>

typedef enum {
  TOKEN_INTEGER = 0,
  TOKEN_STRING,
  TOKEN_BOOLEAN,
  TOKEN_EOF,

  TOKEN_ILLEGAL,
  // Operators
  TOKEN_EQ,
  TOKEN_NOT_EQ,
  TOKEN_ASSIGN,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_BANG,
  TOKEN_ASTERISK,
  TOKEN_SLASH,
  TOKEN_LT,
  TOKEN_GT,

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

char *tokenTypeToString(Token token);

Lexer initLexer(const char *source);

Token nextToken(Lexer *lexer);

#endif
