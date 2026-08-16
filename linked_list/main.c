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

static bool sum_all(void *value, void *user_data);
static bool find_largest(void *value, void *user_data);
static bool find(void *value, void *user_data);
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

    uint8_t first = 1;
    LinkedList *list = linked_list_new(&allocator, &first);
    if (!list) {
        printf("Error initializing linked list\n");
        return 1;
    }

    for (uint8_t i = 2; i <= 10; i++) {
        if (!linked_list_append(list, &i)) {
            printf("Error pushing to linked list\n");
            return 1;
        }
        linked_list_visualize(list);
    }

    linked_list_visualize(list);

    // TODO: probably wont work
    uint8_t *val3 = NULL;
    bool success = linked_list_get(list, 2, (void *)&val3);
    if (success) printf("3rd node value: %d\n", *val3);

    uint8_t *val20 = NULL;
    success = linked_list_get(list, 20, (void *)val20);
    if (!success) printf("index 20 is out of bounds\n");

    linked_list_visualize(list);

    if (!linked_list_delete(list, 2))
        printf("Error deleting 3rd item from list\n");
    if (!linked_list_delete(list, 7))
        printf("Error deleting 8th item from list\n");
    if (!linked_list_delete(list, 0))
        printf("Error deleting 1st item from list\n");

    linked_list_visualize(list);

    uint8_t put4 = 12;
    if (linked_list_update(list, 4, &put4))
        printf("item at index 4 updated\n");

    uint8_t put10 = 20;
    if (!linked_list_update(list, 10, &put10))
        printf("index 10 out of bounds\n");

    linked_list_visualize(list);

    uint8_t pre1 = 1;
    if (!linked_list_prepend(list, &pre1)) printf("Error prepending to list\n");

    linked_list_visualize(list);

    size_t i = 0;
    for (LinkedListNode *n = linked_list_head(list); n != NULL; n = linked_list_next(n)) {
        uint8_t *value = linked_list_node_value(n);
        uint8_t update_val = *value * 10;
        linked_list_update(list, i++, &update_val);
    }

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

    uint8_t first_val = 1;
    LinkedList *list2 = linked_list_new(&allocator, &first_val);

    for (i = 1; i < 10000; i++)
        linked_list_append(list2, &i);

    linked_list_visualize(list2);

    linked_list_foreach_node(list2, delete_node, list2);

    linked_list_visualize(list2);

    double_t used = (double_t)allocator.offset / (double_t)allocator.length * 100;
    printf("arena length: %zu, offset: %zu, %f%%\n", allocator.length, allocator.offset, used);

    for (i = 1; i < 10000; i++)
        linked_list_append(list, &i);

    linked_list_visualize(list);

    used = (double_t)allocator.offset / (double_t)allocator.length * 100;
    printf("arena length: %zu, offset: %zu, %f%%\n", allocator.length, allocator.offset, used);

    return 0;
}

bool sum_all(void *value, void *user_data)
{
    uint8_t *val = value;
    size_t *total = user_data;
    *total += *val;
    return true;
}

bool find_largest(void *value, void *user_data)
{
    uint8_t *val = value;
    size_t *largest = user_data;
    if (*val > *largest) *largest = *val;
    return true;
}

bool find(void *value, void *user_data)
{
    uint8_t *val = value;
    Query *query = user_data;
    if (*val == query->search_val) {
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
