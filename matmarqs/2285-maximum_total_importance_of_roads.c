#include <stdlib.h>

typedef struct {
    int num;
    int degree;
} City;

int cmp_cities(const void *a, const void *b) {
    return (*(City *)a).degree - (*(City *)b).degree;
}

long long maximumImportance(int n, int** roads, int roadsSize, int* roadsColSize) {
    int V = n;
    int E = roadsSize;

    City *cities = malloc(sizeof(City) * V);
    for (int i = 0; i < V; i++) {
        cities[i].num = i;
        cities[i].degree = 0;
    }

    for (int i = 0; i < E; i++) {
        cities[roads[i][0]].degree++;
        cities[roads[i][1]].degree++;
    }

    qsort(cities, V, sizeof(City), cmp_cities);

    long long total_importance = 0;
    for (long long i = 0; i < V; i++) {
        total_importance += (i + 1) * cities[i].degree;
    }

    free(cities);
    return total_importance;
}
