typedef enum {true, false} bool;

/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *items;
    int top;
    int size;
} Stack;

Stack *create_stack(int initial_size) {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    if (!stack) return NULL;

    stack->items = (int *) malloc(initial_size * sizeof(int));
    if (!stack->items) {
        free(stack);
        return NULL;
    }
    stack->top = -1;
    stack->size = initial_size;
    return stack;
}

bool is_full(Stack *stack) {
    return stack->top == stack->size - 1;
}

void resize(Stack *stack) {
    int new_size = stack->size * 2;
    int *new_items = (int *) realloc(stack->items, new_size * sizeof(int));
    if (new_items) {
        stack->items = new_items;
        stack->size = new_size;
    }
    else {
        fprintf(stderr, "Failed to resize stack\n");
        exit(EXIT_FAILURE);
    }
}

void push(Stack *stack, int item) {
    if (is_full(stack)) {
        resize(stack);
    }
    stack->items[++stack->top] = item;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findEvenNumbers(int* digits, int digitsSize, int* returnSize) {
                /* 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 */
    int count[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i < digitsSize; i++) {
        count[digits[i]]++;
    }

    Stack *stack = create_stack(20);

    for (int d2 = 1; d2 < 10; d2++) {
        if (count[d2]) {
            count[d2]--;
            for (int d1 = 0; d1 < 10; d1++) {
                if (count[d1]) {
                    count[d1]--;
                    for (int d0 = 0; d0 < 10; d0 += 2) {
                        if (count[d0]) {
                            push(stack, 100*d2 + 10*d1 + d0);
                        }
                    }
                    count[d1]++;
                }
            }
            count[d2]++;
        }
    }

    int *numbers = stack->items;
    *returnSize = stack->top + 1;
    free(stack);
    return numbers;
}
