#define main q4_e_bt_original_main
#include "Q4_E_BT.c"
#undef main

#include "../test_runner_output.h"

static BTNode *build_sum_tree(void)
{
    BTNode *root = createBTNode(50);
    root->left = createBTNode(40);
    root->right = createBTNode(60);
    root->left->left = createBTNode(11);
    root->left->right = createBTNode(35);
    root->right->left = createBTNode(80);
    root->right->right = createBTNode(85);
    return root;
}

int main(void)
{
    int failures = 0;
    BTNode *root = build_sum_tree();

    failures += expect_int_value("BT Q4 sum of odd nodes", sumOfOddNodes(root), 131);
    removeAll(&root);

    if (failures == 0) {
        printf("\nAll BT Q4 tests passed.\n");
        return 0;
    }

    printf("\nBT Q4 tests failed: %d\n", failures);
    return 1;
}
