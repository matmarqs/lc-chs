#include <stdbool.h>

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

bool isSameTree(struct TreeNode* p, struct TreeNode* q) {
    if (!p && q) {
        return false;
    }
    else if (p && !q) {
        return false;
    }
    else if (!p && !q) {
        return true;
    }
    else if (p->val != q->val) {
        return false;
    }
    /* from here, we know that p->val == q->val */
    /* we have to check their children */

    bool same = isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    
    return same;
}
