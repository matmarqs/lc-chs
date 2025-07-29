#include <stdbool.h>

/***********************************************/

#include <stdlib.h>

typedef struct DisjointSets {
    int *rank;
    int *parent;
    int size;
} DisjointSets;

DisjointSets *init_disjoint_sets(int size) {
    DisjointSets *djsets = (DisjointSets *) malloc(sizeof(DisjointSets));
    djsets->rank = (int *) malloc(sizeof(int) * size);
    djsets->parent = (int *) malloc(sizeof(int) * size);
    djsets->size = size;
    return djsets;
}

void djsets_make(DisjointSets *djsets, int i) {
    djsets->parent[i] = i;
    djsets->rank[i] = 0;
}

int djsets_find(DisjointSets *djsets, int i) {
    while (i != djsets->parent[i]) {
        djsets->parent[i] = djsets->parent[djsets->parent[i]];  // Path compression
        i = djsets->parent[i];
    }
    return i;
}

void djsets_union(DisjointSets *djsets, int i, int j) {
    int i_id = djsets_find(djsets, i);
    int j_id = djsets_find(djsets, j);

    if (i_id == j_id)
        return;

    int *rank = djsets->rank;
    int *parent = djsets->parent;

    if (rank[i_id] > rank[j_id]) {
        parent[j_id] = i_id;
    }
    else {
        parent[i_id] = j_id;
        if (rank[i_id] == rank[j_id]) {
            rank[j_id] += 1;
        }
    }
}

void djsets_free(DisjointSets *djsets) {
    free(djsets->rank);
    free(djsets->parent);
    free(djsets);
}

bool validPath(int n, int** edges, int edgesSize, int* edgesColSize, int source, int destination) {
    if (source == destination) return true;

    DisjointSets *djsets = init_disjoint_sets(n);

    for (int i = 0; i < n; i++) {
        djsets_make(djsets, i);
    }

    for (int e = 0; e < edgesSize; e++) {
        djsets_union(djsets, edges[e][0], edges[e][1]);
    }

    bool result = djsets_find(djsets, source) == djsets_find(djsets, destination);

    free(djsets->rank);
    free(djsets->parent);
    free(djsets);

    return result;
}

/***********************************************/
