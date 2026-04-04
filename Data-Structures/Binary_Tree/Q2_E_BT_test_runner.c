#define main q2_e_bt_original_main
#include "Q2_E_BT.c"
#undef main

#include "../test_runner_output.h"

static BTNode *build_height_tree(void)
{
    BTNode *root = createBTNode(4);
    root->left = createBTNode(2);
    root->right = createBTNode(6);
    root->left->left = createBTNode(1);
    root->left->right = createBTNode(3);
    root->right->left = createBTNode(5);
    root->right->right = createBTNode(7);
    return root;
}

int main(void)
{
    int failures = 0;
    BTNode *root = build_height_tree();

    failures += expect_int_value("BT Q2 balanced tree height", maxHeight(root), 2);
    failures += expect_int_value("BT Q2 empty tree height", maxHeight(NULL), -1);
    removeAll(&root);

    if (failures == 0) {
        printf("\nAll BT Q2 tests passed.\n");
        return 0;
    }

    printf("\nBT Q2 tests failed: %d\n", failures);
    return 1;
}
