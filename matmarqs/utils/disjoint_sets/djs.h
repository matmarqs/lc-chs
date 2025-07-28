#ifndef DISJOINT_SETS_H
#define DISJOINT_SETS_H

#include <stdlib.h>
#include <stdbool.h>

#define DEFINE_DISJOINT_SETS(prefix, name) \
    \
    typedef struct { \
        int *rank; \
        int *parent; \
        int capacity; \
    } name; \
    \
    static void prefix##_resize(name *djs, int new_capacity) { \
        int *new_rank = (int *)realloc(djs->rank, new_capacity * sizeof(int)); \
        int *new_parent = (int *)realloc(djs->parent, new_capacity * sizeof(int)); \
        if (!new_rank || !new_parent) { \
            free(new_rank); \
            free(new_parent); \
            return; \
        } \
        djs->rank = new_rank; \
        djs->parent = new_parent; \
        djs->capacity = new_capacity; \
    } \
    \
    name *prefix##_create(int initial_capacity) { \
        name *djs = (name *)malloc(sizeof(name)); \
        djs->rank = (int *)malloc(initial_capacity * sizeof(int)); \
        djs->parent = (int *)malloc(initial_capacity * sizeof(int)); \
        djs->capacity = initial_capacity; \
        return djs; \
    } \
    \
    void prefix##_free(name *djs) { \
        free(djs->rank); \
        free(djs->parent); \
        free(djs); \
    } \
    \
    void prefix##_ensure_capacity(name *djs, int i) { \
        if (i >= djs->capacity) { \
            int new_capacity = (i + 1) * 2; \
            prefix##_resize(djs, new_capacity); \
        } \
    } \
    \
    void prefix##_make_set(name *djs, int i) { \
        prefix##_ensure_capacity(djs, i); \
        djs->parent[i] = i; \
        djs->rank[i] = 0; \
    } \
    \
    int prefix##_find(name *djs, int i) { \
        prefix##_ensure_capacity(djs, i); \
        while (i != djs->parent[i]) { \
            djs->parent[i] = djs->parent[djs->parent[i]]; \
            i = djs->parent[i]; \
        } \
        return i; \
    } \
    \
    bool prefix##_same_set(name *djs, int i, int j) { \
        return prefix##_find(djs, i) == prefix##_find(djs, j); \
    } \
    \
    void prefix##_unite(name *djs, int i, int j) { \
        int i_id = prefix##_find(djs, i); \
        int j_id = prefix##_find(djs, j); \
        if (i_id == j_id) return; \
        \
        prefix##_ensure_capacity(djs, i_id); \
        prefix##_ensure_capacity(djs, j_id); \
        \
        if (djs->rank[i_id] > djs->rank[j_id]) { \
            djs->parent[j_id] = i_id; \
        } else { \
            djs->parent[i_id] = j_id; \
            if (djs->rank[i_id] == djs->rank[j_id]) { \
                djs->rank[j_id]++; \
            } \
        } \
    } \
    \
    int prefix##_get_capacity(name *djs) { \
        return djs->capacity; \
    }

#endif // DISJOINT_SETS_H
