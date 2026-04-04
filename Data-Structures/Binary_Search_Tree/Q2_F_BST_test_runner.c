#define main q2_f_bst_original_main
#include "Q2_F_BST.c"
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

static void run_in_order(void *ctx)
{
    TraversalCtx *traversal = (TraversalCtx *)ctx;
    inOrderTraversal(traversal->root);
}

int main(void)
{
    int failures = 0;
    char output[256];
    TraversalCtx ctx;
    BSTNode *root = NULL;
    const int values[] = {20, 15, 50, 10, 18};

    build_bst(&root, values, 5);
    ctx.root = root;
    capture_output(run_in_order, &ctx, output, sizeof(output));
    failures += expect_string("BST Q2 in-order traversal", output, "10 15 18 20 50 ");
    removeAll(&root);

    if (failures == 0) {
        printf("\nAll BST Q2 tests passed.\n");
        return 0;
    }

    printf("\nBST Q2 tests failed: %d\n", failures);
    return 1;
}
