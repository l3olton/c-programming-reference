#include <alloca.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct ListNode_s {
    void *value;
    struct ListNode_s *next;
    struct ListNode_s *prev;
} ListNode;

typedef struct {
    ListNode *head;
    ListNode *tail;
    size_t size;
} List;

typedef struct {
    ListNode *pool;
    ListNode *free_nodes;
    size_t capacity;
    size_t used;
} NodePool;

bool node_pool_init(NodePool *np, ListNode *backing_buffer, size_t size)
{
    if (!np || !backing_buffer) return false;
    np->pool = backing_buffer;
    np->capacity = size;
    np->free_nodes = NULL;
    np->used = 0;
    return true;
}

ListNode *allocate_node(NodePool *np)
{
    // TODO: check free_nodes
    if (np->used <= np->capacity - 1) {
        ListNode *return_ptr = np->pool++;
        np->used++;
        return return_ptr;
    }
    return NULL;
}

List *list_append(List *list, NodePool *np, void* value)
{

}

List *list_init(NodePool *np, void *value)
{

}

bool list_append2(List *list, NodePool *np, void* value)
{
    if (!list || !np || !value) return false;

    List *new_node = allocate_node(np);
    if (!new_node) return false;

    List *last = list;

    while (last->next != NULL) last = last->next;

    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = last;
    last->next = new_node;
    return true;
}

int main(void)
{
    NodePool np = {0};
    size_t pool_size = 10000;
    List pool[pool_size];
    if (!node_pool_init(&np, pool, pool_size)) {
        fprintf(stderr, "Error initializing node pool\n");
        return 1;
    }

    printf("np capacity: %zu, np used: %zu\n", np.capacity, np.used);

    List *list = NULL;

    list = list_append(list, &np, "one");
    list = list_append(list, &np, "two");

    List *list2 = list_init(&np, "a");
    list_append2(list2, &np, "b");
    list_append2(list2, &np, "c");

    for (List *l = list; l != NULL; l = l->next)
        printf("%s ", (char *)l->value);
    putchar('\n');

    for (List *l = list2; l != NULL; l = l->next)
        printf("%s ", (char *)l->value);
    putchar('\n');

    return 0;
}
