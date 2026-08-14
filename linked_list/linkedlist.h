#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "../arena_allocator/arena.h" // TODO: dont use relative path
#include <stdint.h>

typedef struct LinkedListNode_s LinkedListNode;

typedef struct LinkedList_s LinkedList;

typedef bool (*ForEachFn)(uint8_t value, void *user_data);

LinkedList *linked_list_new(Arena *allocator, uint8_t value);

bool linked_list_append(LinkedList *list, uint8_t value);

bool linked_list_prepend(LinkedList *list, uint8_t value);

LinkedListNode *linked_list_head(const LinkedList *list);

bool linked_list_get(const LinkedList *list, size_t index, uint8_t *out);

bool linked_list_update(const LinkedList *list, size_t index, uint8_t value);

bool linked_list_node_update(LinkedListNode *node, uint8_t value);

bool linked_list_delete(LinkedList *list, size_t index);

bool linked_list_node_delete(LinkedList *list, const LinkedListNode *node);

LinkedListNode *linked_list_next(const LinkedListNode *node);

uint8_t linked_list_node_value(const LinkedListNode *node);

size_t linked_list_size(const LinkedList *list);

void linked_list_foreach(const LinkedList *list, ForEachFn cb, void *user_data);

void linked_list_visualize(const LinkedList *list);

#endif
