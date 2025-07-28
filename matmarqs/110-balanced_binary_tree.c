/* The older solution was O(n^2) */
/* because height() is O(n) */
/* and it was called O(n) times */

#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/***************************************************/

/* This new solution is O(n), as it calculates height and checks balance simultaneously  */

#include <stdlib.h> // for abs()

// Helper function that returns a pair: (height, is_balanced)
// We use a pointer to store the height and return the balance status
bool checkBalance(struct TreeNode* node, int* height) {
    if (!node) {
        *height = 0;
        return true;
    }

    int left_height, right_height;
    bool left_balanced = checkBalance(node->left, &left_height);
    bool right_balanced = checkBalance(node->right, &right_height);

    *height = (left_height > right_height ? left_height : right_height) + 1;

    return left_balanced && right_balanced && 
           abs(left_height - right_height) <= 1;
}

bool isBalanced(struct TreeNode* root) {
    int height;
    return checkBalance(root, &height);
}
