struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


/***************************************************************/

int max(int a, int b) {
    return (a > b) ? a : b;
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int maxDepth(struct TreeNode* root) {
    if (!root)
        return 0;
    return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}
