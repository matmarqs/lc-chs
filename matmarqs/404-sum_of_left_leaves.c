struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/*****************************************/

/*
 * Given the root of a binary tree, return the sum of all left leaves.
 * A leaf is a node with no children. A left leaf is a leaf that is the left child of another node.
*/

int sumOfLeftLeaves(struct TreeNode* root) {
    if (!root)
        return 0;
    if (root->left && !root->left->left && !root->left->right) {
        return root->left->val + sumOfLeftLeaves(root->right);
    }
    return sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
}
