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

#include <stdlib.h>

typedef struct TreeNode TreeNode;

TreeNode* find(TreeNode* root, int key, TreeNode **parent) {
    if (!root) {
        return NULL;
    }
    if (key == root->val) {
        return root;
    }
    else if (key < root->val) {
        *parent = root;
        return find(root->left, key, parent);
    }
    else {
        *parent = root;
        return find(root->right, key, parent);
    }
}

TreeNode* deleteNode(TreeNode* root, int key) {
    TreeNode *parent = NULL;
    TreeNode *node = find(root, key, &parent);
    if (!node) {
        return root; // Key not found, return original tree
    }

    // Case 1: Node is a leaf (no children)
    if (node->left == NULL && node->right == NULL) {
        if (parent == NULL) {
            root = NULL; // Node is root, tree becomes empty
        } else if (parent->left == node) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        free(node);
    }
    // Case 2: Node has one child
    else if (node->left == NULL || node->right == NULL) {
        TreeNode *child = node->left ? node->left : node->right;
        if (parent == NULL) {
            root = child; // Node is root, new root is child
        } else if (parent->left == node) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        free(node);
    }
    // Case 3: Node has two children
    else {
        // Find inorder successor (leftmost in right subtree)
        TreeNode *succ_parent = node;
        TreeNode *succ = node->right;
        while (succ->left) {
            succ_parent = succ;
            succ = succ->left;
        }

        // Copy successor value to node
        node->val = succ->val;

        // Delete successor node (has at most one right child)
        if (succ_parent->left == succ) {
            succ_parent->left = succ->right;
        } else {
            succ_parent->right = succ->right;
        }
        free(succ);
    }

    return root;
}
