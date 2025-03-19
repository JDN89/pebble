#include "../src/lexer.h"
#include <assert.h>
#include <stdio.h>

void testVariableDeclarations() {
  char *source = " x : int = 5 \n"
                 "x :: 5 \n"
                 "x :: 6 + 5 - 4 * 3  \n"
                 "x := 5 \n";

  TokenType expectedTokens[] = {TOKEN_IDENTIFIER,
                                TOKEN_COLON,
                                TOKEN_TYPE_DECLARATION,
                                TOKEN_ASSIGN,
                                TOKEN_INTEGER,
                                TOKEN_IDENTIFIER,
                                TOKEN_CONST_DECLARATION,
                                TOKEN_INTEGER,
                                TOKEN_PLUS,
                                TOKEN_INTEGER,
                                TOKEN_MUT_DECLARATION,
                                TOKEN_INTEGER,
                                TOKEN_ASTERISK,
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
    if (token.type == TOKEN_EOF) {
      break;
    }
  }
  printf("Typed and untyped variable declarations test -- PASSED \n");
}

int main() {
  printf("START testing LEXER\n");
  testVariableDeclarations();
  printf("finished running LEXER tests \n");
}
