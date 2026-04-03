#define main q4_a_ll_original_main
#include "Q4_A_LL.c"
#undef main

static void build_list(LinkedList *ll, const int *values, int count)
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

    {
        const int initial[] = {2, 3, 4, 7, 15, 18};
        const int expected[] = {3, 7, 15, 2, 4, 18};

        build_list(&ll, initial, 6);
        moveEvenItemsToBack(&ll);
        failures += expect_list("Q4 mixed values", &ll, expected, 6);
        removeAllItems(&ll);
    }

    {
        const int initial[] = {1, 3, 5};
        const int expected[] = {1, 3, 5};

        build_list(&ll, initial, 3);
        moveEvenItemsToBack(&ll);
        failures += expect_list("Q4 all odd", &ll, expected, 3);
        removeAllItems(&ll);
    }

    {
        const int initial[] = {2, 4, 6};
        const int expected[] = {2, 4, 6};

        build_list(&ll, initial, 3);
        moveEvenItemsToBack(&ll);
        failures += expect_list("Q4 all even", &ll, expected, 3);
        removeAllItems(&ll);
    }

    if (failures == 0) {
        printf("\nAll Q4 tests passed.\n");
        return 0;
    }

    printf("\nQ4 tests failed: %d\n", failures);
    return 1;
}
