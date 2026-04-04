#define main q3_c_sq_original_main
#include "Q3_C_SQ.c"
#undef main

#include "../test_runner_output.h"

static void build_stack(Stack *s, const int *top_order_values, int count)
{
    int i;

    s->ll.head = NULL;
    s->ll.size = 0;
    for (i = count - 1; i >= 0; i--) {
        push(s, top_order_values[i]);
    }
}

int main(void)
{
    int failures = 0;
    Stack s = {{0, NULL}};
    int result;

    {
        const int values[] = {16, 15, 11, 10, 5, 4};
        build_stack(&s, values, 6);
        result = isStackPairwiseConsecutive(&s);
        failures += expect_int_value("SQ Q3 consecutive stack", result, 1);
        removeAllItems(&(s.ll));
    }

    {
        const int values[] = {16, 15, 11, 10, 5, 1};
        build_stack(&s, values, 6);
        result = isStackPairwiseConsecutive(&s);
        failures += expect_int_value("SQ Q3 non-consecutive stack", result, 0);
        removeAllItems(&(s.ll));
    }

    {
        const int values[] = {16, 15, 11, 10, 5};
        build_stack(&s, values, 5);
        result = isStackPairwiseConsecutive(&s);
        failures += expect_int_value("SQ Q3 odd-sized stack", result, 0);
        removeAllItems(&(s.ll));
    }

    if (failures == 0) {
        printf("\nAll SQ Q3 tests passed.\n");
        return 0;
    }

    printf("\nSQ Q3 tests failed: %d\n", failures);
    return 1;
}
