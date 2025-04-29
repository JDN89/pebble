#ifndef pebble_lexer_h
#define pebble_lexer_h

#include <stdlib.h>

typedef enum {
  TOKEN_INTEGER = 0,
  TOKEN_EOF,
  TOKEN_TYPE_DECLARATION,
  TOKEN_LET,
  TOKEN_IDENTIFIER,
  TOKEN_KEYWORD,
  TOKEN_COLON,
  TOKEN_SEMICOLON,
  TOKEN_RETURN,

  TOKEN_ILLEGAL,
  // Operators
  TOKEN_ASSIGN,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_ASTERISK,
  TOKEN_SLASH,

  // builtin
  TOKEN_PRINT,

} token_type;

typedef struct {
  token_type type;
  int offset;
  size_t length;
  size_t line;
} Token;

typedef struct {
  token_type type;
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

char *tokenTypeToString(token_type type);

Lexer create_lexer(const char *source);

Token next_token(Lexer *lexer);

#endif
