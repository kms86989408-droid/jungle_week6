#define main q5_e_bt_original_main
#include "Q5_E_BT.c"
#undef main

#include "../test_runner_output.h"

typedef struct {
    BTNode *root;
} TreeCtx;

static BTNode *build_mirror_tree(void)
{
    BTNode *root = createBTNode(4);
    root->left = createBTNode(5);
    root->right = createBTNode(2);
    root->left->right = createBTNode(6);
    root->right->left = createBTNode(3);
    root->right->right = createBTNode(1);
    return root;
}

static void run_print_tree(void *ctx)
{
    TreeCtx *tree = (TreeCtx *)ctx;
    printTree(tree->root);
}

int main(void)
{
    int failures = 0;
    char output[256];
    TreeCtx ctx;
    BTNode *root = build_mirror_tree();

    mirrorTree(root);
    ctx.root = root;
    capture_output(run_print_tree, &ctx, output, sizeof(output));
    failures += expect_string("BT Q5 mirror tree in-order", output, "1 2 3 4 6 5 ");
    removeAll(&root);

    if (failures == 0) {
        printf("\nAll BT Q5 tests passed.\n");
        return 0;
    }

    printf("\nBT Q5 tests failed: %d\n", failures);
    return 1;
}
