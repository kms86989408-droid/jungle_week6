#define main q5_a_ll_original_main
#include "Q5_A_LL.c"
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
    LinkedList front = {0, NULL};
    LinkedList back = {0, NULL};

    {
        const int initial[] = {2, 3, 5, 6, 7};
        const int expected_front[] = {2, 3, 5};
        const int expected_back[] = {6, 7};

        build_list(&ll, initial, 5);
        front.head = NULL;
        front.size = 0;
        back.head = NULL;
        back.size = 0;
        frontBackSplitLinkedList(&ll, &front, &back);
        failures += expect_list("Q5 odd front list", &front, expected_front, 3);
        failures += expect_list("Q5 odd back list", &back, expected_back, 2);
        removeAllItems(&front);
        removeAllItems(&back);
        ll.head = NULL;
        ll.size = 0;
    }

    {
        const int initial[] = {1, 2, 3, 4};
        const int expected_front[] = {1, 2};
        const int expected_back[] = {3, 4};

        build_list(&ll, initial, 4);
        front.head = NULL;
        front.size = 0;
        back.head = NULL;
        back.size = 0;
        frontBackSplitLinkedList(&ll, &front, &back);
        failures += expect_list("Q5 even front list", &front, expected_front, 2);
        failures += expect_list("Q5 even back list", &back, expected_back, 2);
        removeAllItems(&front);
        removeAllItems(&back);
        ll.head = NULL;
        ll.size = 0;
    }

    {
        const int expected_front[] = {42};

        build_list(&ll, expected_front, 1);
        front.head = NULL;
        front.size = 0;
        back.head = NULL;
        back.size = 0;
        frontBackSplitLinkedList(&ll, &front, &back);
        failures += expect_list("Q5 single front list", &front, expected_front, 1);
        failures += expect_list("Q5 single back list", &back, NULL, 0);
        removeAllItems(&front);
        removeAllItems(&back);
        ll.head = NULL;
        ll.size = 0;
    }

    if (failures == 0) {
        printf("\nAll Q5 tests passed.\n");
        return 0;
    }

    printf("\nQ5 tests failed: %d\n", failures);
    return 1;
}
