#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    uint8_t *buffer;
    size_t length;
    size_t offset;
} Arena;

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

typedef struct {
    char *val;
    size_t len;
} String;

#define string_from_literal(a, s) _string_create(a, s, sizeof(s) - 1)
#define string(a, s) _string_create(a, s, strlen(s))

String *_string_create(Arena *arena, const char *val, size_t len) {
    String *str = arena_alloc(arena, sizeof(String));
    if (!str) return NULL;

    str->val = arena_alloc(arena, len);
    if (!str->val) return NULL;

    memcpy(str->val, val, len);
    str->len = len;

    return str;
}

void print_string(const String *str) {
    for (size_t i = 0; i < str->len; ++i) {
        printf("%c", str->val[i]);
    }
}

int main(void) {
    Arena *arena = arena_create(1024); // reserve 1 kib
    if (!arena) {
        printf("Error creating arena\n");
        return 1;
    }
    printf("buffer start addr: %p, buffer end addr: %p\n", arena->buffer, arena->buffer + arena->length);
    printf("length: %zu, offset: %zu\n\n", arena->length, arena->offset);

    size_t prev_offset = arena->offset;

    size_t arr1_len = 256;
    uint8_t *arr1 = arena_alloc(arena, arr1_len);
    if (arr1) {
        printf("arr[0]: %d, arr[%zu]: %d\n", arr1[0], arr1_len - 1, arr1[arr1_len - 1]);
    }
    
    printf("allocation from %zu to %zu, curr offset: %zu\n\n", prev_offset, prev_offset + arr1_len, arena->offset);

    prev_offset = arena->offset;
    char *str1 = arena_alloc(arena, 64);
    if (str1) {
        char *str1_src = "Hello";
        strncpy(str1, str1_src, strlen(str1_src));

        for (size_t i = 0; i < strlen(str1); ++i) {
            printf("%c", str1[i]);
        }
        printf("\n");
    }

    printf("allocation from %zu to %zu, curr offset: %zu\n\n", prev_offset, prev_offset + 64, arena->offset);

    prev_offset = arena->offset;
    String *str = string_from_literal(arena, "Hello World!");
    if (str) {
        printf("String val: ");
        print_string(str);
        printf(", length: %zu\n", str->len);
    }

    printf("allocation from %zu to %zu, curr offset: %zu\n\n", prev_offset, prev_offset + sizeof(String) + 12, arena->offset);

    printf("Enter some text:\n");
    char temp[64];
    fgets(temp, 64, stdin);

    prev_offset = arena->offset;
    String *str2 = string(arena, temp);
    print_string(str2);

    printf("allocation from %zu to %zu, curr offset: %zu\n\n", prev_offset, prev_offset + sizeof(String) + strlen(temp), arena->offset);

    arena_free(arena);

    return 0;
}
