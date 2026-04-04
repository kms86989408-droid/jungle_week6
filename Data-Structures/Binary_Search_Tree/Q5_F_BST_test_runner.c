#define main q5_f_bst_original_main
#include "Q5_F_BST.c"
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

static void run_post_order_s2(void *ctx)
{
    TraversalCtx *traversal = (TraversalCtx *)ctx;
    postOrderIterativeS2(traversal->root);
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
    capture_output(run_post_order_s2, &ctx, output, sizeof(output));
    failures += expect_string("BST Q5 post-order traversal", output, "10 18 15 25 80 50 20 ");
    removeAll(&root);

    if (failures == 0) {
        printf("\nAll BST Q5 tests passed.\n");
        return 0;
    }

    printf("\nBST Q5 tests failed: %d\n", failures);
    return 1;
}
