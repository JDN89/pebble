#ifndef pebble_parser_h
#define pebble_parser_h

#include "lexer.h"

#define ERROR_SIZE 256
typedef struct {
  Token ct;
  Token pt;
  char *errors[ERROR_SIZE];
  int errorCount;
} Parser;

void initParser(const char *source);

void parse_source(char *source);

#endif
