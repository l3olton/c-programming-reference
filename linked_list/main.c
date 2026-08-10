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

    LinkedListNode list = {0};
    if (!linked_list_init(&allocator, &list, 1)) {
        printf("Error initializing linked list\n");
        return 1;
    }

    for (uint8_t i = 2; i <= 10; i++) {
        if (!linked_list_push(&list, i)) {
            printf("Error pushing to linked list\n");
            return 1;
        }
    }

    for (LinkedListNode *node = &list; node != NULL; node = node->next)
        printf("%d ", node->value);
    putchar('\n');

    LinkedListNode *third_node = linked_list_get_node(&list, 2);
    printf("3rd node value: %d\n", third_node->value);

    for (LinkedListNode *node = &list; node != NULL; node = node->next)
        printf("%d ", node->value);
    putchar('\n');

    if (!linked_list_delete(&list, 2))
        printf("Error deleting 3rd item from list\n");
    if (!linked_list_delete(&list, 7))
        printf("Error deleting 8th item from list\n");

    for (LinkedListNode *node = &list; node != NULL; node = node->next)
        printf("%d ", node->value);
    putchar('\n');

    return 0;
}
