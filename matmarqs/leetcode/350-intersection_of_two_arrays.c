#include <stdbool.h>

/************************************/

#include <stdlib.h>

#define DEFINE_HASHMAP(name, prefix, key_type, val_type, hash_func, key_equals, NOT_FOUND) \
    \
    typedef enum { FREE, OCCUPIED, DELETED } name##_SlotState; \
    \
    typedef struct { \
        key_type key; \
        val_type val; \
        name##_SlotState state; \
    } name##_Slot; \
    \
    typedef struct { \
        name##_Slot *slots; \
        int size; \
        int capacity; \
        int threshold; \
        val_type not_found; \
    } name; \
    \
    static int prefix##_next_power_of_two(int n) { \
        if (n <= 1) return 1; \
        int power = 1; \
        while (power < n) power *= 2; \
        return power; \
    } \
    \
    static void prefix##_set(name *map, key_type key, val_type val); \
    \
    static void prefix##_inner_rehash(name *map) { \
        int new_capacity = map->capacity * 2; \
        name##_Slot *new_slots = calloc(new_capacity, sizeof(name##_Slot)); \
        if (!new_slots) return; \
        int old_capacity = map->capacity; \
        name##_Slot *old_slots = map->slots; \
        map->slots = new_slots; \
        map->capacity = new_capacity; \
        map->threshold = (int)(new_capacity * 0.7); \
        map->size = 0; \
        for (int i = 0; i < old_capacity; i++) { \
            if (old_slots[i].state == OCCUPIED) { \
                prefix##_set(map, old_slots[i].key, old_slots[i].val); \
            } \
        } \
        free(old_slots); \
    } \
    \
    static name *prefix##_create(int initial_capacity) { \
        name *map = malloc(sizeof(name)); \
        if (!map) return NULL; \
        map->capacity = prefix##_next_power_of_two(initial_capacity); \
        if (map->capacity < 16) map->capacity = 16; \
        map->slots = calloc(map->capacity, sizeof(name##_Slot)); \
        if (!map->slots) { \
            free(map); \
            return NULL; \
        } \
        map->size = 0; \
        map->threshold = (int)(map->capacity * 0.7); \
        map->not_found = NOT_FOUND; \
        return map; \
    } \
    \
    static void prefix##_free(name *map) { \
        free(map->slots); \
        free(map); \
    } \
    \
    static int prefix##_haskey(name *map, key_type key) { \
        if (map->size == 0) return 0; \
        size_t hash_val = hash_func(key); \
        int idx = (int)(hash_val & (map->capacity - 1)); \
        for (int i = 0; i < map->capacity; i++) { \
            int j = (idx + i) & (map->capacity - 1); \
            if (map->slots[j].state == FREE) return 0; \
            if (map->slots[j].state == OCCUPIED && \
                key_equals(map->slots[j].key, key)) return 1; \
        } \
        return 0; \
    } \
    \
    static val_type prefix##_get(name *map, key_type key) { \
        if (map->size == 0) return map->not_found; \
        size_t hash_val = hash_func(key); \
        int idx = (int)(hash_val & (map->capacity - 1)); \
        for (int i = 0; i < map->capacity; i++) { \
            int j = (idx + i) & (map->capacity - 1); \
            if (map->slots[j].state == FREE) break; \
            if (map->slots[j].state == OCCUPIED && \
                key_equals(map->slots[j].key, key)) \
                return map->slots[j].val; \
        } \
        return map->not_found; \
    } \
    \
    static void prefix##_set(name *map, key_type key, val_type val) { \
        if (map->size >= map->threshold) { \
            prefix##_inner_rehash(map); \
        } \
        size_t hash_val = hash_func(key); \
        int idx = (int)(hash_val & (map->capacity - 1)); \
        int first_deleted = -1; \
        for (int i = 0; i < map->capacity; i++) { \
            int j = (idx + i) & (map->capacity - 1); \
            if (map->slots[j].state == OCCUPIED) { \
                if (key_equals(map->slots[j].key, key)) { \
                    map->slots[j].val = val; \
                    return; \
                } \
            } else if (map->slots[j].state == FREE) { \
                if (first_deleted == -1) { \
                    map->slots[j].key = key; \
                    map->slots[j].val = val; \
                    map->slots[j].state = OCCUPIED; \
                    map->size++; \
                } else { \
                    map->slots[first_deleted].key = key; \
                    map->slots[first_deleted].val = val; \
                    map->slots[first_deleted].state = OCCUPIED; \
                    map->size++; \
                } \
                return; \
            } else if (first_deleted == -1) { \
                first_deleted = j; \
            } \
        } \
        if (first_deleted != -1) { \
            map->slots[first_deleted].key = key; \
            map->slots[first_deleted].val = val; \
            map->slots[first_deleted].state = OCCUPIED; \
            map->size++; \
        } \
    } \
    \
    static void prefix##_remove(name *map, key_type key) { \
        size_t hash_val = hash_func(key); \
        int idx = (int)(hash_val & (map->capacity - 1)); \
        for (int i = 0; i < map->capacity; i++) { \
            int j = (idx + i) & (map->capacity - 1); \
            if (map->slots[j].state == FREE) return; \
            if (map->slots[j].state == OCCUPIED && \
                key_equals(map->slots[j].key, key)) { \
                map->slots[j].state = DELETED; \
                map->size--; \
                return; \
            } \
        } \
    }

// Hash function for integers
size_t int_hash(int key) {
    return (size_t)(key * 31LL);
}

// Equality function for integers
bool int_equals(int a, int b) {
    return a == b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

DEFINE_HASHMAP(HashMap, hashmap, int, int, int_hash, int_equals, 1001);

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    int min_size = min(nums1Size, nums2Size);
    int max_size = max(nums1Size, nums2Size);
    int *min_array = nums1Size == min_size ? nums1 : nums2;
    int *max_array = nums1Size != min_size ? nums1 : nums2;

    HashMap *map = hashmap_create(3 * min_size / 2);

    for (int i = 0; i < min_size; i++) {
        if (!hashmap_haskey(map, min_array[i])) {
            hashmap_set(map, min_array[i], 1);
        }
        else {
            int current = hashmap_get(map, min_array[i]);
            hashmap_set(map, min_array[i], current + 1);
        }
    }

    int *return_array = (int *) malloc(sizeof(int) * min_size);
    int size = 0;

    for (int i = 0; i < max_size; i++) {
        if (hashmap_haskey(map, max_array[i])) {
            int current = hashmap_get(map, max_array[i]);
            if (current > 0) {
                return_array[size++] = max_array[i];
                hashmap_set(map, max_array[i], current-1);
            }
        }
    }

    hashmap_free(map);

    *returnSize = size;
    return return_array;
}
