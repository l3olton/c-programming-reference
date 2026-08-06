#include "ring_buffer.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    const size_t buf_size = 8;
    RingBuffer rb = {0};
    uint8_t buffer[buf_size];

    ring_buf_init(&rb, buffer, buf_size);

    for (uint8_t i = 'A'; i <= 'J'; i++) {
        bool can_push = ring_buf_push(&rb, i);
        ring_buf_visualize(&rb);
        printf("can_push: %d\n\n", can_push);
    }

    uint8_t out;

    for (size_t i = 0; i < 3; i++) {
        if (ring_buf_pop(&rb, &out)) {
            printf("pop: %c\n", out);
            ring_buf_visualize(&rb);
            putchar('\n');
        }
    }

    for (uint8_t i = 'K'; i <= 'T'; i++) {
        bool can_push = ring_buf_push(&rb, i);
        ring_buf_visualize(&rb);
        printf("can_push: %d\n\n", can_push);
    }

    while (ring_buf_pop(&rb, &out));

    ring_buf_visualize(&rb);
    putchar('\n');

    uint8_t message[] = "risalah";
    for (size_t i = 0; i < sizeof(message) / sizeof(message[0]); i++)
        ring_buf_push(&rb, message[i]);

    ring_buf_visualize(&rb);
    putchar('\n');

    printf("Pop all elements:\n");
    while (ring_buf_pop(&rb, &out))
        putchar(out);
    putchar('\n');

    ring_buf_visualize(&rb);
    putchar('\n');

    return 1;
}
