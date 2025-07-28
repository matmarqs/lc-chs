#include <stdbool.h>

/******************************************************/

#include <stdlib.h>
#include <string.h>

// Macro to define a generic HashMap
#define DEFINE_HASHMAP(key_type, val_type, name, hash_func, key_equals, NOT_FOUND) \
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
    static name##_Node *name##_create_node(key_type key, val_type val) { \
        name##_Node *n = (name##_Node *)malloc(sizeof(name##_Node)); \
        n->key = key; \
        n->val = val; \
        n->next = NULL; \
        return n; \
    } \
    \
    static void name##_append_to_chain(name##_Chain *chain, key_type key, val_type val) { \
        name##_Node *new_node = name##_create_node(key, val); \
        new_node->next = chain->head; \
        chain->head = new_node; \
    } \
    \
    static void name##_free_chain(name##_Chain *chain) { \
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
    } HashMap; \
    \
    HashMap *name##_create(int cardinality) { \
        HashMap *map = (HashMap *)malloc(sizeof(HashMap)); \
        map->cardinality = cardinality; \
        map->size = 0; \
        map->chains = (name##_Chain *)malloc(sizeof(name##_Chain) * cardinality); \
        for (int i = 0; i < cardinality; i++) { \
            map->chains[i].head = NULL; \
        } \
        return map; \
    } \
    \
    void name##_free(HashMap *map) { \
        for (int i = 0; i < map->cardinality; i++) { \
            name##_free_chain(&map->chains[i]); \
        } \
        free(map->chains); \
        free(map); \
    } \
    \
    int name##_haskey(HashMap *map, key_type key) { \
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
    val_type name##_get(HashMap *map, key_type key) { \
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
        return NOT_FOUND; \
    } \
    \
    void name##_set(HashMap *map, key_type key, val_type val) { \
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
        name##_append_to_chain(chain, key, val); \
        map->size++; \
    } \
    \
    void name##_remove(HashMap *map, key_type key) { \
        size_t hash_val = hash_func(key); \
        int idx = (int)(hash_val % (size_t)map->cardinality); \
        name##_Chain *chain = &map->chains[idx]; \
        name##_Node *current = chain->head; \
        if (!current) return; \
        \
        if (key_equals(current->key, key)) { \
            chain->head = current->next; \
            free(current); \
            map->size--; \
            return; \
        } \
        \
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

// Hash function for integers
size_t char_hash(char key) {
    return (size_t)(key * 31);
}

// Equality function for integers
bool char_equals(char a, char b) {
    return a == b;
}

DEFINE_HASHMAP(char, char, hashmap, char_hash, char_equals, '\0');

bool isIsomorphic_HashMap(char* s, char* t) {
    size_t len_s = strlen(s);
    size_t len_t = strlen(t);
    if (len_s != len_t)
        return false;
    
    HashMap *map1 = hashmap_create(256);
    HashMap *map2 = hashmap_create(256);
    for (int i = 0; i < len_s; i++) {
        if (!hashmap_haskey(map1, s[i])) {
            hashmap_set(map1, s[i], t[i]);
        }
        else {
            if (hashmap_get(map1, s[i]) != t[i]) {
                return false;
            }
        }

        if (!hashmap_haskey(map2, t[i])) {
            hashmap_set(map2, t[i], s[i]);
        }
        else {
            if (hashmap_get(map2, t[i]) != s[i]) {
                return false;
            }
        }
    }

    return true;
}

/******************************************************/


bool isIsomorphic(char* s, char* t) {
    size_t len_s = strlen(s);
    size_t len_t = strlen(t);
    if (len_s != len_t)
        return false;
    
    char map1[256] = { '\0' };
    char map2[256] = { '\0' };
    for (int i = 0; i < len_s; i++) {
        if (map1[s[i]] == '\0') {
            map1[s[i]] = t[i];
        }
        else {
            if (map1[s[i]] != t[i]) {
                return false;
            }
        }

        if (map2[t[i]] == '\0') {
            map2[t[i]] = s[i];
        }
        else {
            if (map2[t[i]] != s[i]) {
                return false;
            }
        }
    }

    return true;
}
