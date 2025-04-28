

// Size is not realistic. I just wanted to create an arena that fits in my L1
// cache...
#include "program.h"
#include "arena.h"
#define ARENA_SIZE (64 * 1024) // 64 KB
unsigned char backing_buffer[ARENA_SIZE];

struct Program create_program() {
  struct Program program = {0};

  struct Arena arena = {0};
  arena_init(&arena, backing_buffer, ARENA_SIZE);
  program.arena = arena;
  return program;
};
