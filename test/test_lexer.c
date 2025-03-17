#include "../src/lexer.h"
#include <assert.h>
#include <stdio.h>

void testLexer() {
  char *source = " x : int = 5 \n"
                 "x :: 5 \n"
                 "x := 5 \n";

  TokenType expectedTokens[] = {TOKEN_IDENTIFIER,
                                TOKEN_COLON,
                                TOKEN_TYPE_DECLARATION,
                                TOKEN_ASSIGN,
                                TOKEN_INTEGER,
                                TOKEN_IDENTIFIER,
                                TOKEN_CONST_DECLARATION,
                                TOKEN_MUT_DECLARATION,
                                TOKEN_EOF};

  Lexer lexer = initLexer(source);

  int counter = 0;

  for (;;) {
    Token token = nextToken(&lexer);

    if (token.type != expectedTokens[counter]) {
      fprintf(stderr, "Assertion failed at token[%d]: expected %s, got %s\n",
              counter, tokenTypeToString(expectedTokens[counter]),
              tokenTypeToString(token.type));
    }

    assert(token.type == expectedTokens[counter]);
    counter++;
    break;
  }
}

int main() {
  printf("START testing LEXER\n");

  testLexer();
}
