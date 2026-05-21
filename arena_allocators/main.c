#include "arena.h"
#include "str.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void do_things(Arena arena);

int main(void) {
    // ====== arena_create creates arena and dynamically allocates its memory ======

    Arena *arena1 = arena_create(1024);
    if (arena1) {
        do_things(*arena1);
    } else {
        printf("Error creating arena1\n");
        return 1;
    }

    arena_free(arena1);
    arena1 = NULL;

    // ====== init arena from statically allocated buffer ======

    Arena arena2 = {0};
    size_t arena2_size = 1024;
    uint8_t arena2_buffer[arena2_size];

    if (arena_init(&arena2, arena2_buffer, arena2_size)) {
        do_things(arena2);
    } else {
        printf("Error intialising arena2\n");
        return 1;
    }

    // ====== init arena from dynamically allocated buffer ======

    Arena arena3 = {0};
    size_t arena3_size = 1024;
    uint8_t *arena3_buffer = malloc(arena2_size);
    if (arena3_buffer == NULL) {
        printf("Error allocating arena3 buffer\n");
        return 1;
    }

    if (arena_init(&arena3, arena3_buffer, arena3_size)) {
        do_things(arena3);
    } else {
        printf("Error initialising arena3\n");
        return 1;
    }

    free(arena3_buffer);
    arena3_buffer = NULL;

    return 0;
}

void do_things(Arena arena) {
    printf("buffer start addr: %p, buffer end addr: %p\n", arena.buffer, arena.buffer + arena.length);
    printf("length: %zu, offset: %zu\n\n", arena.length, arena.offset);

    size_t prev_offset = arena.offset;

    size_t arr1_len = 256;
    uint8_t *arr1 = arena_alloc(&arena, arr1_len);
    if (arr1) {
        printf("arr[0]: %d, arr[%zu]: %d\n", arr1[0], arr1_len - 1, arr1[arr1_len - 1]);
    }
    
    printf("allocation from %zu to %zu, curr offset: %zu\n\n", prev_offset, prev_offset + arr1_len, arena.offset);

    prev_offset = arena.offset;
    char *str1 = arena_alloc(&arena, 64);
    if (str1) {
        char *str1_src = "Hello";
        strncpy(str1, str1_src, strlen(str1_src));

        for (size_t i = 0; i < strlen(str1); ++i) {
            printf("%c", str1[i]);
        }
        printf("\n");
    }

    printf("allocation from %zu to %zu, curr offset: %zu\n\n", prev_offset, prev_offset + 64, arena.offset);

    prev_offset = arena.offset;
    String *str = string_from_literal(&arena, "Hello World!");
    if (str) {
        printf("String val: ");
        print_string(str);
        printf(", length: %zu\n", str->len);
    }

    printf("allocation from %zu to %zu, curr offset: %zu\n\n", prev_offset, prev_offset + sizeof(String) + 12, arena.offset);

    printf("Enter some text: ");
    char temp[64];
    fgets(temp, 64, stdin); // TODO: check for error and remove newline

    prev_offset = arena.offset;
    String *str2 = string(&arena, temp);
    print_string(str2);
    printf("\n");

    printf("allocation from %zu to %zu, curr offset: %zu\n\n", prev_offset, prev_offset + sizeof(String) + strlen(temp), arena.offset);
}
