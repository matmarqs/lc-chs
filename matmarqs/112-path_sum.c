#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/*************************************************************/

bool hasPathSum(struct TreeNode* root, int targetSum) {
    if (!root)
        return false;

    if (!root->left && !root->right) {
        return root->val == targetSum;
    }

    bool result = false;

    if (root->left)
        result = hasPathSum(root->left, targetSum - root->val);

    if (!result && root->right)
        result = hasPathSum(root->right, targetSum - root->val);

    return result;
}
