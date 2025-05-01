#include "parser.h"
#include "arena.h"
#include "ast.h"
#include "lexer.h"
#include "program.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

Token advance(Lexer *lexer) { return next_token(lexer); }

void parse_retun_statement(Token token) {}

struct LetStatement *parse_let_statement(Parser *parser, const char *source,
                                         struct Arena *arena) {
  struct LetStatement *letStatement =
      arena_alloc(arena, sizeof(struct LetStatement));
  assert(letStatement != NULL);

  char *identifier = arena_alloc(arena, parser->ct.length + 1);
  assert(identifier != NULL);
  memcpy(identifier, source + parser->ct.offset, parser->ct.length);
  identifier[parser->ct.length] = '\0';

  letStatement->identifier = identifier;

  // TODO parse value expression
  return letStatement;
}

struct Statement *parse_statement(Parser *parser, char *source,
                                  struct Arena *arena) {
  switch (parser->ct.type) {
  case TOKEN_LET: {

    printf("parse let staement");

    advance(parser->lexer);
    struct Statement *statement = arena_alloc(arena, sizeof(struct Statement));
    statement->type = LET_STATMENT;
    statement->as.let_stmt = parse_let_statement(parser, source, arena);
    return statement;
  } break;
  default:
    // TODO fix or improve, if default shouldn't happy print to stderr
    return NULL;
    break;
  }
}

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
  printf("parser : source -- \n%s \n", source);

  // TODO creatProgram with storage of arena

  // init lexer and create parser in main?
  Lexer lexer = create_lexer(source);
  Parser parser = create_parser(&lexer);
  struct Program prog = create_program();
  struct Statement *statement = parse_statement(&parser, source, prog.arena);

  struct StatementArray *statement_array;
  statement_array_init(statement_array);
  assert(statement_array != NULL);

  statement_array_push(statement_array, statement);

  printf("first identifier %s",
         statement_array->items[0]->as.let_stmt->identifier);

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
