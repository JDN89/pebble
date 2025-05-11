

// Size is not realistic. I just wanted to create an arena that fits in my L1
// cache...
#include "program.h"

// TODO capacity is to small
void statement_array_init(StatementArray *arr) {
  arr->count = 0;
  arr->capacity = 4;
  arr->items = malloc(arr->capacity * sizeof(Statement *));
}

void statement_array_push(StatementArray *arr, Statement *stmt) {
  if (arr->count >= arr->capacity) {
    arr->capacity *= 2;
    arr->items = realloc(arr->items, arr->capacity * sizeof(Statement *));
  }
  arr->items[arr->count++] = stmt;
}

void statement_array_free(StatementArray *arr) {
  free(arr->items);
  arr->count = 0;
  arr->capacity = 0;
  arr->items = NULL;
}
