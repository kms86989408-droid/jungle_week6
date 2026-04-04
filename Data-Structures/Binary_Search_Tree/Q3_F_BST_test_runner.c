#define main q3_f_bst_original_main
#include "Q3_F_BST.c"
#undef main

#include "../test_runner_output.h"

typedef struct {
    BSTNode *root;
} TraversalCtx;

static void build_bst(BSTNode **root, const int *values, int count)
{
    int i;

    *root = NULL;
    for (i = 0; i < count; i++) {
        insertBSTNode(root, values[i]);
    }
}

static void run_pre_order(void *ctx)
{
    TraversalCtx *traversal = (TraversalCtx *)ctx;
    preOrderIterative(traversal->root);
}

int main(void)
{
    int failures = 0;
    char output[256];
    TraversalCtx ctx;
    BSTNode *root = NULL;
    const int values[] = {20, 15, 50, 10, 18, 25, 80};

    build_bst(&root, values, 7);
    ctx.root = root;
    capture_output(run_pre_order, &ctx, output, sizeof(output));
    failures += expect_string("BST Q3 pre-order traversal", output, "20 15 10 18 50 25 80 ");
    removeAll(&root);

    if (failures == 0) {
        printf("\nAll BST Q3 tests passed.\n");
        return 0;
    }

    printf("\nBST Q3 tests failed: %d\n", failures);
    return 1;
}
