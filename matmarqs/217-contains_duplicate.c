#include <stdbool.h>

/*********************************************/

#include <stdlib.h>

typedef long long ll;

typedef struct {
    ll *keys;
    bool *occupied;
    int size;
} HashSet;

HashSet *set_create(int size) {
    HashSet *set = (HashSet *) malloc(sizeof(HashSet));
    set->keys = (ll *) calloc(size, sizeof(ll));
    set->occupied = (bool *) calloc(size, sizeof(bool));
    set->size = size;
    return set;
}

void set_free(HashSet *set) {
    free(set->keys);
    free(set->occupied);
    free(set);
}

/* simple hash function with prime number */
int hash(ll key, int size) {
    return (int) ((key * 31LL) % size + size) % size;
    // a % b is not a modulo operator, but a remainder operator
    // a % b can return negative values
}

bool contains(ll key, HashSet *set) {
    int index = hash(key, set->size);
    int original_index = index;

    while (set->occupied[index]) {
        if (set->keys[index] == key) {
            return true;
        }
        index = (index + 1) % set->size;
        if (index == original_index) // this prevents an infinite loop
            return false;
        // in the worst case scenario, we take O(N) to check
        // but, on average we take O(1)
    }
    return false;
}

void add(ll key, HashSet *set) {
    int index = hash(key, set->size);

    while (set->occupied[index]) {
        if (set->keys[index] == key) {
            return; // it's already in the set
        }
        index = (index + 1) % set->size; // possible infinite loop, if the set is full
    }

    set->keys[index] = key;
    set->occupied[index] = true;
}

bool containsDuplicate(int* nums, int numsSize) {

    HashSet *set = set_create(2 * numsSize); // 2 * numsSize in order to minimize collisions

    for (int i = 0; i < numsSize; i++) {
        if (contains(nums[i], set)) {
            set_free(set);
            return true;
        }
        add(nums[i], set);
    }

    set_free(set);
    return false;
}
