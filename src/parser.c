#include "parser.h"
#include "lexer.h"
#include <stdio.h>

// init parser and keep asking for tokens -> scanning for demand

/*void initParser(const char *source) {*/
/*  printf("init parsser \n");*/
/*  // advance 2 times to set current token and next token*/
/*}*/

// TODO: create arena and add to the arena. What is the lifetime of the AST?
void parse_retun_statement(Token token) {}

void parse_source(char *source) {
  printf("source -- \n%s \n", source);

  Lexer lexer = initLexer(source);

  for (;;) {

    Token token = nextToken(&lexer);

    switch (token.type) {
    case TOKEN_INTEGER:
    case TOKEN_EOF:
    case TOKEN_TYPE_DECLARATION:
    case TOKEN_IDENTIFIER:
    case TOKEN_KEYWORD:
    case TOKEN_COLON:
    case TOKEN_CONST_DECLARATION:
    case TOKEN_MUT_DECLARATION:
    case TOKEN_ILLEGAL:
    case TOKEN_ASSIGN:
    case TOKEN_PLUS:
    case TOKEN_MINUS:
    case TOKEN_ASTERISK:
    case TOKEN_SLASH: {
      printf("TODO report error; Read chapter error handling in book effective "
             "c. Or google it");
    } break;
    case TOKEN_RETURN: {
      printf("token return");

    }

    break;
    }

    printf("Token Type %s \n", tokenTypeToString(token.type));

    // NOTE: Bitwise & comparison that compares each bit token.type and compares
    // it to TOKEN EOF
    if (token.type == TOKEN_EOF)
      break;
  };
}
