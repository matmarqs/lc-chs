struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

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

#include <stdlib.h>

typedef struct TreeNode Tree;

void inorderSolve(Tree *root, int **arr, int *sz, int *cap) {
    if (!root)
        return;

    inorderSolve(root->left, arr, sz, cap);

    if (*sz == *cap) {  // array is full, alloc more space
        *cap *= 2;
        *arr = (int *) realloc(*arr, sizeof(int) * *cap);
    }

    // appending in order
    *sz += 1;
    (*arr)[*sz-1] = root->val;

    inorderSolve(root->right, arr, sz, cap);
}

int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    int capacity = 4;
    int *array = (int *) malloc(sizeof(int) * capacity);
    int size = 0;

    inorderSolve(root, &array, &size, &capacity);

    *returnSize = size;
    return array;
}
