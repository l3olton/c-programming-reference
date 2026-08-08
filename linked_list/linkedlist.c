#include "linkedlist.h"
#include "../arena_allocator/arena.h" // TODO: dont use relative path
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

bool linked_list_init(Arena *allocator, LinkedListNode *list, uint8_t value)
{
    if (list == NULL) return false;
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

bool linked_list_get_val(LinkedListNode *list, size_t index, uint8_t *output)
{
    if (list == NULL || output == NULL) return false;
    LinkedListNode *node = list;
    while (index--) node = node->next;
    *output = node->value;
    return true;
}

bool linked_list_get_node(LinkedListNode *list, size_t index, LinkedListNode *output)
{
    if (list == NULL || output == NULL) return false;
    *output = *list;
    while (index--) *output = *output->next;
    return true;
}
