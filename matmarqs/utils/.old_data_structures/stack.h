#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stddef.h>

// Opaque pointer type - hides implementation details
typedef struct Stack Stack;

// Creates a new stack
Stack* stack_create(int initialCapacity, size_t itemSize);

// Checks if stack is empty
bool stack_is_empty(const Stack *stack);

// Checks if stack is full
bool stack_is_full(const Stack *stack);

// Pushes an item onto the stack
void stack_push(Stack *stack, const void *item);

// Pops an item from the stack
void stack_pop(Stack *stack, void *output);

// Peeks at the top item without removing it
void stack_peek(const Stack *stack, void *output);

// Frees stack memory
void stack_free(Stack *stack);

#endif // STACK_H
