#ifndef PROGRAM
#define PROGRAM

#include "arena.h"
#include "ast.h"

// The arena will contain statements, but how do I keep track to the beginning
// of each statement? Store the pointers to the statements in dynamic array?

struct StatementArray {
  struct Statement **items;
  size_t count;
  size_t capacity;
};
void statement_array_init(struct StatementArray *arr);
void statement_array_push(struct StatementArray *arr, struct Statement *stmt);
void statement_array_free(struct StatementArray *arr);

#endif
