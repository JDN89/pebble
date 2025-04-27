#include "../src/lexer.h"
#include <assert.h>
#include <stdio.h>

// use to find bug in lexer for a specific token
// void test_parse_specific_token() {
//   char *source = "::";
//   TokenType expectedTokens[] = {TOKEN_CONST_DECLARATION, TOKEN_EOF};
//   Lexer lexer = initLexer(source);
//   int counter = 0;
//
//   for (;;) {
//     Token token = nextToken(&lexer);
//
//     if (token.type != expectedTokens[counter]) {
//       fprintf(stderr,
//               "Assertion failed at token[%d] source[%c]: expected %s, got
//               %s\n", counter, source[token.offset],
//               tokenTypeToString(expectedTokens[counter]),
//               tokenTypeToString(token.type));
//     }
//
//     assert(token.type == expectedTokens[counter]);
//     counter++;
//     if (token.type == TOKEN_EOF) {
//       break;
//     }
//   }
//   printf("test_parse_specific_token -- PASSED \n");
// }

void testVariableDeclarations() {
  char *source =

      " let a: int = 3 \n;"
      "let b: int = 4; \n"
      "let c : int  = a + b; \n"
      "let d: int = c * a; \n"
      "let result : int = a + b * c + d;\n"
      " print result;";

  token_type expectedTokens[] = {TOKEN_LET,
                                 TOKEN_IDENTIFIER,
                                 TOKEN_COLON,
                                 TOKEN_TYPE_DECLARATION,
                                 TOKEN_ASSIGN,
                                 TOKEN_INTEGER,
                                 TOKEN_SEMICOLON,
                                 TOKEN_LET,
                                 TOKEN_IDENTIFIER,
                                 TOKEN_COLON,
                                 TOKEN_TYPE_DECLARATION,
                                 TOKEN_ASSIGN,
                                 TOKEN_INTEGER,
                                 TOKEN_SEMICOLON,
                                 TOKEN_LET,
                                 TOKEN_IDENTIFIER,
                                 TOKEN_COLON,
                                 TOKEN_TYPE_DECLARATION,
                                 TOKEN_ASSIGN,
                                 TOKEN_IDENTIFIER,
                                 TOKEN_PLUS,
                                 TOKEN_IDENTIFIER,
                                 TOKEN_SEMICOLON,

                                 TOKEN_LET,
                                 TOKEN_IDENTIFIER,
                                 TOKEN_COLON,
                                 TOKEN_TYPE_DECLARATION,
                                 TOKEN_ASSIGN,
                                 TOKEN_IDENTIFIER,
                                 TOKEN_ASTERISK,
                                 TOKEN_IDENTIFIER,
                                 TOKEN_SEMICOLON,
                                 TOKEN_LET,
                                 TOKEN_IDENTIFIER,
                                 TOKEN_COLON,
                                 TOKEN_TYPE_DECLARATION,
                                 TOKEN_ASSIGN,
                                 TOKEN_IDENTIFIER,
                                 TOKEN_PLUS,
                                 TOKEN_IDENTIFIER,
                                 TOKEN_ASTERISK,
                                 TOKEN_IDENTIFIER,
                                 TOKEN_PLUS,
                                 TOKEN_IDENTIFIER,
                                 TOKEN_SEMICOLON,
                                 TOKEN_PRINT,
                                 TOKEN_IDENTIFIER,
                                 TOKEN_SEMICOLON,
                                 TOKEN_EOF};

  Lexer lexer = initLexer(source);

  int counter = 0;

  for (;;) {
    Token token = nextToken(&lexer);

    if (token.type != expectedTokens[counter]) {
      fprintf(stderr,
              "Assertion failed at token[%d] source[%c]: expected %s, got %s\n",
              counter, source[token.offset],
              tokenTypeToString(expectedTokens[counter]),
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
  // test_parse_specific_token();
  testVariableDeclarations();
  printf("finished running LEXER tests \n");
}
