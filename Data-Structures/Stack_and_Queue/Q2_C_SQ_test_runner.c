#define main q2_c_sq_original_main
#include "Q2_C_SQ.c"
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
    Stack s = {{0, NULL}};

    {
        const int initial[] = {1, 3, 5, 6, 7};
        const int expected_stack[] = {7, 6, 5, 3, 1};
        const int expected_after_remove[] = {7, 5, 3, 1};

        build_linked_list(&ll, initial, 5);
        createStackFromLinkedList(&ll, &s);
        failures += expect_list("SQ Q2 create stack", &(s.ll), expected_stack, 5);
        removeEvenValues(&s);
        failures += expect_list("SQ Q2 remove even", &(s.ll), expected_after_remove, 4);
        removeAllItems(&ll);
        removeAllItemsFromStack(&s);
    }

    if (failures == 0) {
        printf("\nAll SQ Q2 tests passed.\n");
        return 0;
    }

    printf("\nSQ Q2 tests failed: %d\n", failures);
    return 1;
}
