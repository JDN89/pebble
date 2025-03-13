#include "scanner.h"
#include "parser.h"

typedef struct Scanner {
  const char *start;
  const char *current;
  int line;
} Scanner;

struct Scanner scanner;

void initScanner(const char *source) {
  scanner.start = source;
  scanner.current = source;
  scanner.line = -1;
}

// TODO
Token makeToken(Scanner scanner) {
  Token token = {0};
  return token;

  ;
}
