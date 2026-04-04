#define main q7_e_bt_original_main
#include "Q7_E_BT.c"
#undef main

#include "../test_runner_output.h"

static BTNode *build_smallest_tree(void)
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

int main(void)
{
    int failures = 0;
    BTNode *root = build_smallest_tree();

    failures += expect_int_value("BT Q7 smallest value", smallestValue(root), 10);
    removeAll(&root);

    if (failures == 0) {
        printf("\nAll BT Q7 tests passed.\n");
        return 0;
    }

    printf("\nBT Q7 tests failed: %d\n", failures);
    return 1;
}
