#include "../src/arena.h"
#include "../src/ast.h"
#include "../src/program.h"
#include <assert.h>
#include <stdio.h>

#define ARENA_SIZE (64 * 1024)
unsigned char backing_buffer[ARENA_SIZE];

void test_arena() {
  struct Arena a = {0};
  arena_init(&a, backing_buffer, ARENA_SIZE);

  struct StatementArray stmts;
  statement_array_init(&stmts); // Initialize dynamic array

  // Allocate space for a Statement in the arena
  struct Statement *stmt =
      (struct Statement *)arena_alloc(&a, sizeof(struct Statement));
  assert(stmt != NULL);

  // Fill it with data
  struct Expression expr = {0};
  expr.type = NUMBER_EXPRESSION;
  expr.as.val = NUMBER(4);

  stmt->type = RETURN_STATEMENT;
  stmt->as.return_stmt.expr = expr; // Point to the Expression

  // Push statement to dynamic array
  statement_array_push(&stmts, stmt);

  // Retrieve and print the first statement
  struct Statement first = *stmts.items[0];
  int val = AS_NUMBER(first.as.return_stmt.expr.as.val);
  printf("first statement value: %f\n",
         AS_NUMBER(first.as.return_stmt.expr.as.val));

  assert(val == 4);

  // Cleanup
  statement_array_free(&stmts);

  printf("test_arena -- PASSED\n");
}

int main() {

  test_arena();

  return 0;
}
