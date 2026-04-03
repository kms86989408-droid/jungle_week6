#define main q2_a_ll_original_main
#include "Q2_A_LL.c"
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
    LinkedList ll1 = {0, NULL};
    LinkedList ll2 = {0, NULL};

    {
        const int initial1[] = {1, 2, 3};
        const int initial2[] = {4, 5, 6, 7};
        const int expected1[] = {1, 4, 2, 5, 3, 6};
        const int expected2[] = {7};

        build_list(&ll1, initial1, 3);
        build_list(&ll2, initial2, 4);
        alternateMergeLinkedList(&ll1, &ll2);
        failures += expect_list("Q2 example ll1", &ll1, expected1, 6);
        failures += expect_list("Q2 example ll2", &ll2, expected2, 1);
        removeAllItems(&ll1);
        removeAllItems(&ll2);
    }

    {
        const int initial1[] = {1, 5, 7, 3, 9, 11};
        const int initial2[] = {6, 10, 2, 4};
        const int expected1[] = {1, 6, 5, 10, 7, 2, 3, 4, 9, 11};

        build_list(&ll1, initial1, 6);
        build_list(&ll2, initial2, 4);
        alternateMergeLinkedList(&ll1, &ll2);
        failures += expect_list("Q2 longer first list ll1", &ll1, expected1, 10);
        failures += expect_list("Q2 longer first list ll2", &ll2, NULL, 0);
        removeAllItems(&ll1);
        removeAllItems(&ll2);
    }

    {
        const int initial2[] = {4, 5};
        const int expected2[] = {4, 5};

        build_list(&ll1, NULL, 0);
        build_list(&ll2, initial2, 2);
        alternateMergeLinkedList(&ll1, &ll2);
        failures += expect_list("Q2 empty first list ll1", &ll1, NULL, 0);
        failures += expect_list("Q2 empty first list ll2", &ll2, expected2, 2);
        removeAllItems(&ll1);
        removeAllItems(&ll2);
    }

    if (failures == 0) {
        printf("\nAll Q2 tests passed.\n");
        return 0;
    }

    printf("\nQ2 tests failed: %d\n", failures);
    return 1;
}
