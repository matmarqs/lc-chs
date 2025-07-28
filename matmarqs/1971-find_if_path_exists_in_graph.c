#include <stdbool.h>

/***********************************************/

#include <stdlib.h>

typedef struct Vertex {
    int num;
    struct Vertex **neighbors;
    int cap;    /* maximum capacity of neighbors */
    int deg;    /* number of neighbors */
    bool visited;
} Vertex;

Vertex *create_vertex(int num) {
    Vertex *v = (Vertex *) malloc(sizeof(Vertex));
    v->num = num;
    v->cap = 1;
    v->neighbors = (Vertex **) malloc(sizeof(Vertex *) * v->cap);
    v->deg = 0;
    v->visited = false;
    return v;
}

void add_edge(Vertex *u, Vertex *v) {
    /* allocate more space if necessary */
    if (u->deg == u->cap) {
        u->cap *= 2;
        u->neighbors = (Vertex **) realloc(u->neighbors, sizeof(Vertex *) * u->cap);
    }
    if (v->deg == v->cap) {
        v->cap *= 2;
        v->neighbors = (Vertex **) realloc(v->neighbors, sizeof(Vertex *) * v->cap);
    }

    /* u <-> v as neighbors */
    u->neighbors[u->deg++] = v;
    v->neighbors[v->deg++] = u;
}

bool explore(Vertex *v, int dest) {
    v->visited = true;

    /* reached the destination */
    if (v->num == dest) {
        return true;
    }

    for (int n = 0; n < v->deg; n++) {
        if (!v->neighbors[n]->visited) {
            if (explore(v->neighbors[n], dest)) {
                return true;
            }
        }
    }

    /* explored everything and not reached destination */
    return false;
}

bool validPath(int n, int** edges, int edgesSize, int* edgesColSize, int source, int destination) {
    Vertex **vertices = (Vertex **) malloc(sizeof(Vertex *) * n);
    for (int i = 0; i < n; i++) {
        vertices[i] = create_vertex(i);
    }
    for (int e = 0; e < edgesSize; e++) {
        add_edge(vertices[edges[e][0]], vertices[edges[e][1]]);
    }

    bool result = explore(vertices[source], destination);

    /* free memory */
    for (int i = 0; i < n; i++) {
        free(vertices[i]->neighbors);
        free(vertices[i]);
    }
    free(vertices);
    
    return result;
}

/***********************************************/
