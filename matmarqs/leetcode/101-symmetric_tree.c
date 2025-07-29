#include <stdbool.h>

 struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
 };

/**********************************************/

bool isEqual(struct TreeNode* a, struct TreeNode* b) {
    if (a && !b || !a && b)
        return false;
    else if (!a && !b)
        return true;

    if (a->right && !b->left)
        return false;
    else if (!a->right && b->left)
        return false;

    if (a->left && !b->right)
        return false;
    else if (!a->left && b->right)
        return false;

    if (a->val == b->val) {
        return isEqual(a->left, b->right) && isEqual(a->right, b->left);
    }
    else {
        return false;
    }
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool isSymmetric(struct TreeNode* root) {
    if (root) {
        return isEqual(root->left, root->right);
    }
    else {
        return true;
    }
}

