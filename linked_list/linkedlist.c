#include "linkedlist.h"
#include "../arena_allocator/arena.h" // TODO: dont use relative path
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

bool linked_list_init(Arena *allocator, LinkedList *list, uint8_t value)
{
    if (allocator == NULL || list == NULL) return false;
    list->allocator = allocator;
    list->values = arena_alloc(list->allocator, sizeof(LinkedListNode));
    list->values->value = value;
    list->values->next = NULL;
    list->size = 1;
    return true;
}

bool linked_list_push(LinkedList *list, uint8_t value)
{
    if (list == NULL || list->values == NULL) return false;

    LinkedListNode *new_node = arena_alloc(list->allocator, sizeof(LinkedListNode));
    if (new_node == NULL) return false; // TODO: handle better
    new_node->value = value;
    new_node->next = NULL;
    
    LinkedListNode *last = list->values;
    while (last->next != NULL) last = last->next;
    last->next = new_node;

    list->size++;
    return true;
}

LinkedListNode *linked_list_get(const LinkedList *list, size_t index)
{
    if (list == NULL || list->values == NULL) return NULL;
    if (index > list->size - 1) return NULL;
    LinkedListNode *node = list->values;
    while (index--) node = node->next;
    return node;
}

bool linked_list_delete(LinkedList *list, size_t index)
{
    if (list == NULL || list->values == NULL) return false;
    if (index > list->size - 1) return false;
    if (index == 0) {
        list->values = list->values->next;
        list->size--;
        return true;
    }
    LinkedListNode *prev_node = linked_list_get(list, index - 1);
    if (prev_node == NULL) return false;

    LinkedListNode *deleted_node = prev_node->next;
    prev_node->next = prev_node->next->next;
    deleted_node->next = NULL;

    list->size--;
    return true;
}
