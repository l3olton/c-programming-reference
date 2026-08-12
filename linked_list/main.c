#include "linkedlist.h"
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    Arena allocator = {0};
    size_t allocator_size = 1024;
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

    return 0;
}
