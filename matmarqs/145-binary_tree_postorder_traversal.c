struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/******************************************/

#include <stdlib.h>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

void treeTraversal(struct TreeNode *root, int *node_values, int *size) {
    int top = -1;
    int capacity = 4;
    struct TreeNode **stack = (struct TreeNode **) malloc(sizeof(struct TreeNode *) * capacity);

    struct TreeNode *node = root;
    struct TreeNode *prev = NULL;

    while (top != -1 || node) {
        while (node) {

            /* preOrderTraversal operation here */

            if (top + 1 >= capacity) {
                capacity = 2*capacity + 1;
                stack = (struct TreeNode **) realloc(stack, sizeof(struct TreeNode *) * capacity);
            }
            stack[++top] = node;
            node = node->left;
        }
        /* finishing the while loop, node == NULL and stack[top] == node.parent */
        node = stack[top];

        /* inOrderTraversal operation here */

        if (!node->right || node->right == prev) {

            /* postOrderTraversal here */
            node_values[(*size)++] = node->val;

            top--;
            prev = node;
            node = NULL;
        }
        else {
            node = node->right;
        }
    }
}

void postorderTraversalHelperRecursive(struct TreeNode *root, int *node_values, int *size) {
    if (!root)
        return;

    postorderTraversalHelperRecursive(root->left, node_values, size);
    postorderTraversalHelperRecursive(root->right, node_values, size);

    node_values[(*size)++] = root->val;
}

int* postorderTraversal(struct TreeNode* root, int* returnSize) {
    int size = 0;
    int *node_values = (int *) malloc(sizeof(int) * 100);
    treeTraversal(root, node_values, &size);
    *returnSize = size;
    return node_values;
}
