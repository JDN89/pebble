#ifndef AST
#define AST

#include "lexer.h"
#include "value.h"

struct Expression;

enum expression_type { NUMBER_EXPRESSION, INFIX_EXPRESSION };

struct InfixExpression {

  struct Expression *left;
  token_type op;
  struct Expression *right;
};

struct Expression {
  enum expression_type type;
  union {
    struct Value val;
    struct InfixExpression infix;
  } as;
};

enum StatementType { RETURN_STATEMENT, LET_STATMENT };

struct ReturnStatement {
  token_type type;
  struct Expression *expr;
};

struct LetStatement {
  char *identifier;
  struct Expression *expr;
};

typedef struct {
  enum StatementType type;
  union {
    struct ReturnStatement *return_stmt;
    struct LetStatement *let_stmt;
  } as;
} Statement;

#endif
