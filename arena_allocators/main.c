#include "arena.h"
#include "str.h"
#include <stdio.h>
#include <string.h>

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
