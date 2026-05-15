#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint8_t *buffer;
    size_t length;
    size_t offset;
} Arena;

Arena *arena_create(size_t size);

void *arena_alloc(Arena *arena, size_t size);

void arena_reset(Arena *arena);

void arena_free(Arena *arena);

#endif
