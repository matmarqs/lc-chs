#include "stack.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

void test_int_stack() {
    printf("Testing integer stack...\n");
    
    // Create stack
    Stack *stack = stack_create(2, sizeof(int));
    assert(stack != NULL);
    assert(stack_is_empty(stack));
    
    // Push and peek
    int values[] = {10, 20, 30, 40, 50};
    for (size_t i = 0; i < sizeof(values)/sizeof(values[0]); i++) {
        stack_push(stack, &values[i]);
        int top;
        stack_peek(stack, &top);
        assert(top == values[i]);
        assert(!stack_is_empty(stack));
    }
    
    // Pop and verify
    for (int i = sizeof(values)/sizeof(values[0]) - 1; i >= 0; i--) {
        int val;
        stack_pop(stack, &val);
        assert(val == values[i]);
    }
    
    assert(stack_is_empty(stack));
    stack_free(stack);
    printf("Integer stack tests passed!\n\n");
}

void test_struct_stack() {
    printf("Testing struct stack...\n");
    
    typedef struct {
        char name[32];
        int age;
        float height;
    } Person;
    
    // Create stack
    Stack *stack = stack_create(3, sizeof(Person));
    assert(stack != NULL);
    
    // Test data
    Person people[] = {
        {"Alice", 25, 1.68f},
        {"Bob", 30, 1.82f},
        {"Charlie", 35, 1.77f}
    };
    
    // Push all
    for (size_t i = 0; i < sizeof(people)/sizeof(people[0]); i++) {
        stack_push(stack, &people[i]);
    }
    
    // Verify peek
    Person top;
    stack_peek(stack, &top);
    assert(strcmp(top.name, "Charlie") == 0);
    assert(top.age == 35);
    
    // Verify pop order
    stack_pop(stack, &top);
    assert(strcmp(top.name, "Charlie") == 0);
    
    stack_pop(stack, &top);
    assert(strcmp(top.name, "Bob") == 0);
    
    stack_pop(stack, &top);
    assert(strcmp(top.name, "Alice") == 0);
    
    assert(stack_is_empty(stack));
    stack_free(stack);
    printf("Struct stack tests passed!\n\n");
}

void test_edge_cases() {
    printf("Testing edge cases...\n");
    
    // Test empty stack
    Stack *stack = stack_create(1, sizeof(int));
    assert(stack_is_empty(stack));
    
    // Test single element
    int val = 42;
    stack_push(stack, &val);
    assert(!stack_is_empty(stack));
    
    int out;
    stack_peek(stack, &out);
    assert(out == 42);
    
    stack_pop(stack, &out);
    assert(out == 42);
    assert(stack_is_empty(stack));
    
    // Test resizing
    for (int i = 0; i < 1000; i++) {
        stack_push(stack, &i);
    }
    
    for (int i = 999; i >= 0; i--) {
        stack_pop(stack, &out);
        assert(out == i);
    }
    
    stack_free(stack);
    printf("Edge cases tests passed!\n\n");
}

int main() {
    test_int_stack();
    test_struct_stack();
    test_edge_cases();
    
    printf("All tests passed successfully!\n");
    return 0;
}
