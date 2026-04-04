#define main q4_c_sq_original_main
#include "Q4_C_SQ.c"
#undef main

static void build_queue(Queue *q, const int *values, int count)
{
    int i;

    q->ll.head = NULL;
    q->ll.tail = NULL;
    q->ll.size = 0;
    for (i = 0; i < count; i++) {
        enqueue(q, values[i]);
    }
}

static int queue_matches(Queue *q, const int *expected, int count)
{
    int i;
    ListNode *cur = q->ll.head;

    if (q->ll.size != count) {
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

static int expect_queue(const char *label, Queue *q, const int *expected, int count)
{
    if (!queue_matches(q, expected, count)) {
        int i;

        printf("[FAIL] %s\n", label);
        printf("  expected: ");
        for (i = 0; i < count; i++) {
            printf("%d ", expected[i]);
        }
        printf("\n  actual:   ");
        printList(&(q->ll));
        return 1;
    }

    printf("[PASS] %s\n", label);
    return 0;
}

int main(void)
{
    int failures = 0;
    Queue q = {{0, NULL, NULL}};

    {
        const int initial[] = {1, 2, 3, 4, 5};
        const int expected[] = {5, 4, 3, 2, 1};

        build_queue(&q, initial, 5);
        reverse(&q);
        failures += expect_queue("SQ Q4 reverse queue", &q, expected, 5);
        removeAllItems(&(q.ll));
    }

    if (failures == 0) {
        printf("\nAll SQ Q4 tests passed.\n");
        return 0;
    }

    printf("\nSQ Q4 tests failed: %d\n", failures);
    return 1;
}
