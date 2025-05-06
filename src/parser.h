#ifndef pebble_Parser_h
#define pebble_Parser_h

#include "lexer.h"

#define ERROR_SIZE 256

struct Arena;

enum precedence {
  LOWEST,
  EQUALS,
  SUM,
  PRODUCT,
};

struct Parser {
  Token ct;
  Token pt;
  char *errors[ERROR_SIZE];
  int errorCount;
  struct Lexer *lexer;
};

struct Parser create_parser(struct Lexer *lexer);

void parse_source(const char *source, struct Arena *arena,
                  struct Parser *parser);

#endif
