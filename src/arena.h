#ifndef ARENA
#define ARENA

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct Arena {
  unsigned char *buf;
  size_t buf_len;
  size_t prev_offset; // This will be useful for later on
  size_t curr_offset;
};

void *arena_alloc(struct Arena *a, size_t size);

void arena_init(struct Arena *a, void *backing_buffer,
                size_t backing_buffer_length);
void arena_free_all(struct Arena *a);

#endif
