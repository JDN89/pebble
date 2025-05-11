#include "../src/arena.h"
#include "../src/ast.h"
#include "../src/program.h"
#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#define ARENA_SIZE (64 * 1024)
unsigned char test_backing_buffer[ARENA_SIZE];

void create_statement(int i, Statement *stmt, Arena *a) {
  assert(stmt != NULL);

  // Allocate memory for the return statement in the arena
  struct ReturnStatement *return_stmt = arena_push(a, struct ReturnStatement);
  assert(return_stmt != NULL);

  // Allocate the expression and initialize it
  struct Expression *expr = arena_push(a, struct Expression);
  assert(expr != NULL);

  expr->type = NUMBER_EXPRESSION;
  expr->as.val = NUMBER(i);

  // Assign the expression to the return statement
  return_stmt->expr = expr;

  // Now assign the return statement to the statement
  stmt->type = RETURN_STATEMENT;
  stmt->as.return_stmt = return_stmt;
}

void test_arena(void) {
  printf("Start test_arena \n");

  Arena a = {0};
  arena_alloc(&a, ARENA_SIZE);

  StatementArray stmts;
  statement_array_init(&stmts); // Initialize dynamic array

  // Allocate space for a Statement in the arena

  for (int i = 0; i < 4; i++) {
    Statement *stmt = (Statement *)arena_alloc(&a, sizeof(Statement));

    create_statement(i, stmt, &a);
    // Push statement to dynamic array
    statement_array_push(&stmts, stmt);
  }

  for (int i = 0; i < 4; i++) {
    Statement x = *stmts.items[i];
    int val = AS_NUMBER(x.as.return_stmt->expr->as.val);
    assert(val == i);
    // TODO assert that addres is modulo fo 16 for cacha alignment
    uintptr_t ptr = (uintptr_t)stmts.items[i];
    assert(ptr % 16 == 0);
    printf("address %" PRIxPTR "\n", ptr);
  }

  // Cleanup
  statement_array_free(&stmts);

  printf("test_arena -- PASSED\n");
}

int main(void) {
  test_arena();
  return 0;
}
