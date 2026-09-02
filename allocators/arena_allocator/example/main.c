#include <allocators/arena.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void do_things(Arena arena);

int main(void)
{
    Arena arena = {0};
    size_t arena_size = 1024;
    uint8_t arena_buffer[arena_size];

    if (arena_init(&arena, arena_buffer, arena_size)) {
        do_things(arena);
    } else {
        printf("Error intialising arena\n");
        return 1;
    }

    return 0;
}

void do_things(Arena arena)
{
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

    char *str1_src = "Hello";

    const size_t sixteen = 16;
    char *str1 = arena_alloc(&arena, sixteen);

    if (str1) {
        strncpy(str1, str1_src, strlen(str1_src));

        for (size_t i = 0; i < strlen(str1); ++i)
            putchar(str1[i]);
        putchar('\n');
    }

    printf("allocation from %zu to %zu, curr offset: %zu\n\n", prev_offset, prev_offset + sixteen, arena.offset);
}
