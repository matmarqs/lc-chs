#include <stdbool.h>

/***********************************************************************/

#include <stdlib.h>

int hash(int n) {
    return n-1;
}

bool is_in(bool *set, int x) {
    return set[hash(x)];
}

void add(bool *set, int x) {
    set[hash(x)] = true;
}

void empty(bool *set, int size) {
    for (int i = 0; i < size; i++) {
        set[i] = false;
    }
}

bool checkValid(int** matrix, int matrixSize, int* matrixColSize) {
    int n = matrixSize;
    bool *set = (bool *) calloc(n, sizeof(bool));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (is_in(set, matrix[i][j])) {
                free(set);
                return false;
            }
            add(set, matrix[i][j]);
        }
        empty(set, n);
    }

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            if (is_in(set, matrix[i][j])) {
                free(set);
                return false;
            }
            add(set, matrix[i][j]);
        }
        empty(set, n);
    }

    free(set);
    return true;
}
