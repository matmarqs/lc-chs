#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stack {
    void *items;       // Contiguous memory block
    int top;           // Index of top element
    int capacity;      // Current capacity
    size_t item_size;   // Size of each item
};

Stack* stack_create(int initial_capacity, size_t item_size) {
    Stack *stack = malloc(sizeof(Stack));
    if (!stack) return NULL;
    
    stack->items = malloc(initial_capacity * item_size);
    if (!stack->items) {
        free(stack);
        return NULL;
    }
    
    stack->top = -1;
    stack->capacity = initial_capacity;
    stack->item_size = item_size;
    return stack;
}

bool stack_is_empty(const Stack *stack) {
    return stack->top == -1;
}

bool stack_is_full(const Stack *stack) {
    return stack->top == stack->capacity - 1;
}

static void stack_resize(Stack *stack) {
    int newCapacity = stack->capacity * 2;
    void *newItems = realloc(stack->items, newCapacity * stack->item_size);
    if (newItems) {
        stack->items = newItems;
        stack->capacity = newCapacity;
    } else {
        fprintf(stderr, "Failed to resize stack\n");
        exit(EXIT_FAILURE);
    }
}

void stack_push(Stack *stack, const void *item) {
    if (stack_is_full(stack)) {
        stack_resize(stack);
    }
    void *target = (char*)stack->items + (++stack->top * stack->item_size);
    memcpy(target, item, stack->item_size);
}

void stack_pop(Stack *stack, void *output) {
    if (stack_is_empty(stack)) {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    void *source = (char*)stack->items + (stack->top-- * stack->item_size);
    memcpy(output, source, stack->item_size);
}

void stack_peek(const Stack *stack, void *output) {
    if (stack_is_empty(stack)) {
        fprintf(stderr, "Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    void *source = (char*)stack->items + (stack->top * stack->item_size);
    memcpy(output, source, stack->item_size);
}

void stack_free(Stack *stack) {
    if (stack) {
        free(stack->items);
        free(stack);
    }
}
