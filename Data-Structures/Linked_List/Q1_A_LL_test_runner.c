#define main q1_a_ll_original_main
#include "Q1_A_LL.c"
#undef main

static void reset_list(LinkedList *ll)
{
    removeAllItems(ll);
}

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

static int expect_int(const char *label, int actual, int expected)
{
    if (actual != expected) {
        printf("[FAIL] %s: expected %d, got %d\n", label, expected, actual);
        return 1;
    }

    printf("[PASS] %s\n", label);
    return 0;
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
    int result;
    LinkedList ll = {0, NULL};

    {
        const int expected[] = {5};
        reset_list(&ll);
        result = insertSortedLL(&ll, 5);
        failures += expect_int("Q1 empty insert return", result, 0);
        failures += expect_list("Q1 empty insert list", &ll, expected, 1);
    }

    {
        const int initial[] = {2, 3, 5, 7, 9};
        const int expected[] = {2, 3, 5, 7, 8, 9};
        build_list(&ll, initial, 5);
        result = insertSortedLL(&ll, 8);
        failures += expect_int("Q1 middle insert return", result, 4);
        failures += expect_list("Q1 middle insert list", &ll, expected, 6);
    }

    {
        const int initial[] = {5, 7, 9, 11, 15};
        const int expected[] = {5, 7, 9, 11, 15};
        build_list(&ll, initial, 5);
        result = insertSortedLL(&ll, 7);
        failures += expect_int("Q1 duplicate insert return", result, -1);
        failures += expect_list("Q1 duplicate insert list", &ll, expected, 5);
    }

    {
        const int initial[] = {3, 5, 7};
        const int expected[] = {1, 3, 5, 7};
        build_list(&ll, initial, 3);
        result = insertSortedLL(&ll, 1);
        failures += expect_int("Q1 front insert return", result, 0);
        failures += expect_list("Q1 front insert list", &ll, expected, 4);
    }

    removeAllItems(&ll);

    if (failures == 0) {
        printf("\nAll Q1 tests passed.\n");
        return 0;
    }

    printf("\nQ1 tests failed: %d\n", failures);
    return 1;
}
