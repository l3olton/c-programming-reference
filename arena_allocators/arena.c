#include "arena.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

Arena *arena_create(size_t size) {
    Arena *arena = malloc(sizeof(Arena));
    if (!arena) return NULL;

    arena->buffer = malloc(size);
    if (!arena->buffer) {
        free(arena);
        return NULL;
    }

    arena->length = size;
    arena->offset = 0;

    return arena;
}

void *arena_alloc(Arena *arena, size_t size) {
    size_t alignment = _Alignof(max_align_t);
    size_t aligned_offset = (arena->offset + alignment - 1) & ~(alignment - 1);
    if (size <= arena->length - aligned_offset) {
        void *ptr = arena->buffer + aligned_offset;
        memset(ptr, 0, size);
        arena->offset = aligned_offset + size;
        return ptr;
    }
    return NULL;
}

void arena_reset(Arena *arena) {
    arena->offset = 0;
}

void arena_free(Arena *arena) {
    free(arena->buffer);
    free(arena);
}

