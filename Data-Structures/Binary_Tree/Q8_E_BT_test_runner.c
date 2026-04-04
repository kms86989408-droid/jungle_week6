#define main q8_e_bt_original_main
#include "Q8_E_BT.c"
#undef main

#include "../test_runner_output.h"

typedef struct {
    BTNode *root;
} GreatGrandCtx;

static BTNode *build_great_grand_tree(void)
{
    BTNode *root = createBTNode(50);
    root->left = createBTNode(30);
    root->right = createBTNode(60);
    root->left->left = createBTNode(25);
    root->left->right = createBTNode(65);
    root->left->right->left = createBTNode(20);
    root->right->left = createBTNode(10);
    root->right->right = createBTNode(75);
    root->right->right->right = createBTNode(15);
    return root;
}

static void run_great_grandchild(void *ctx)
{
    GreatGrandCtx *great = (GreatGrandCtx *)ctx;
    hasGreatGrandchild(great->root);
}

int main(void)
{
    int failures = 0;
    char output[256];
    GreatGrandCtx ctx;
    BTNode *root = build_great_grand_tree();

    ctx.root = root;
    capture_output(run_great_grandchild, &ctx, output, sizeof(output));
    failures += expect_string("BT Q8 great-grandchild nodes", output, "50 ");
    removeAll(&root);

    if (failures == 0) {
        printf("\nAll BT Q8 tests passed.\n");
        return 0;
    }

    printf("\nBT Q8 tests failed: %d\n", failures);
    return 1;
}
