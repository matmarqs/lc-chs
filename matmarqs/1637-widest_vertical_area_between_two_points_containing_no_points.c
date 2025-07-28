#include <stdlib.h>

int cmp_points_by_x(const void *a, const void *b) {
    int *pa = *(int **) a;
    int *pb = *(int **) b;
    return pa[0] - pb[0];
}

int max(int a, int b) {
    return a > b ? a : b;
}

/* Sorting, so O(N log N) */
int maxWidthOfVerticalArea(int** points, int pointsSize, int* pointsColSize) {
    qsort(points, pointsSize, sizeof(int *), cmp_points_by_x);
    int max_diff = 0;
    for (int i = 0; i < pointsSize-1; i++) {
        max_diff = max(max_diff, points[i+1][0] - points[i][0]);
    }
    return max_diff;
}
