
// TODO: for (;;) { Token token = nextToken(); if token.type = EOF break; push
// the scanned tokens in an array and assert them}
// write a function,... in your language and see that we output the correct
// tokens
//
#include "../src/lexer.h"
#include <stdio.h>
#include <stdlib.h>

void testLexEOF() {
  char *source = "+ \n";

  Lexer lexer = initLexer(source);

  for (;;) {
    Token token = nextToken();

    if (token.type == TOK_EOF)
      break;
  }
}

int main() { printf("done testing lexer\n"); }
