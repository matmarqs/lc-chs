#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, realloc, free */
#include <string.h> /* strlen */

typedef enum {true, false} bool;

typedef struct {
    char *items;
    int top;
    int size;
} Stack;

Stack *create_stack(int initial_size) {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    if (!stack) return NULL;

    stack->items = (char *) malloc(initial_size * sizeof(char));
    if (!stack-> items) {
        free(stack);
        return NULL;
    }

    stack->top = -1;
    stack->size = initial_size;
    return stack;
}

bool is_empty(Stack *stack) {
    return stack->top == -1;
}

bool is_full(Stack *stack) {
    return stack->top == stack->size - 1;
}

void resize(Stack *stack) {
    int new_size = stack->size * 2;
    char *new_items = (char *) realloc(stack->items, new_size * sizeof(char));
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

char pop(Stack *stack) {
    if (is_empty(stack)) {
        fprintf(stderr, "Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return stack->items[stack->top--];
}

char peek(Stack *stack) {
    if (is_empty(stack)) {
        fprintf(stderr, "Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return stack->items[stack->top];
}

void free_stack(Stack *stack) {
    if (stack) {
        free(stack->items);
        free(stack);
    }
}

char invert(char c) {
    switch (c) {
        case ')':
            return '(';
        case '}':
            return '{';
        case ']':
            return '[';
    }
    return 0;
}

bool isValid(char* s) {
    Stack *stack = create_stack(6);
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
            push(stack, s[i]);
        }
        else {
            if (is_empty(stack)) {
                return false;
            }
            else if (invert(s[i]) == peek(stack)) {
                pop(stack);
            }
            else {
                return false;
            }
        }
    }
    bool result = is_empty(stack);
    free_stack(stack);
    return result;
}
