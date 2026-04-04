#define main q3_e_bt_original_main
#include "Q3_E_BT.c"
#undef main

#include "../test_runner_output.h"

static BTNode *build_one_child_tree(void)
{
    BTNode *root = createBTNode(50);
    root->left = createBTNode(20);
    root->right = createBTNode(60);
    root->left->left = createBTNode(10);
    root->left->right = createBTNode(30);
    root->left->right->left = createBTNode(55);
    root->right->right = createBTNode(80);
    return root;
}

int main(void)
{
    int failures = 0;
    BTNode *root = build_one_child_tree();

    failures += expect_int_value("BT Q3 one-child nodes", countOneChildNodes(root), 2);
    removeAll(&root);

    if (failures == 0) {
        printf("\nAll BT Q3 tests passed.\n");
        return 0;
    }

    printf("\nBT Q3 tests failed: %d\n", failures);
    return 1;
}
