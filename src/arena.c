#include "arena.h"
#include "ast.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

Arena *arena_alloc(Arena *a, size_t size) {
  assert(a != NULL);
  a->size = size;
  a->used = 0;
  void *base = mmap(NULL, size, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (base == MAP_FAILED)
    return NULL;
  assert(base != NULL);
  a->buf = base;
  return a;
}

void *push_size_(Arena *a, size_t size) {
  assert(a != NULL);
  assert(size > 0);

  uintptr_t currnt = (uintptr_t)(a->buf + a->used);
  uintptr_t aligned = AlignPow2(currnt, 16);
  size_t offset = aligned - (uintptr_t)a->buf;

  // TODO: when we hid assert start linking arena's
  assert(offset + size < a->size);

  a->used = offset + size;
  return (void *)aligned;
}

void free_arena(Arena *a) {
  assert(a != NULL);
  munmap(a->buf, a->size);
}
