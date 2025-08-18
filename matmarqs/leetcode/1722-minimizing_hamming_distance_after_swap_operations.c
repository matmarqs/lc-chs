#include <stdbool.h>

/*********************************************************/
// CSR (Compressed Sparse Row) -- This is for static graphs

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
    } \
    /* ===== ITERATOR ADDITIONS ===== */ \
    typedef struct { \
        name *map;           /* Pointer to the hashmap */ \
        int current_index;   /* Current position in the slots array */ \
    } name##_Iterator; \
    \
    /* Initialize iterator at start of map */ \
    static name##_Iterator prefix##_iterator_begin(name *map) { \
        name##_Iterator it; \
        it.map = map; \
        it.current_index = -1;  /* Start before first slot */ \
        return it; \
    } \
    \
    /* Advance iterator to next occupied slot */ \
    static bool prefix##_iterator_next(name##_Iterator *it, key_type *key, val_type *val) { \
        name *map = it->map; \
        /* Start from next slot after current position */ \
        for (int i = it->current_index + 1; i < map->capacity; i++) { \
            if (map->slots[i].state == OCCUPIED) { \
                it->current_index = i; \
                if (key) *key = map->slots[i].key; \
                if (val) *val = map->slots[i].val; \
                return true; \
            } \
        } \
        return false; /* No more elements */ \
    }


// Hash function for integers
size_t int_hash(int key) {
    return (size_t)(key * 31LL);
}

// Equality function for integers
bool int_equals(int a, int b) {
    return a == b;
}

typedef struct {
    int n;          // number of vertices
    int m;          // number of edges
    int *offsets;   // size n+1, offsets[i] = start index in edges[]
    int *edges;     // size m*2 if undirected, m if directed
    bool *visited;
} Graph;

// Create empty graph
Graph* create_graph(int n, int m, int directed) {
    Graph *g = malloc(sizeof(Graph));
    g->n = n;
    g->m = directed ? m : m * 2;
    g->offsets = calloc(n + 1, sizeof(int));
    g->edges   = malloc(sizeof(int) * g->m);
    g->visited = calloc(n, sizeof(bool));
    return g;
}

// Build adjacency list from edge list
void build_graph(Graph *g, int **edges, int m, int directed) {
    // Count degree of each vertex
    for (int i = 0; i < m; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        g->offsets[u+1]++;
        if (!directed) g->offsets[v+1]++;
    }

    // Prefix sum to get offsets
    for (int i = 1; i <= g->n; i++) {
        g->offsets[i] += g->offsets[i-1];
    }

    // Temp array to track fill positions
    int *pos = calloc(g->n, sizeof(int));

    // Fill adjacency
    for (int i = 0; i < m; i++) {
        int u = edges[i][0];
        int v = edges[i][1];

        int idx = g->offsets[u] + pos[u]++;
        g->edges[idx] = v;

        if (!directed) {
            idx = g->offsets[v] + pos[v]++;
            g->edges[idx] = u;
        }
    }

    free(pos);
}

void free_graph(Graph *g) {
    free(g->edges);
    free(g->offsets);
    free(g->visited);
    free(g);
}

DEFINE_HASHMAP(HashMap, hashmap, int, int, int_hash, int_equals, -1);

void dfs(Graph *g, int i, int *source, int *target, HashMap *h_source, HashMap *h_target) {
    if (!g->visited[i]) {
        g->visited[i] = true;

        if (!hashmap_haskey(h_source, source[i])) {
            hashmap_set(h_source, source[i], 1);
        }
        else {
            hashmap_set(h_source, source[i], hashmap_get(h_source, source[i]) + 1);
        }

        if (!hashmap_haskey(h_target, target[i])) {
            hashmap_set(h_target, target[i], 1);
        }
        else {
            hashmap_set(h_target, target[i], hashmap_get(h_target, target[i]) + 1);
        }

        for (int j = g->offsets[i]; j < g->offsets[i+1]; j++) {
            dfs(g, g->edges[j], source, target, h_source, h_target);
        }
    }
}

int min(int a, int b) {
    return a < b ? a : b;
}

int minimumHammingDistance(int* source, int sourceSize, int* target, int targetSize, int** allowedSwaps, int allowedSwapsSize, int* allowedSwapsColSize) {
    Graph *g = create_graph(sourceSize, allowedSwapsSize, 0);
    build_graph(g, allowedSwaps, allowedSwapsSize, 0);

    int count = 0;

    for (int i = 0; i < g->n; i++) {
        HashMap *h_source = hashmap_create(5);
        HashMap *h_target = hashmap_create(5);

        dfs(g, i, source, target, h_source, h_target);
        HashMap_Iterator i_source = hashmap_iterator_begin(h_source);
        int key_source, val_source;
        int val_target;
        while (hashmap_iterator_next(&i_source, &key_source, &val_source)) {
            if (hashmap_haskey(h_target, key_source)) {
                val_target = hashmap_get(h_target, key_source);
                count += min(val_source, val_target);
            }
        }

        hashmap_free(h_source);
        hashmap_free(h_target);
    }

    free_graph(g);

    return sourceSize - count;
}
