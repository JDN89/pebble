#include "arena.h"
#include "ast.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

bool is_power_of_two(uintptr_t x) { return (x & (x - 1)) == 0; }

uintptr_t align_forward(uintptr_t ptr, size_t align) {
  uintptr_t p, a, modulo;

  assert(is_power_of_two(align));

  p = ptr;
  a = (uintptr_t)align;
  // Same as (p % a) but faster as 'a' is a power of two
  modulo = p & (a - 1);

  if (modulo != 0) {
    // If 'p' address is not aligned, push the address to the
    // next value which is aligned
    p += a - modulo;
  }
  return p;
}

#ifndef DEFAULT_ALIGNMENT
#define DEFAULT_ALIGNMENT (2 * sizeof(void *))
#endif

void create_arena(struct Arena *a, void *backing_buffer,
                  size_t backing_buffer_length) {
  a->buf = (unsigned char *)backing_buffer;
  a->buf_len = backing_buffer_length;
  a->curr_offset = 0;
  a->prev_offset = 0;
}

void *arena_alloc_align(struct Arena *a, size_t size, size_t align) {
  // Align 'curr_offset' forward to the specified alignment
  uintptr_t curr_ptr = (uintptr_t)a->buf + (uintptr_t)a->curr_offset;
  uintptr_t offset = align_forward(curr_ptr, align);
  offset -= (uintptr_t)a->buf; // Change to relative offset

  // Check to see if the backing memory has space left
  if (offset + size <= a->buf_len) {
    void *ptr = &a->buf[offset];
    a->prev_offset = offset;
    a->curr_offset = offset + size;

    // Zero new memory by default
    memset(ptr, 0, size);
    return ptr;
  }
  // Return NULL if the arena is out of memory (or handle differently)
  return NULL;
}

// Because C doesn't have default parameters
void *arena_alloc(struct Arena *a, size_t size) {
  return arena_alloc_align(a, size, DEFAULT_ALIGNMENT);
}

struct Statement *push_statement(struct Arena *a) {
  return arena_alloc_align(a, sizeof(struct Statement), DEFAULT_ALIGNMENT);
}

void *arena_resize_align(struct Arena *a, void *old_memory, size_t old_size,
                         size_t new_size, size_t align) {
  assert(a != NULL);
  assert(is_power_of_two(align));

  unsigned char *old_mem = (unsigned char *)old_memory;

  // Case 1: fresh allocation
  if (old_mem == NULL || old_size == 0) {
    return arena_alloc_align(a, new_size, align);
  }

  // Case 2: in-bounds check
  if (old_mem < a->buf || old_mem >= a->buf + a->buf_len) {
    assert(0 && "Memory is out of bounds of the buffer in this arena");
    return NULL;
  }

  // Case 3: top-of-stack allocation — we can grow/shrink in place
  if (old_mem == a->buf + a->prev_offset) {
    size_t new_offset = a->prev_offset + new_size;

    // Check if there's space for resizing
    if (new_offset > a->buf_len) {
      return NULL; // Not enough space
    }

    if (new_size > old_size) {
      // Zero the new memory region
      memset(a->buf + a->prev_offset + old_size, 0, new_size - old_size);
    }

    a->curr_offset = new_offset;
    return old_memory;
  }

  // Case 4: not at top, must reallocate
  void *new_memory = arena_alloc_align(a, new_size, align);
  if (new_memory == NULL) {
    return NULL; // Allocation failed
  }

  size_t copy_size = old_size < new_size ? old_size : new_size;
  memmove(new_memory, old_memory, copy_size);
  return new_memory;
}

// Because C doesn't have default parameters
void *arena_resize(struct Arena *a, void *old_memory, size_t old_size,
                   size_t new_size) {
  return arena_resize_align(a, old_memory, old_size, new_size,
                            DEFAULT_ALIGNMENT);
}

void arena_free_all(struct Arena *a) {
  a->curr_offset = 0;
  a->prev_offset = 0;
}
