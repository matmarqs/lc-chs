struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/*************************************************************/

#include <stdlib.h>

struct TreeNode* searchBST(struct TreeNode* root, int val) {
    if (!root) return NULL;

    if (root->val == val) return root;

    if (val < root->val) {
        return searchBST(root->left, val);
    }
    else {
        return searchBST(root->right, val);
    }
}
