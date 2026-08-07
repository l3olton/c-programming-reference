#include "ring_buffer.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void ring_buf_init(RingBuffer *rb, uint8_t *buffer, size_t size)
{
    rb->buffer = buffer;
    memset(rb->buffer, 0, size);
    rb->write_index = 0;
    rb->read_index = 0;
    rb->size = size;
}

bool ring_buf_is_full(const RingBuffer *rb)
{
    return (rb->write_index + 1) % rb->size == rb->read_index;
}

bool ring_buf_is_empty(const RingBuffer *rb)
{
    return rb->write_index == rb->read_index;
}

bool ring_buf_push(RingBuffer *rb, uint8_t byte)
{
    if (ring_buf_is_full(rb)) return false;
    rb->buffer[rb->write_index] = byte;
    rb->write_index = (rb->write_index + 1) % rb->size;
    return true;
}

bool ring_buf_pop(RingBuffer *rb, uint8_t *output)
{
    if (ring_buf_is_empty(rb)) return false;
    *output = rb->buffer[rb->read_index];
    rb->read_index = (rb->read_index + 1) % rb->size;
    return true;
}

void ring_buf_visualize(const RingBuffer *rb)
{
    for (size_t i = 0; i < rb->size; i++) {
        if (rb->write_index >= rb->read_index)
            printf("%c ", i < rb->write_index && i >= rb->read_index ? rb->buffer[i] : '_');
        else if (rb->write_index < rb->read_index)
            printf("%c ", i < rb->write_index || i >= rb->read_index ? rb->buffer[i] : '_');
    }
    printf("\nwrite_index: %lu, read_index: %lu\n", rb->write_index, rb->read_index);
}
