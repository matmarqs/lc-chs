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

typedef struct TreeNode TreeNode;

/* PreOrderTraversal */
void dfs(TreeNode *node, int max, int *count) {
    if (!node) {
        return;
    }

    if (max <= node->val)
        (*count)++;

    if (node->val > max)
        max = node->val;

    dfs(node->left, max, count);
    dfs(node->right, max, count);
}

int goodNodes(TreeNode* root){
    int count = 0;
    int max = -10001;   /* -10^4 <= val <= 10^4 */

    dfs(root, max, &count);

    return count;
}
