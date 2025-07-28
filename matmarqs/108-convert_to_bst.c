struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**********************************************************/

#include <stdlib.h>

typedef struct TreeNode TreeNode;

TreeNode *create_node(int val) {
    TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
    t->val = val;
    t->left = t->right = NULL;
    return t;
}

TreeNode *solve(int *nums, int left, int right) {
    if (left > right) {
        return NULL;
    }

    int mid = (right + left)/2;
    TreeNode *t = create_node(nums[mid]);

    t->left = solve(nums, left, mid-1);
    t->right = solve(nums, mid+1, right);

    return t;
}

struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
    return solve(nums, 0, numsSize-1);
}
