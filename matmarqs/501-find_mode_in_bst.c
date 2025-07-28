struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/*******************************************************/

#include <stdlib.h>

typedef struct Stack {
    int *array;
    int top;
    int size;
} Stack;

void inOrderTraversal_Pre(struct TreeNode *root, int *val, int *freq, int *max_freq) {
    if (!root)
        return;

    inOrderTraversal_Pre(root->left, val, freq, max_freq);

    if (root->val == *val) {
        (*freq)++;
    }
    else {
        *val = root->val;
        *freq = 1;
    }
    if (*freq > *max_freq) {
        *max_freq = *freq;
    }

    inOrderTraversal_Pre(root->right, val, freq,  max_freq);
}

void inOrderTraversal_Post(struct TreeNode *root, int *val, int *freq, const int max_freq, Stack *stack) {
    if (!root)
        return;

    inOrderTraversal_Post(root->left, val, freq, max_freq, stack);

    if (root->val == *val) {
        (*freq)++;
    }
    else {
        *val = root->val;
        *freq = 1;
    }
    if (*freq == max_freq) {
        stack->top++;
        if (stack->top >= stack->size) {
            stack->size *= 2;
            stack->array = realloc(stack->array, sizeof(int) * (stack->size));
        }
        stack->array[stack->top] = root->val;
    }

    inOrderTraversal_Post(root->right, val, freq, max_freq, stack);
}

int* findMode(struct TreeNode* root, int* returnSize) {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->size = 2;
    stack->array = (int *) malloc(sizeof(int) * stack->size);
    stack->top = -1;

    int current_val = -1000000;
    int current_freq = 0;
    int max_freq = 0;
    inOrderTraversal_Pre(root, &current_val, &current_freq, &max_freq);

    current_val = -1000000;
    current_freq = 0;
    inOrderTraversal_Post(root, &current_val, &current_freq, max_freq, stack);

    *returnSize = stack->top + 1;
    return stack->array;
}
