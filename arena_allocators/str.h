#ifndef STR_H
#define STR_H

#include "arena.h"
#include <stddef.h>

typedef struct {
    char *val;
    size_t len;
} String;

String *string_from_literal(Arena *arena, const char *str);

String *string(Arena *arena, const char *str);

void print_string(const String *str);

#endif
