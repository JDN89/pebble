#include "parser.h"
#include "arena.h"
#include "ast.h"
#include "lexer.h"
#include "program.h"
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

// TODO simplify and cleanup
void parse_source(char *source) {
  printf("source -- \n%s \n", source);

  // TODO creatProgram with storage of arena

  // init lexer and create parser in main?
  Lexer lexer = create_lexer(source);
  Parser parser = create_parser(&lexer);
  struct Program prog = create_program();
  struct Statement *stmt;

  stmt = (struct Statement *)arena_alloc(&prog.arena, sizeof(struct Statement));

  // parse statement parsed de juiste statement based on swithc case
  // we beginnen met let statement
  // let statement indentifier en expr
  // parse_expression(precedence = LOWEST) begint met parsen van left expression
  // indien op
  // callen we parse_infix_expression indien precedence hoger is dan voorgaande
  // en we geven de left expression mee aan de call in infixexpression asignen
  // we left aan left en right is resultaat van parse expression(prec = prec
  // CURRENT OP!!), waar we blijven infix aanroepen zolang prec hoger is dan de
  // voorgaande. Belangrijk we blijven aan de rechter kant leaves aan de AST
  // toevoegen zolang de precedence hoger is dan de voorgaande 1 + 3 * 6
  // 	+
  //   / \
  // 1    *
  //     / \
  //     3  6
  //
  // *stmt = parse_statement();
}
