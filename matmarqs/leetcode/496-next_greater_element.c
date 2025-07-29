#include <stdio.h>
#include <stdbool.h>

/***************************************************************/

#include <stdlib.h>
#include <string.h>

#define NOT_FOUND -1

typedef struct Node {
    int key;
    int val;
    struct Node *next;
} Node;

Node *create_node (int key, int value) {
    Node *n = (Node *) malloc(sizeof(Node));
    n->key = key;
    n->val = value;
    n->next = NULL;
    return n;
}

typedef struct {
    Node *head;
} Chain;

void append_to_chain(Chain *chain, int key, int value) {
    Node *new = create_node(key, value);
    if (!chain->head) {
        chain->head = new;
    }
    else {
        new->next = chain->head;
        chain->head = new;
    }
}

void free_chain(Chain *chain) {
    while (chain->head) {
        Node *next = chain->head->next;
        free(chain->head);
        chain->head = next;
    }
}

typedef struct {
    Chain *chains;
    int size;
    int cardinality;
} HashMap;

/* simple hash function with prime number */
    int h(long long key, int m) {
    return (int) ((key * 31LL) % m + m) % m;
    // a % b is not a modulo operator, but a remainder operator
    // a % b can return negative values
}

HashMap *create_map(int cardinality) {
    HashMap *set = (HashMap *) malloc(sizeof(HashMap));
    set->cardinality = cardinality;
    set->size = 0;
    set->chains = (Chain *) malloc(sizeof(Chain) * cardinality);
    for (int i = 0; i < cardinality; i++) {
        set->chains[i].head = NULL;
    }
    return set;
}

void free_map(HashMap *map) {
    for (int i = 0; i < map->cardinality; i++) {
        free_chain(&map->chains[i]);
    }
    free(map->chains);
    free(map);
}

bool map_haskey(HashMap *map, int key) {
    Chain *chain = &map->chains[h(key, map->cardinality)];
    Node *current = chain->head;
    while (current) {
        if (current->key == key) {
            return true;
        }
        current = current->next;
    }
    return false;
}

int map_get(HashMap *map, int key) {
    Chain *chain = &map->chains[h(key, map->cardinality)];
    Node *current = chain->head;
    while (current) {
        if (current->key == key) {
            return current->val;
        }
        current = current->next;
    }
    return NOT_FOUND;
}

void map_set(HashMap *map, int key, int value) {
    if (!map_haskey(map, key)) {
        append_to_chain(&map->chains[h(key, map->cardinality)], key, value);
        map->size++;
    }
}

/* more complex, because we have to find the previous node, since we have a singly linked list */
void map_remove(HashMap *set, int key) {
    Chain *chain = &set->chains[h(key, set->cardinality)];

    Node *current = chain->head;
    if (chain->head && chain->head->key == key) {
        if (!chain->head->next) {   // there is only one node in the Chain
            free(chain->head);
            chain->head = NULL;
        }
        else {  // there is more than one node in Chain, and key is on the head
            chain->head = chain->head->next;
            free(current);
        }
        set->size--;
        return;
    }

    while (current->next) {
        if (current->next->key == key) {
            Node *next_node = current->next;
            current->next = current->next->next;
            free(next_node);
            set->size--;
            return;
        }
        current = current->next;
    }

}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* nextGreaterElement(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    HashMap *map2 = create_map(3 * nums2Size / 2);

    int *stack = (int *) malloc(sizeof(int) * nums2Size);
    int top = -1;

    // Process from right to left
    for (int i = nums2Size-1; i >= 0; i--) {
        while (top >= 0 && stack[top] <= nums2[i]) {
            top--; // Pop elements smaller than current
        }

        int nextGreater = (top >= 0) ? stack[top]: -1;

        map_set(map2, nums2[i], nextGreater);

        stack[++top] = nums2[i]; // Push current element
    }
    free(stack);

    *returnSize = nums1Size;
    int *result = (int *) malloc(sizeof(int) * nums1Size);

    for (int i = 0; i < nums1Size; i++) {
        result[i] = map_get(map2, nums1[i]);
    }

    free_map(map2);

    return result;
}

/************************************************************************************************/

int main() {
    int nums2[4] = { 1, 2, 3, 4 };
    int ng_array[4];
    int size = 4;

    //inner_next_greater_element(nums2, ng_array, size, 0);


    for (int i = 0; i < 4; i++) {
        printf("%d\n", ng_array[i]);
    }
}
