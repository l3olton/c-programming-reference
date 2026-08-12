#include "linkedlist.h"
#include "../arena_allocator/arena.h" // TODO: dont use relative path
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct LinkedListNode_s {
    // TODO: make generic
    uint8_t value;
    LinkedListNode *next;
};

struct LinkedList_s {
    Arena *allocator;
    LinkedListNode *values;
    size_t size;
};

LinkedList *linked_list_new(Arena *allocator, uint8_t value)
{
    if (allocator == NULL) return NULL;

    LinkedList *list = arena_alloc(allocator, sizeof(LinkedList));
    if (list == NULL) return NULL;

    list->allocator = allocator;

    // TODO: maybe initialize without any nodes
    list->values = arena_alloc(list->allocator, sizeof(LinkedListNode));
    if (list->values == NULL) {
        list = NULL;
        return NULL;
    }

    list->values->next = NULL;
    list->values->value = value;
    list->size = 1;

    return list;
}

bool linked_list_append(LinkedList *list, uint8_t value)
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

bool linked_list_prepend(LinkedList *list, uint8_t value)
{
    if (list == NULL || list->values == NULL) return false;

    LinkedListNode *new_node = arena_alloc(list->allocator, sizeof(LinkedListNode));
    if (new_node == NULL) return false;

    LinkedListNode *first = list->values;
    new_node->next = first;
    new_node->value = value;

    list->values = new_node;
    list->size++;

    return true;
}

static LinkedListNode *linked_list_get_node(const LinkedList *list, size_t index)
{
    if (list == NULL || list->values == NULL) return NULL;
    if (index > list->size - 1) return NULL;
    LinkedListNode *node = list->values;
    while (index--) node = node->next;
    return node;
}

bool linked_list_get(const LinkedList *list, size_t index, uint8_t *out)
{
    LinkedListNode *node = linked_list_get_node(list, index);
    if (node == NULL) return false;
    *out = node->value;
    return true;
}

bool linked_list_update(const LinkedList *list, size_t index, uint8_t value)
{
    if (list == NULL || list->values == NULL) return false;
    if (index > list->size - 1) return false;
    LinkedListNode *node = linked_list_get_node(list, index);
    if (node == NULL) return false;
    node->value = value;
    return true;
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
    LinkedListNode *prev_node = linked_list_get_node(list, index - 1);
    if (prev_node == NULL) return false;

    LinkedListNode *deleted_node = prev_node->next;
    prev_node->next = prev_node->next->next;
    deleted_node->next = NULL;

    list->size--;
    return true;
}

LinkedListNode *linked_list_head(const LinkedList *list)
{
    return linked_list_get_node(list, 0);
}

LinkedListNode *linked_list_next(const LinkedListNode *node)
{
    return node->next;
}

uint8_t linked_list_node_value(const LinkedListNode *node)
{
    return node->value;
}

void linked_list_visualize(const LinkedList *list)
{
    for (LinkedListNode *node = list->values; node != NULL; node = node->next)
        printf("%d ", node->value);
    printf("\nsize: %zu\n\n", list->size);
}
