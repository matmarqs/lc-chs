#include <stdlib.h>

typedef struct {
    int index;
    int num_soldiers;
} Row;

int cmp_rows(const void *a, const void *b) {
    Row ra = *(Row *)a;
    Row rb = *(Row *)b;
    if (ra.num_soldiers == rb.num_soldiers) {
        return ra.index - rb.index;
    }
    else {
        return ra.num_soldiers - rb.num_soldiers;
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* kWeakestRows(int** mat, int matSize, int* matColSize, int k, int* returnSize) {
    int m = matSize;
    int n = matColSize[0];

    Row *rows = (Row *) malloc(sizeof(Row) * m);

    for (int i = 0; i < m; i++) {
        int num_soldiers = 0;
        for (int j = 0; j < n; j++) {
            num_soldiers += mat[i][j];
        }
        rows[i].index = i;
        rows[i].num_soldiers = num_soldiers;
    }

    qsort(rows, m, sizeof(Row), cmp_rows);

    *returnSize = k;
    int *return_rows = (int *) malloc(sizeof(int) * k);

    for (int i = 0; i < k; i++) {
        return_rows[i] = rows[i].index;
    }

    free(rows);
    return return_rows;
}
