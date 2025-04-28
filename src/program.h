#ifndef PROGRAM
#define PROGRAM

#include "arena.h"
#include "ast.h"

// The arena will contain statements, but how do I keep track to the beginning
// of each statement? Store the pointers to the statements in dynamic array?
struct Program {
  struct Arena arena;
};

struct Program create_program();

#endif
