#ifndef PROGRAM
#define PROGRAM

#include "arena.h"
#include "ast.h"

// The arena will contain statements, but how do I keep track to the beginning
// of each statement? Store the pointers to the statements in dynamic array?

typedef struct {
  Statement **items;
  size_t count;
  size_t capacity;
} StatementArray;
void statement_array_init(StatementArray *arr);
void statement_array_push(StatementArray *arr, Statement *stmt);
void statement_array_free(StatementArray *arr);

#endif
