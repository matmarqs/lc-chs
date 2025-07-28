#include <stdbool.h>

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


#include <string.h>

// Hash function for strings (djb2 algorithm)
size_t str_hash(char *key) {
    size_t hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

// Equality function for strings
bool str_equals(char *a, char *b) {
    if (a == b) return true;
    if (!a || !b) return false;
    return strcmp(a, b) == 0;
}
