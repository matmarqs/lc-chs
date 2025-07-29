struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/*******************************************************************************/

/* inOrderTraversal is the correct solution because it traverses the tree in sorted order */
/* we just have to keep track of the previous node, and subtract to the current one */

#include <stdlib.h>

#define MYMAX (100001)
#define min(a,b) (((a) < (b)) ? (a) : (b))

void inOrderTraversal(struct TreeNode *root, struct TreeNode **prev, int *min_diff) {
    if (!root) return;

    inOrderTraversal(root->left, prev, min_diff);

    if (*prev) {
        *min_diff = min(*min_diff, root->val - (*prev)->val);
    }
    *prev = root;

    inOrderTraversal(root->right, prev, min_diff);
}

int getMinimumDifference(struct TreeNode* root) {
    int min_diff = MYMAX;
    struct TreeNode *prev = NULL;
    inOrderTraversal(root, &prev, &min_diff);
    return min_diff;
}
