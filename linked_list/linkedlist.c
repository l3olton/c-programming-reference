#include "linkedlist.h"
#include "../arena_allocator/arena.h" // TODO: dont use relative path
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

bool linked_list_init(Arena *allocator, LinkedListNode *list, uint8_t value)
{
    if (allocator == NULL || list == NULL) return false;
    list->value = value;
    list->next = NULL;
    list->allocator = allocator;
    return true;
}

bool linked_list_push(LinkedListNode *list, uint8_t value)
{
    if (list == NULL) return false;

    LinkedListNode *node = arena_alloc(list->allocator, sizeof(LinkedListNode));
    linked_list_init(list->allocator, node, value);

    LinkedListNode *last = NULL;
    for (last = list; last->next != NULL; last = last->next);
    last->next = node;

    return true;
}

LinkedListNode *linked_list_get_node(LinkedListNode *node, size_t index)
{
    if (node == NULL) return NULL;
    // TODO: check index

    while (index--) node = node->next;
    return node;
}

bool linked_list_delete(LinkedListNode *list, size_t index)
{
    if (list == NULL) return false;
    // TODO: check index
    // TODO: handle first item
    LinkedListNode *prev_node = linked_list_get_node(list, index - 1);
    if (prev_node == NULL) return false;

    prev_node->next = prev_node->next->next;
    return true;
}
