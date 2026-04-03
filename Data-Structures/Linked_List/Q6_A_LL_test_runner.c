#define main q6_a_ll_original_main
#include "Q6_A_LL.c"
#undef main

static void build_list_from_head(ListNode **head, const int *values, int count)
{
    int i;
    ListNode *tail = NULL;

    *head = NULL;
    for (i = 0; i < count; i++) {
        ListNode *node = malloc(sizeof(ListNode));
        node->item = values[i];
        node->next = NULL;

        if (*head == NULL) {
            *head = node;
        } else {
            tail->next = node;
        }
        tail = node;
    }
}

static void free_list_from_head(ListNode **head)
{
    ListNode *cur = *head;

    while (cur != NULL) {
        ListNode *next = cur->next;
        free(cur);
        cur = next;
    }

    *head = NULL;
}

static int list_matches_head(ListNode *head, const int *expected, int count)
{
    int i;
    ListNode *cur = head;

    for (i = 0; i < count; i++) {
        if (cur == NULL || cur->item != expected[i]) {
            return 0;
        }
        cur = cur->next;
    }

    return cur == NULL;
}

static void print_head_list(ListNode *head)
{
    ListNode *cur = head;

    if (cur == NULL) {
        printf("Empty / 비어 있음\n");
        return;
    }

    while (cur != NULL) {
        printf("%d ", cur->item);
        cur = cur->next;
    }
    printf("\n");
}

static int expect_head_list(const char *label, ListNode *head, const int *expected, int count)
{
    if (!list_matches_head(head, expected, count)) {
        int i;

        printf("[FAIL] %s\n", label);
        printf("  expected: ");
        for (i = 0; i < count; i++) {
            printf("%d ", expected[i]);
        }
        printf("\n  actual:   ");
        print_head_list(head);
        return 1;
    }

    printf("[PASS] %s\n", label);
    return 0;
}

int main(void)
{
    int failures = 0;
    ListNode *head = NULL;

    {
        const int initial[] = {30, 20, 40, 70, 50};
        const int expected[] = {70, 30, 20, 40, 50};

        build_list_from_head(&head, initial, 5);
        moveMaxToFront(&head);
        failures += expect_head_list("Q6 move max from middle", head, expected, 5);
        free_list_from_head(&head);
    }

    {
        const int initial[] = {9, 1, 2};
        const int expected[] = {9, 1, 2};

        build_list_from_head(&head, initial, 3);
        moveMaxToFront(&head);
        failures += expect_head_list("Q6 max already front", head, expected, 3);
        free_list_from_head(&head);
    }

    {
        moveMaxToFront(&head);
        failures += expect_head_list("Q6 empty list", head, NULL, 0);
    }

    if (failures == 0) {
        printf("\nAll Q6 tests passed.\n");
        return 0;
    }

    printf("\nQ6 tests failed: %d\n", failures);
    return 1;
}
