struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/*************************************/

#include <stdlib.h>

typedef struct TreeNode TreeNode;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* pruneTree(struct TreeNode* root) {
    if (!root) {
        return NULL;
    }

    if (root->left) {
        pruneTree(root->left);
        if (!root->left->left && !root->left->right && root->left->val != 1) {
            root->left = NULL;
        }
    }
    if (root->right) {
        pruneTree(root->right);
        if (!root->right->left && !root->right->right && root->right->val != 1) {
            root->right = NULL;
        }
    }

    if (!root->left && !root->right && root->val != 1) {
        return NULL;
    }
    else {
        return root;
    }
}
