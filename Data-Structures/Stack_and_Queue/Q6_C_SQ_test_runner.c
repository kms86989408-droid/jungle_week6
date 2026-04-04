#define main q6_c_sq_original_main
#include "Q6_C_SQ.c"
#undef main

static void build_stack(Stack *s, const int *top_order_values, int count)
{
    int i;

    s->ll.head = NULL;
    s->ll.size = 0;
    for (i = count - 1; i >= 0; i--) {
        push(s, top_order_values[i]);
    }
}

static int stack_matches(Stack *s, const int *expected, int count)
{
    int i;
    ListNode *cur = s->ll.head;

    if (s->ll.size != count) {
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

static int expect_stack(const char *label, Stack *s, const int *expected, int count)
{
    if (!stack_matches(s, expected, count)) {
        int i;

        printf("[FAIL] %s\n", label);
        printf("  expected: ");
        for (i = 0; i < count; i++) {
            printf("%d ", expected[i]);
        }
        printf("\n  actual:   ");
        printList(&(s->ll));
        return 1;
    }

    printf("[PASS] %s\n", label);
    return 0;
}

int main(void)
{
    int failures = 0;
    Stack s = {{0, NULL}};

    {
        const int initial[] = {1, 2, 3, 4, 5, 6, 7};
        const int expected[] = {4, 5, 6, 7};

        build_stack(&s, initial, 7);
        removeUntil(&s, 4);
        failures += expect_stack("SQ Q6 remove until 4", &s, expected, 4);
        removeAllItems(&(s.ll));
    }

    {
        const int initial[] = {10, 20, 15, 25, 5};
        const int expected[] = {15, 25, 5};

        build_stack(&s, initial, 5);
        removeUntil(&s, 15);
        failures += expect_stack("SQ Q6 remove until 15", &s, expected, 3);
        removeAllItems(&(s.ll));
    }

    if (failures == 0) {
        printf("\nAll SQ Q6 tests passed.\n");
        return 0;
    }

    printf("\nSQ Q6 tests failed: %d\n", failures);
    return 1;
}
