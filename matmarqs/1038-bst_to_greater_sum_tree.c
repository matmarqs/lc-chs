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

/* InOrderTraversal, but reversed, first the right subtrees */
void dfs(TreeNode *root, int *sum) {
    if (!root)
        return;

    dfs(root->right, sum);

    *sum += root->val;
    root->val = *sum;

    dfs(root->left, sum);
}

struct TreeNode* bstToGst(struct TreeNode* root) {
    int sum = 0;

    dfs(root, &sum);

    return root;
}
