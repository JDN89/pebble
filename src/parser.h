#ifndef pebble_Parser_h
#define pebble_Parser_h

#include "arena.h"
#include "lexer.h"

#define ERROR_SIZE 256

typedef enum {
  LOWEST,
  EQUALS,
  SUM,
  PRODUCT,
} Precedence;

struct Parser {
  Token ct;
  Token pt;
  char *errors[ERROR_SIZE];
  int errorCount;
  struct Lexer *lexer;
};

struct Parser create_parser(struct Lexer *lexer);

void parse_source(const char *source, Arena *arena, struct Parser *parser);

#endif
