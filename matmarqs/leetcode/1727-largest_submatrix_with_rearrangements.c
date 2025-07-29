#include <stdio.h>

void print_matrix(int **mat, int m, int n) {
    for (int i = 0; i < m; i++) {
        printf("[ ");
        for (int j = 0; j < n; j++) {
            printf("%d%s ", mat[i][j], j == n-1 ? "" : ",");
        }
        printf("]\n");
    }
}

/************************************************************/

#include <stdlib.h>

int cmp_dec(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

/* O(N log N) */
int largestAreaSubmatrixInRow(int *row, int n) {
    qsort(row, n, sizeof(int), cmp_dec);
    int area = row[0];
    for (int j = 1; j < n; j++) {
        area = max(area, min(row[j], row[j-1]) * (j+1));
    }
    return area;
}

int largestSubmatrix(int** matrix, int matrixSize, int* matrixColSize) {
    int m = matrixSize;
    int n = *matrixColSize;

    /* cumulative sum */
    for (int j = 0; j < n; j++) {
        for (int i = 1; i < m; i++) {
            matrix[i][j] = matrix[i][j] ? matrix[i-1][j] + 1 : 0;
        }
    }

    //print_matrix(matrix, m, n);
    //printf("\n\n");

    int area = 0;
    for (int i = 0; i < m; i++) {
        area = max(area, largestAreaSubmatrixInRow(matrix[i], n));
    }

    //print_matrix(matrix, m, n);

    return area;
}

/*
[ 0 0 1 ]    [ 0 0 1 ]
[ 1 1 1 ] -> [ 1 1 2 ]
[ 1 0 1 ]    [ 2 0 3 ]

m * n

m * n log(n)


[ 100 3 2 1 0 0 0 ]

area = 100
area = max(area, min(r[i], r[i-1]) * i)


[ 1 1 0 ] -> [ 1 1 0 ]
[ 1 0 1 ]    [ 2 0 1 ]
*/
