#include "str.h"
#include "arena.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

String *_string_create(Arena *arena, const char *val, size_t len) {
    String *str = arena_alloc(arena, sizeof(String));
    if (!str) return NULL;

    str->val = arena_alloc(arena, len);
    if (!str->val) return NULL;

    memcpy(str->val, val, len);
    str->len = len;

    return str;
}

String *string_from_literal(Arena *arena, const char *str) {
    return _string_create(arena, str, sizeof(str) - 1);
}

String *string(Arena *arena, const char *str) {
    return _string_create(arena, str, strlen(str));
}

void print_string(const String *str) {
    for (size_t i = 0; i < str->len; ++i) {
        printf("%c", str->val[i]);
    }
}

