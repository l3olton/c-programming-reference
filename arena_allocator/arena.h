#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t *buffer;
    size_t length;
    size_t offset;
    bool dynamic_mem;
} Arena;

Arena *arena_create(const size_t size);

void *arena_alloc(Arena *arena, const size_t size);

bool arena_init(Arena *arena, uint8_t *buffer, const size_t size);

void arena_reset(Arena *arena);

void arena_free(Arena *arena);

#endif
