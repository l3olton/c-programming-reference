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

    uint8_t val_output;
    linked_list_get_val(&list, 2, &val_output);
    printf("%d\n", val_output);

    LinkedListNode node_output;
    linked_list_get_node(&list, 2, &node_output);
    printf("%d\n", node_output.value);

    for (LinkedListNode *node = &list; node != NULL; node = node->next)
        printf("%d ", node->value);
    putchar('\n');

    return 0;
}
