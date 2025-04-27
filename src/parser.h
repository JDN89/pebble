#ifndef pebble_parser_h
#define pebble_parser_h

#include "lexer.h"

#define ERROR_SIZE 256
typedef struct {
  Token ct;
  Token pt;
  char *errors[ERROR_SIZE];
  int errorCount;
  Lexer lex;
} parser;

parser create_parser(Lexer *lexer);

void parse_source(char *source);

#endif
