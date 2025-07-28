#include <stdbool.h>

/******************************************************************************************************/

#include <stdlib.h>
#include <string.h>

// Macro to define a generic name
#define DEFINE_HASHMAP(name, prefix, key_type, val_type, hash_func, key_equals, NOT_FOUND) \
    \
    typedef struct name##_Node { \
        key_type key; \
        val_type val; \
        struct name##_Node *next; \
    } name##_Node; \
    \
    typedef struct { \
        name##_Node *head; \
    } name##_Chain; \
    \
    static name##_Node *prefix##_inner_create_node(key_type key, val_type val) { \
        name##_Node *n = (name##_Node *)malloc(sizeof(name##_Node)); \
        n->key = key; \
        n->val = val; \
        n->next = NULL; \
        return n; \
    } \
    \
    static void prefix##_inner_append_to_chain(name##_Chain *chain, key_type key, val_type val) { \
        name##_Node *new_node = prefix##_inner_create_node(key, val); \
        new_node->next = chain->head; \
        chain->head = new_node; \
    } \
    \
    static void prefix##_inner_free_chain(name##_Chain *chain) { \
        while (chain->head) { \
            name##_Node *next = chain->head->next; \
            free(chain->head); \
            chain->head = next; \
        } \
    } \
    \
    typedef struct { \
        name##_Chain *chains; \
        int size; \
        int cardinality; \
        int not_found; \
    } name; \
    \
    static void prefix##_inner_rehash(name *map, int new_cardinality) { \
        name##_Chain *new_chains = (name##_Chain *)malloc(sizeof(name##_Chain) * new_cardinality); \
        if (!new_chains) return; /* Malloc failure; leave map unchanged */ \
        for (int i = 0; i < new_cardinality; i++) { \
            new_chains[i].head = NULL; \
        } \
        int old_cardinality = map->cardinality; \
        name##_Chain *old_chains = map->chains; \
        for (int i = 0; i < old_cardinality; i++) { \
            name##_Node *node = old_chains[i].head; \
            while (node) { \
                name##_Node *next_node = node->next; \
                size_t hash_val = hash_func(node->key); \
                int new_idx = (int)(hash_val % (size_t)new_cardinality); \
                node->next = new_chains[new_idx].head; \
                new_chains[new_idx].head = node; \
                node = next_node; \
            } \
        } \
        map->chains = new_chains; \
        map->cardinality = new_cardinality; \
        free(old_chains); \
    } \
    \
    name *prefix##_create(int cardinality) { \
        name *map = (name *)malloc(sizeof(name)); \
        map->size = 0; \
        map->cardinality = cardinality; \
        map->not_found = NOT_FOUND; \
        map->chains = (name##_Chain *)malloc(sizeof(name##_Chain) * cardinality); \
        for (int i = 0; i < cardinality; i++) { \
            map->chains[i].head = NULL; \
        } \
        return map; \
    } \
    \
    void prefix##_free(name *map) { \
        for (int i = 0; i < map->cardinality; i++) { \
            prefix##_inner_free_chain(&map->chains[i]); \
        } \
        free(map->chains); \
        free(map); \
    } \
    \
    int prefix##_haskey(name *map, key_type key) { \
        size_t hash_val = hash_func(key); \
        int idx = (int)(hash_val % (size_t)map->cardinality); \
        name##_Chain *chain = &map->chains[idx]; \
        name##_Node *current = chain->head; \
        while (current) { \
            if (key_equals(current->key, key)) { \
                return 1; \
            } \
            current = current->next; \
        } \
        return 0; \
    } \
    \
    val_type prefix##_get(name *map, key_type key) { \
        size_t hash_val = hash_func(key); \
        int idx = (int)(hash_val % (size_t)map->cardinality); \
        name##_Chain *chain = &map->chains[idx]; \
        name##_Node *current = chain->head; \
        while (current) { \
            if (key_equals(current->key, key)) { \
                return current->val; \
            } \
            current = current->next; \
        } \
        return map->not_found; \
    } \
    \
    void prefix##_set(name *map, key_type key, val_type val) { \
        size_t hash_val = hash_func(key); \
        int idx = (int)(hash_val % (size_t)map->cardinality); \
        name##_Chain *chain = &map->chains[idx]; \
        name##_Node *current = chain->head; \
        while (current) { \
            if (key_equals(current->key, key)) { \
                current->val = val; \
                return; \
            } \
            current = current->next; \
        } \
        prefix##_inner_append_to_chain(chain, key, val); \
        map->size++; \
        if ((long long)map->size * 4 > (long long)map->cardinality * 3) { \
            prefix##_inner_rehash(map, map->cardinality * 2); \
        } \
    } \
    \
    void prefix##_remove(name *map, key_type key) { \
        size_t hash_val = hash_func(key); \
        int idx = (int)(hash_val % (size_t)map->cardinality); \
        name##_Chain *chain = &map->chains[idx]; \
        name##_Node *current = chain->head; \
        if (!current) return; \
        if (key_equals(current->key, key)) { \
            chain->head = current->next; \
            free(current); \
            map->size--; \
            return; \
        } \
        while (current->next) { \
            if (key_equals(current->next->key, key)) { \
                name##_Node *to_remove = current->next; \
                current->next = to_remove->next; \
                free(to_remove); \
                map->size--; \
                return; \
            } \
            current = current->next; \
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

DEFINE_HASHMAP(HashMap, hashmap, int, int, int_hash, int_equals, 1000000001);

bool containsNearbyDuplicate(int* nums, int numsSize, int k) {
    HashMap *map = hashmap_create(5);
    for (int i = 0; i < numsSize; i++) {
        if (hashmap_haskey(map, nums[i])) {
            int j = hashmap_get(map, nums[i]);
            if (i-j <= k) {
                hashmap_free(map);
                return true;
            }
        }
        hashmap_set(map, nums[i], i);
    }
    hashmap_free(map);
    return false;
}
