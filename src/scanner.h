#ifndef pebble_scanner_h
#define pebble_scanner_h

#include <stdlib.h>

typedef enum {
  INTEGER = 0,
  STRING,
  BOOLEAN,
} TokenType;

typedef struct {
  TokenType type;
  size_t offset;
  size_t length;
  size_t line;
} Token;

void initScanner(const char *source);

Token nextToken();

#endif
