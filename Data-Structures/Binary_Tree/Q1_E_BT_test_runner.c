#define main q1_e_bt_original_main
#include "Q1_E_BT.c"
#undef main

#include "../test_runner_output.h"

static BTNode *build_identical_tree(void)
{
    BTNode *root = createBTNode(5);
    root->left = createBTNode(3);
    root->right = createBTNode(7);
    root->left->left = createBTNode(1);
    root->left->right = createBTNode(2);
    root->right->left = createBTNode(4);
    root->right->right = createBTNode(8);
    return root;
}

int main(void)
{
    int failures = 0;
    BTNode *tree1 = build_identical_tree();
    BTNode *tree2 = build_identical_tree();

    failures += expect_int_value("BT Q1 identical trees", identical(tree1, tree2), 1);
    tree2->right->right->item = 9;
    failures += expect_int_value("BT Q1 different trees", identical(tree1, tree2), 0);

    removeAll(&tree1);
    removeAll(&tree2);

    if (failures == 0) {
        printf("\nAll BT Q1 tests passed.\n");
        return 0;
    }

    printf("\nBT Q1 tests failed: %d\n", failures);
    return 1;
}
