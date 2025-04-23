#ifndef AST
#define AST

#include "lexer.h"
#include "value.h"

enum expression_type { NUMBER_EXPRESSION };

struct expression {
  expression_type type;
  union {
    value val;
  } as;
};

struct return_statement {
  token_type type;
  expression expr;
};

#endif // !AST
