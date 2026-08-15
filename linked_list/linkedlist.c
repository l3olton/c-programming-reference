#include "linkedlist.h"
#include "../arena_allocator/arena.h" // TODO: dont use relative path
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
    LinkedListNode *head;
    LinkedListNode *free_nodes; // maybe better as global node pool, that can be passed to multiple lists
    size_t size;
};

LinkedList *linked_list_new(Arena *allocator, const uint8_t value)
{
    if (allocator == NULL) return NULL;

    LinkedList *list = arena_alloc(allocator, sizeof(LinkedList));
    if (list == NULL) return NULL;

    list->allocator = allocator;

    // TODO: maybe initialize without any nodes
    list->head = arena_alloc(list->allocator, sizeof(LinkedListNode));
    if (list->head == NULL) {
        list = NULL;
        return NULL;
    }

    list->head->next = NULL;
    list->head->value = value;
    list->size = 1;

    return list;
}

static LinkedListNode *get_free_node(LinkedList *list)
{
    if (list == NULL || list->free_nodes == NULL) return NULL;

    LinkedListNode *free_node = list->free_nodes;
    list->free_nodes = list->free_nodes->next;
    free_node->next = NULL;

    return free_node;
}

bool linked_list_append(LinkedList *list, const uint8_t value)
{
    if (list == NULL || list->head == NULL) return false;

    LinkedListNode *new_node = get_free_node(list);
    if (new_node == NULL)
        new_node = arena_alloc(list->allocator, sizeof(LinkedListNode));

    if (new_node == NULL) return false; // TODO: handle better
    new_node->value = value;
    new_node->next = NULL;
    
    LinkedListNode *last = list->head;
    while (last->next != NULL) last = last->next;
    last->next = new_node;

    list->size++;
    return true;
}

bool linked_list_prepend(LinkedList *list, const uint8_t value)
{
    if (list == NULL || list->head == NULL) return false;

    LinkedListNode *new_node = get_free_node(list);
    if (new_node == NULL)
        new_node = arena_alloc(list->allocator, sizeof(LinkedListNode));

    if (new_node == NULL) return false;

    LinkedListNode *first = list->head;
    new_node->next = first;
    new_node->value = value;

    list->head = new_node;
    list->size++;

    return true;
}

static LinkedListNode *linked_list_get_node(const LinkedList *list, size_t index)
{
    if (list == NULL || list->head == NULL) return NULL;
    if (index > list->size - 1) return NULL;
    LinkedListNode *node = list->head;
    while (index--) node = node->next;
    return node;
}

bool linked_list_get(const LinkedList *list, size_t index, uint8_t *out)
{
    const LinkedListNode *node = linked_list_get_node(list, index);
    if (node == NULL) return false;
    *out = node->value;
    return true;
}

bool linked_list_update(const LinkedList *list, const size_t index, const uint8_t value)
{
    if (list == NULL || list->head == NULL) return false;
    if (index > list->size - 1) return false;
    LinkedListNode *node = linked_list_get_node(list, index);
    if (node == NULL) return false;
    node->value = value;
    return true;
}

bool linked_list_node_update(LinkedListNode *node, uint8_t value)
{
    if (node == NULL) return false;
    node->value = value;
    return true;
}

static bool free_node(LinkedList *list, LinkedListNode *node)
{
    if (list == NULL || node == NULL) return false;

    node->value = 0; // TODO: use NULL when using void *
    node->next = NULL;

    if (!list->free_nodes) {
        list->free_nodes = node;
        return true;
    }

    LinkedListNode *last = list->free_nodes;
    while (last->next) last = last->next;
    last->next = node;

    return true;
}

bool linked_list_delete(LinkedList *list, const size_t index)
{
    if (list == NULL || list->head == NULL) return false;
    if (index > list->size - 1) return false;
    LinkedListNode *delete_node = NULL;
    if (index == 0) {
        delete_node = list->head;
        list->head = list->head->next;
        free_node(list, delete_node);
        list->size--;
        return true;
    }

    LinkedListNode *prev_node = linked_list_get_node(list, index - 1);
    if (prev_node == NULL) return false;

    delete_node = prev_node->next;
    prev_node->next = prev_node->next->next;
    free_node(list, delete_node);

    list->size--;
    return true;
}

bool linked_list_node_delete(LinkedList *list, const LinkedListNode *node)
{
    if (list == NULL || node == NULL) return false;

    LinkedListNode *delete_node = NULL;

    if (node == list->head) {
        delete_node = list->head;
        list->head = list->head->next;
        free_node(list, delete_node);
        list->size--;
        return true;
    }

    for (LinkedListNode *n = list->head; n != NULL; n = n->next)
        if (n->next == node) {
            delete_node = n->next;
            n->next = n->next->next;
            free_node(list, delete_node);
            list->size--;
            return true;
        }

    return false;
}

LinkedListNode *linked_list_head(const LinkedList *list)
{
    return list->head;
}

LinkedListNode *linked_list_next(const LinkedListNode *node)
{
    return node->next;
}

size_t linked_list_size(const LinkedList *list)
{
    return list->size;
}

uint8_t linked_list_node_value(const LinkedListNode *node)
{
    return node->value;
}

void linked_list_foreach(const LinkedList *list, const ForEachFn cb, void *user_data)
{
    if (list == NULL || cb == NULL) return;
    for (const LinkedListNode *node = list->head; node != NULL; node = node->next)
        if (!cb(node->value, user_data))
            break;
}

void linked_list_foreach_node(const LinkedList *list, const ForEachNodeFn cb, void *user_data)
{
    if (list == NULL || cb == NULL) return;

    const LinkedListNode *node = list->head;
    while (node != NULL) {
        const LinkedListNode *next = node->next;
        if (!cb(node, user_data))
            break;
        node = next;
    }
}

void linked_list_visualize(const LinkedList *list)
{
    for (const LinkedListNode *node = list->head; node != NULL; node = node->next)
        printf("%d ", node->value);
    printf("\nsize: %zu\n", list->size);
    size_t free_length = 0;
    for (const LinkedListNode *free = list->free_nodes; free != NULL; free = free->next)
        free_length++;
    printf("free list length: %zu\n\n", free_length);
}
