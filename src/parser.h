#ifndef pebble_Parser_h
#define pebble_Parser_h

#include "lexer.h"

#define ERROR_SIZE 256

enum precedence {
  LOWEST,
  EQUALS,
  SUM,
  PRODUCT,
};

typedef struct {
  Token ct;
  Token pt;
  char *errors[ERROR_SIZE];
  int errorCount;
  Lexer *lexer;
} Parser;

Parser create_parser(Lexer *lexer);

void parse_source(char *source);

#endif
