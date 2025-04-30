#include "../src/arena.h"
#include "../src/ast.h"
#include "../src/program.h"
#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#define ARENA_SIZE (64 * 1024)
unsigned char test_backing_buffer[ARENA_SIZE];

void create_statement(int i, struct Statement *stmt) {

  assert(stmt != NULL);

  // Fill it with data
  struct Expression expr = {0};
  expr.type = NUMBER_EXPRESSION;
  expr.as.val = NUMBER(i);

  stmt->type = RETURN_STATEMENT;
  stmt->as.return_stmt.expr = expr; // Point to the Expression
}

void test_arena(void) {
  printf("Start test_arena \n");

  struct Arena a = {0};
  arena_init(&a, test_backing_buffer, ARENA_SIZE);

  struct StatementArray stmts;
  statement_array_init(&stmts); // Initialize dynamic array

  // Allocate space for a Statement in the arena

  for (int i = 0; i < 4; i++) {
    struct Statement *stmt =
        (struct Statement *)arena_alloc(&a, sizeof(struct Statement));

    create_statement(i, stmt);
    // Push statement to dynamic array
    statement_array_push(&stmts, stmt);
  }

  for (int i = 0; i < 4; i++) {
    struct Statement x = *stmts.items[i];
    int val = AS_NUMBER(x.as.return_stmt.expr.as.val);
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
