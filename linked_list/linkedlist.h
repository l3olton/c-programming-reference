#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "../arena_allocator/arena.h" // TODO: dont use relative path
#include <stdint.h>

typedef struct LinkedListNode {
    // TODO: make generic
    uint8_t value;
    struct LinkedListNode *next;
    Arena *allocator;
} LinkedListNode;

bool linked_list_init(Arena *allocator, LinkedListNode *list, uint8_t value);

bool linked_list_push(LinkedListNode *list, uint8_t value);

bool linked_list_get_val(LinkedListNode *list, size_t index, uint8_t *output);

bool linked_list_get_node(LinkedListNode *list, size_t index, LinkedListNode *output);

#endif
