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
#include <sys/types.h>

#define arena_push(arena, type) (type *)push_size_((arena), sizeof(type))
#define push_array(arena, type, amount) push_size_(arena, sizeof(type) * amount)
#define AlignPow2(x, b) (((x) + (b) - 1) & ~((b) - 1))

typedef struct {
  u_int8_t *buf; // u_int8_t so we can move over the buffer one byte at the time
  u_int64_t size;
  u_int64_t used;
} Arena;

Arena *arena_alloc(Arena *a, size_t size);

void free_arena(Arena *a);

void *push_size_(Arena *a, size_t size);

void create_arena(Arena *a, void *backing_buffer, size_t backing_buffer_length);
void arena_free_all(Arena *a);

#endif
