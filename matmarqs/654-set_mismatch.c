#include <stdbool.h>

/***************************************/

#include <stdlib.h>

#define DEFINE_HASHSET(name, prefix, key_type, hash_func, key_equals) \
    \
    typedef enum { FREE, OCCUPIED, DELETED } name##_SlotState; \
    \
    typedef struct { \
        key_type key; \
        name##_SlotState state; \
    } name##_Slot; \
    \
    typedef struct { \
        name##_Slot *slots; \
        int size; \
        int capacity; \
        int threshold; \
    } name; \
    \
    static int prefix##_next_power_of_two(int n) { \
        if (n <= 1) return 1; \
        int power = 1; \
        while (power < n) power *= 2; \
        return power; \
    } \
    \
    \
    /* Forward declarations to resolve dependency */ \
    void prefix##_add(name *set, key_type key); \
    \
    static void prefix##_inner_rehash(name *set) { \
        int new_capacity = set->capacity * 2; \
        name##_Slot *new_slots = calloc(new_capacity, sizeof(name##_Slot)); \
        int old_capacity = set->capacity; \
        name##_Slot *old_slots = set->slots; \
        \
        set->slots = new_slots; \
        set->capacity = new_capacity; \
        set->threshold = (int)(new_capacity * 0.7); \
        set->size = 0; \
        \
        for (int i = 0; i < old_capacity; i++) { \
            if (old_slots[i].state == OCCUPIED) { \
                prefix##_add(set, old_slots[i].key); \
            } \
        } \
        free(old_slots); \
    } \
    \
    name *prefix##_create(int initial_capacity) { \
        name *set = malloc(sizeof(name)); \
        set->capacity = prefix##_next_power_of_two(initial_capacity); \
        if (set->capacity < 16) set->capacity = 16; \
        set->slots = calloc(set->capacity, sizeof(name##_Slot)); \
        set->size = 0; \
        set->threshold = (int)(set->capacity * 0.7); \
        return set; \
    } \
    \
    void prefix##_free(name *set) { \
        free(set->slots); \
        free(set); \
    } \
    \
    bool prefix##_contains(name *set, key_type key) { \
        if (set->size == 0) return false; \
        size_t hash_val = hash_func(key); \
        int idx = (int)(hash_val & (set->capacity - 1)); \
        \
        for (int i = 0; i < set->capacity; i++) { \
            int j = (idx + i) & (set->capacity - 1); \
            if (set->slots[j].state == FREE) return false; \
            if (set->slots[j].state == OCCUPIED && \
                key_equals(set->slots[j].key, key)) { \
                return true; \
            } \
        } \
        return false; \
    } \
    \
    void prefix##_add(name *set, key_type key) { \
        if (set->size >= set->threshold) { \
            prefix##_inner_rehash(set); \
        } \
        \
        size_t hash_val = hash_func(key); \
        int idx = (int)(hash_val & (set->capacity - 1)); \
        int first_deleted = -1; \
        \
        for (int i = 0; i < set->capacity; i++) { \
            int j = (idx + i) & (set->capacity - 1); \
            \
            if (set->slots[j].state == OCCUPIED) { \
                if (key_equals(set->slots[j].key, key)) return; \
            } else { \
                if (set->slots[j].state == FREE) { \
                    if (first_deleted == -1) { \
                        set->slots[j].key = key; \
                        set->slots[j].state = OCCUPIED; \
                        set->size++; \
                        return; \
                    } else { \
                        set->slots[first_deleted].key = key; \
                        set->slots[first_deleted].state = OCCUPIED; \
                        set->size++; \
                        return; \
                    } \
                } else if (first_deleted == -1) { \
                    first_deleted = j; \
                } \
            } \
        } \
        \
        if (first_deleted != -1) { \
            set->slots[first_deleted].key = key; \
            set->slots[first_deleted].state = OCCUPIED; \
            set->size++; \
        } \
    } \
    \
    void prefix##_remove(name *set, key_type key) { \
        size_t hash_val = hash_func(key); \
        int idx = (int)(hash_val & (set->capacity - 1)); \
        \
        for (int i = 0; i < set->capacity; i++) { \
            int j = (idx + i) & (set->capacity - 1); \
            if (set->slots[j].state == FREE) return; \
            if (set->slots[j].state == OCCUPIED && \
                key_equals(set->slots[j].key, key)) { \
                set->slots[j].state = DELETED; \
                set->size--; \
                return; \
            } \
        } \
    }

// Hash function for integers or chars
size_t int_hash(int key) {
    return (size_t)(key * 31LL);
}

// Equality function for integers or chars
bool int_equals(int a, int b) {
    return a == b;
}

DEFINE_HASHSET(HashSet, hashset, int, int_hash, int_equals);

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findErrorNums(int* nums, int numsSize, int* returnSize) {
    HashSet *set = hashset_create(numsSize);
    int *returnNumbers = (int *) malloc(sizeof(int) * 2);
    *returnSize = 2;
    for (int i = 0; i < numsSize; i++) {
        if (hashset_contains(set, nums[i])) {
            returnNumbers[0] = nums[i];
        }
        hashset_add(set, nums[i]);
    }
    for (int n = 1; n < numsSize + 1; n++) {
        if (!hashset_contains(set, n)) {
            returnNumbers[1] = n;
        }
    }

    hashset_free(set);
    return returnNumbers;
}
