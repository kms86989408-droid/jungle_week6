#define main q1_c_sq_original_main
#include "Q1_C_SQ.c"
#undef main

static void build_linked_list(LinkedList *ll, const int *values, int count)
{
    int i;

    ll->head = NULL;
    ll->size = 0;
    for (i = 0; i < count; i++) {
        insertNode(ll, ll->size, values[i]);
    }
}

static int list_matches(LinkedList *ll, const int *expected, int count)
{
    int i;
    ListNode *cur = ll->head;

    if (ll->size != count) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        if (cur == NULL || cur->item != expected[i]) {
            return 0;
        }
        cur = cur->next;
    }
    return cur == NULL;
}

static int expect_list(const char *label, LinkedList *ll, const int *expected, int count)
{
    if (!list_matches(ll, expected, count)) {
        int i;

        printf("[FAIL] %s\n", label);
        printf("  expected: ");
        for (i = 0; i < count; i++) {
            printf("%d ", expected[i]);
        }
        printf("\n  actual:   ");
        printList(ll);
        return 1;
    }

    printf("[PASS] %s\n", label);
    return 0;
}

int main(void)
{
    int failures = 0;
    LinkedList ll = {0, NULL};
    Queue q = {{0, NULL}};

    {
        const int initial[] = {1, 2, 3, 4, 5};
        const int expected_queue[] = {1, 2, 3, 4, 5};
        const int expected_even_only[] = {2, 4};

        build_linked_list(&ll, initial, 5);
        createQueueFromLinkedList(&ll, &q);
        failures += expect_list("SQ Q1 create queue", &q.ll, expected_queue, 5);
        removeOddValues(&q);
        failures += expect_list("SQ Q1 remove odd", &q.ll, expected_even_only, 2);
        removeAllItems(&ll);
        removeAllItemsFromQueue(&q);
    }

    if (failures == 0) {
        printf("\nAll SQ Q1 tests passed.\n");
        return 0;
    }

    printf("\nSQ Q1 tests failed: %d\n", failures);
    return 1;
}
