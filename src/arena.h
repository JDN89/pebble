#ifndef ARENA
#define ARENA

#include "ast.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Arena {
  u_int8_t *buf;
  size_t buf_len;
  size_t prev_offset; // This will be useful for later on
  size_t curr_offset;
};

void *arena_alloc(struct Arena *a, size_t size);

struct Statement *push_statement(struct Arena *a);

void create_arena(struct Arena *a, void *backing_buffer,
                  size_t backing_buffer_length);
void arena_free_all(struct Arena *a);

#endif
