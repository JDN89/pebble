#ifndef pebble_parser_h
#define pebble_parser_h

#include "scanner.h"

#define ERROR_SIZE 256
typedef struct {
  Token ct;
  Token pt;
  char *errors[ERROR_SIZE];
  int errorCount;
} Parser;

void initParser();

#endif
