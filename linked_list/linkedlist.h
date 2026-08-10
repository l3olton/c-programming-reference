#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "../arena_allocator/arena.h" // TODO: dont use relative path
#include <stdint.h>

typedef struct LinkedListNode {
    // TODO: make generic
    uint8_t value;
    struct LinkedListNode *next;
} LinkedListNode;

typedef struct {
    Arena *allocator;
    LinkedListNode *values;
    size_t size;
} LinkedList;

bool linked_list_init(Arena *allocator, LinkedList *list, uint8_t value);

bool linked_list_push(LinkedList *list, uint8_t value);

LinkedListNode *linked_list_get(const LinkedList *list, size_t index);

bool linked_list_delete(LinkedList *list, size_t index);

#endif
