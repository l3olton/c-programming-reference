#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "../arena_allocator/arena.h" // TODO: dont use relative path
#include <stdint.h>

typedef struct LinkedListNode_s LinkedListNode;

typedef struct LinkedList_s LinkedList;

LinkedList *linked_list_new(Arena *allocator, uint8_t value);

bool linked_list_push(LinkedList *list, uint8_t value);

bool linked_list_get(const LinkedList *list, size_t index, uint8_t *out);

bool linked_list_update(const LinkedList *list, size_t index, uint8_t value);

bool linked_list_delete(LinkedList *list, size_t index);

void linked_list_visualize(const LinkedList *list);

#endif
