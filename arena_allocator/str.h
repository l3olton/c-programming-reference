#ifndef STR_H
#define STR_H

#include "arena.h"
#include <stddef.h>

#define string_from_literal(arena, str) _string_create(arena, str, sizeof(str) - 1)

typedef struct {
    char *val;
    size_t len;
} String;

String *_string_create(Arena *arena, const char *val, size_t len);

String *string(Arena *arena, const char *str);

void print_string(const String *str);

#endif
