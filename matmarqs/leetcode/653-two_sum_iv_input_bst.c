#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/******************************************************/

#include <stdlib.h>

#define DEFINE_HASHSET(name, prefix, key_type, hash_func, key_equals) \
    \
    typedef struct name##_Node { \
        key_type key; \
        struct name##_Node *next; \
    } name##_Node; \
    \
    typedef struct { \
        name##_Node *head; \
    } name##_Chain; \
    \
    static name##_Node *prefix##_inner_create_node(key_type key) { \
        name##_Node *n = (name##_Node *)malloc(sizeof(name##_Node)); \
        n->key = key; \
        n->next = NULL; \
        return n; \
    } \
    \
    static void prefix##_inner_append_to_chain(name##_Chain *chain, key_type key) { \
        name##_Node *new_node = prefix##_inner_create_node(key); \
        new_node->next = chain->head; \
        chain->head = new_node; \
    } \
    \
    static bool prefix##_inner_chain_contains(name##_Chain *chain, key_type key) { \
        name##_Node *current = chain->head; \
        while (current) { \
            if (key_equals(current->key, key)) { \
                return true; \
            } \
            current = current->next; \
        } \
        return false; \
    } \
    \
    static void prefix##_inner_remove_from_chain(name##_Chain *chain, key_type key) { \
        name##_Node *current = chain->head; \
        if (!current) return; \
        \
        if (key_equals(current->key, key)) { \
            chain->head = current->next; \
            free(current); \
            return; \
        } \
        \
        while (current->next) { \
            if (key_equals(current->next->key, key)) { \
                name##_Node *to_remove = current->next; \
                current->next = to_remove->next; \
                free(to_remove); \
                return; \
            } \
            current = current->next; \
        } \
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
    } name; \
    \
    static void prefix##_inner_rehash(name *set, int new_cardinality) { \
        name##_Chain *new_chains = (name##_Chain *)malloc(sizeof(name##_Chain) * new_cardinality); \
        if (!new_chains) return; \
        for (int i = 0; i < new_cardinality; i++) { \
            new_chains[i].head = NULL; \
        } \
        int old_cardinality = set->cardinality; \
        name##_Chain *old_chains = set->chains; \
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
        set->chains = new_chains; \
        set->cardinality = new_cardinality; \
        free(old_chains); \
    } \
    \
    name *prefix##_create(int cardinality) { \
        name *set = (name *)malloc(sizeof(name)); \
        set->cardinality = cardinality; \
        set->size = 0; \
        set->chains = (name##_Chain *)malloc(sizeof(name##_Chain) * cardinality); \
        for (int i = 0; i < cardinality; i++) { \
            set->chains[i].head = NULL; \
        } \
        return set; \
    } \
    \
    void prefix##_free(name *set) { \
        for (int i = 0; i < set->cardinality; i++) { \
            prefix##_inner_free_chain(&set->chains[i]); \
        } \
        free(set->chains); \
        free(set); \
    } \
    \
    bool prefix##_contains(name *set, key_type key) { \
        size_t hash_val = hash_func(key); \
        int idx = (int)(hash_val % (size_t)set->cardinality); \
        return prefix##_inner_chain_contains(&set->chains[idx], key); \
    } \
    \
    void prefix##_add(name *set, key_type key) { \
        size_t hash_val = hash_func(key); \
        int idx = (int)(hash_val % (size_t)set->cardinality); \
        name##_Chain *chain = &set->chains[idx]; \
        if (!prefix##_inner_chain_contains(chain, key)) { \
            prefix##_inner_append_to_chain(chain, key); \
            set->size++; \
            if ((long long)set->size * 4 > (long long)set->cardinality * 3) { \
                prefix##_inner_rehash(set, set->cardinality * 2); \
            } \
        } \
    } \
    \
    void prefix##_remove(name *set, key_type key) { \
        size_t hash_val = hash_func(key); \
        int idx = (int)(hash_val % (size_t)set->cardinality); \
        name##_Chain *chain = &set->chains[idx]; \
        if (prefix##_inner_chain_contains(chain, key)) { \
            prefix##_inner_remove_from_chain(chain, key); \
            set->size--; \
        } \
    }

// Hash function for integers or chars
size_t int_hash(int key) {
    return (size_t)(key * 31);
}

// Equality function for integers or chars
bool int_equals(int a, int b) {
    return a == b;
}

DEFINE_HASHSET(HashSet, hashset, int, int_hash, int_equals);


bool PreOrderTraversal(struct TreeNode *root, int k, HashSet *set) {
    if (!root) {
        return false;
    }

    if (hashset_contains(set, k-root->val)) {
        return true;
    }
    hashset_add(set, root->val);

    return PreOrderTraversal(root->left, k, set) || PreOrderTraversal(root->right, k, set);
}

bool findTarget(struct TreeNode* root, int k) {
    HashSet *set = hashset_create(15);

    return PreOrderTraversal(root, k, set);
}
