#define main q7_c_sq_original_main
#include "Q7_C_SQ.c"
#undef main

#include "../test_runner_output.h"

int main(void)
{
    int failures = 0;

    failures += expect_int_value("SQ Q7 balanced expression", balanced("{[]()[]}"), 0);
    failures += expect_int_value("SQ Q7 unbalanced expression", balanced("[({{)])"), 1);
    failures += expect_int_value("SQ Q7 simple balanced", balanced("()"), 0);

    if (failures == 0) {
        printf("\nAll SQ Q7 tests passed.\n");
        return 0;
    }

    printf("\nSQ Q7 tests failed: %d\n", failures);
    return 1;
}
