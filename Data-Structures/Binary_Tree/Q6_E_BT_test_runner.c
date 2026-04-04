#define main q6_e_bt_original_main
#include "Q6_E_BT.c"
#undef main

#include "../test_runner_output.h"

typedef struct {
    BTNode *root;
    int value;
} SmallerCtx;

static BTNode *build_smaller_tree(void)
{
    BTNode *root = createBTNode(50);
    root->left = createBTNode(30);
    root->right = createBTNode(60);
    root->left->left = createBTNode(25);
    root->left->right = createBTNode(65);
    root->right->left = createBTNode(10);
    root->right->right = createBTNode(75);
    return root;
}

static void run_smaller_values(void *ctx)
{
    SmallerCtx *smaller = (SmallerCtx *)ctx;
    printSmallerValues(smaller->root, smaller->value);
}

int main(void)
{
    int failures = 0;
    char output[256];
    SmallerCtx ctx;
    BTNode *root = build_smaller_tree();

    ctx.root = root;
    ctx.value = 55;
    capture_output(run_smaller_values, &ctx, output, sizeof(output));
    failures += expect_string("BT Q6 print smaller values", output, "50 30 25 10 ");
    removeAll(&root);

    if (failures == 0) {
        printf("\nAll BT Q6 tests passed.\n");
        return 0;
    }

    printf("\nBT Q6 tests failed: %d\n", failures);
    return 1;
}
