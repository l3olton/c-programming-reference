#include "linkedlist.h"
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    int64_t start_index;
    int64_t result_index;
    uint8_t search_val;
} Query;

static bool sum_all(uint8_t value, void *user_data);
static bool find_largest(uint8_t value, void *user_data);
static bool find(uint8_t value, void *user_data);
static bool delete_node(const LinkedListNode *node, void *user_data);

int main(void)
{
    Arena allocator = {0};
    const size_t allocator_size = 1024 * 256; // 256 KiB
    uint8_t allocator_buffer[allocator_size];
    if (!arena_init(&allocator, allocator_buffer, allocator_size)) {
        printf("Error initializing arena allocator\n");
        return 1;
    }

    LinkedList *list = linked_list_new(&allocator, 1);
    if (!list) {
        printf("Error initializing linked list\n");
        return 1;
    }

    for (uint8_t i = 2; i <= 10; i++) {
        if (!linked_list_append(list, i)) {
            printf("Error pushing to linked list\n");
            return 1;
        }
        linked_list_visualize(list);
    }

    linked_list_visualize(list);

    uint8_t val3;
    bool success = linked_list_get(list, 2, &val3);
    if (success) printf("3rd node value: %d\n", val3);

    uint8_t val20;
    success = linked_list_get(list, 20, &val20);
    if (!success) printf("index 20 is out of bounds\n");

    linked_list_visualize(list);

    if (!linked_list_delete(list, 2))
        printf("Error deleting 3rd item from list\n");
    if (!linked_list_delete(list, 7))
        printf("Error deleting 8th item from list\n");
    if (!linked_list_delete(list, 0))
        printf("Error deleting 1st item from list\n");

    linked_list_visualize(list);

    if (linked_list_update(list, 4, 12))
        printf("item at index 4 updated\n");

    if (!linked_list_update(list, 10, 20))
        printf("index 10 out of bounds\n");

    linked_list_visualize(list);

    if (!linked_list_prepend(list, 1)) printf("Error prepending to list\n");

    linked_list_visualize(list);

    size_t i = 0;
    for (LinkedListNode *n = linked_list_head(list); n != NULL; n = linked_list_next(n))
        linked_list_update(list, i++, linked_list_node_value(n) * 10);

    linked_list_visualize(list);

    size_t total = 0;
    linked_list_foreach(list, sum_all, &total);
    printf("total: %zu\n", total);

    size_t largest = 0;
    linked_list_foreach(list, find_largest, &largest);
    printf("largest: %zu\n", largest);

    Query query = {
        .start_index = 0,
        .result_index = -1,
        .search_val = 50
    };
    linked_list_foreach(list, find, &query);
    printf("50 found at index: %ld\n", query.result_index);

    Query query2 = { 0, -1, 51 };
    linked_list_foreach(list, find, &query2);
    if (query2.result_index < 0)
        printf("value 51 not found in list\n");

    printf("arena length: %zu, offset: %zu\n", allocator.length, allocator.offset);

    LinkedList *list2 = linked_list_new(&allocator, 1);

    for (i = 1; i < 10000; i++)
        linked_list_append(list2, 1);

    linked_list_visualize(list2);

    linked_list_foreach_node(list2, delete_node, list2);

    linked_list_visualize(list2);

    double_t used = (double_t)allocator.offset / (double_t)allocator.length * 100;
    printf("arena length: %zu, offset: %zu, %f%%\n", allocator.length, allocator.offset, used);

    for (i = 1; i < 10000; i++)
        linked_list_append(list, 1);

    linked_list_visualize(list);

    used = (double_t)allocator.offset / (double_t)allocator.length * 100;
    printf("arena length: %zu, offset: %zu, %f%%\n", allocator.length, allocator.offset, used);

    return 0;
}

bool sum_all(const uint8_t value, void *user_data)
{
    size_t *total = user_data;
    *total += value;
    return true;
}

bool find_largest(const uint8_t value, void *user_data)
{
    size_t *largest = user_data;
    if (value > *largest) *largest = value;
    return true;
}

bool find(const uint8_t value, void *user_data)
{
    Query *query = user_data;
    if (value == query->search_val) {
        query->result_index = query->start_index;
        return false;
    }
    query->start_index++;
    return true;
}

bool delete_node(const LinkedListNode *node, void *user_data)
{
    LinkedList *list = user_data;
    if (node != linked_list_head(list))
        linked_list_node_delete(list, node); // TODO: should check failure
    return true;
}
