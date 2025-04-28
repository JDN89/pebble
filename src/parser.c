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

Token advance(Lexer *lexer) { return nextToken(lexer); }

Parser create_parser(Lexer *lexer) {

  // Set all bytes of parser to zero (including pointers, integers, structs,
  // arrays, etc.).
  // Set ct and pt to zeroed Tokens.
  // Set errors array to all NULL.
  // Set errorCount to 0.
  // Set lexer pointer to NULL initially.
  Parser parser = {0};
  parser.ct = advance(lexer);
  parser.pt = advance(lexer);
  parser.lexer = lexer;
  return parser;
}

void parse_source(char *source) {
  printf("source -- \n%s \n", source);

  // TODO creatProgram with storage of arena

  // init lexer and create parser in main?
  Lexer lexer = create_lexer(source);
  Parser parser = create_parser(&lexer);

  for (;;) {

    Token token = parser.ct;

    switch (token.type) {
    case TOKEN_INTEGER:
    case TOKEN_EOF:
    case TOKEN_TYPE_DECLARATION:
    case TOKEN_IDENTIFIER:
    case TOKEN_KEYWORD:
    case TOKEN_COLON:
    case TOKEN_ILLEGAL:
    case TOKEN_ASSIGN:
    case TOKEN_PLUS:
    case TOKEN_MINUS:
    case TOKEN_ASTERISK:
    case TOKEN_LET:
    case TOKEN_SEMICOLON:
    case TOKEN_PRINT:
    case TOKEN_SLASH: {
      printf("TODO report error; Read chapter error handling in book effective "
             "c. Or google it");
      advance(Lexer * lexer)
    } break;
    case TOKEN_RETURN: {
      printf("token return");

    }

    break;
      break;
    }

    printf("Token Type %s \n", tokenTypeToString(token.type));

    // NOTE: Bitwise & comparison that compares each bit token.type and compares
    // it to TOKEN EOF
    // you say wut mate?
    if (token.type == TOKEN_EOF)
      break;
  };
}
