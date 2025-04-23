#include "parser.h"
#include "lexer.h"
#include "value.h"
#include <stdio.h>

// init parser and keep asking for tokens -> scanning for demand

/*void initParser(const char *source) {*/
/*  printf("init parsser \n");*/
/*  // advance 2 times to set current token and next token*/
/*}*/

void parseSource(char *source) {
  printf("source -- \n%s \n", source);

  /*initParser(source);*/

  Lexer lexer = initLexer(source);

  for (;;) {

    Token token = nextToken(&lexer);

    printf("Token Type %s \n", tokenTypeToString(token.type));

    // NOTE: Bitwise & comparison that compares each bit token.type and compares
    // it to TOKEN EOF
    if (token.type == TOKEN_EOF)
      break;
  };
}
