#include "../src/lexer.h"
#include <assert.h>
#include <stdio.h>

void testLexEOF() {
  char *source = "+ \n";

  TokenType expectedTokens[] = {TOKEN_IDENTIFIER,
                                TOKEN_COLON,
                                TOKEN_TYPE_DECLARATION,
                                TOKEN_EQ,
                                TOKEN_INTEGER,
                                TOKEN_IDENTIFIER,
                                TOKEN_CONST_DECLARATION,
                                TOKEN_MUT_DECLARATION,
                                TOKEN_EOF};

  Lexer lexer = initLexer(source);

  int counter = 0;

  for (;;) {
    Token token = nextToken(&lexer);

    assert(token.type == expectedTokens[counter]);
    counter++;
    break;
  }
}

int main() { printf("done testing lexer\n"); }
