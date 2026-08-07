#include "ring_buffer.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    const size_t buf_size = 12;
    RingBuffer rb = {0};
    uint8_t buffer[buf_size];

    ring_buf_init(&rb, buffer, buf_size);

    uint8_t out;

    uint8_t str1[] = "subhanallah";
    for (size_t i = 0; i < sizeof(str1) / sizeof(str1[0]); i++)
        ring_buf_push(&rb, str1[i]);

    ring_buf_visualize(&rb);
    putchar('\n');

    printf("Pop 6 elements:\n");
    size_t i = 0;
    while (i++ < 6 && ring_buf_pop(&rb, &out))
        putchar(out);
    putchar('\n');

    ring_buf_visualize(&rb);
    putchar('\n');

    uint8_t str2[] = " akbar";
    for (size_t i = 0; i < sizeof(str2) / sizeof(str2[0]); i++)
        ring_buf_push(&rb, str2[i]);

    ring_buf_visualize(&rb);
    putchar('\n');

    while (ring_buf_pop(&rb, &out))
        putchar(out);
    putchar('\n');

    ring_buf_visualize(&rb);
    putchar('\n');

    return 1;
}
