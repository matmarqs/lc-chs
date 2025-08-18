#include <stdlib.h>

int cmp_int(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int get_height(int h, int *horizontalCuts, int n, int i) {
    if (i == 0) {
        return horizontalCuts[0];
    }
    else if (i == n) {
        return h - horizontalCuts[n-1];
    }
    else {
        return horizontalCuts[i] - horizontalCuts[i-1];
    }
}

int get_width(int w, int *verticalCuts, int n, int i) {
    if (i == 0) {
        return verticalCuts[0];
    }
    else if (i == n) {
        return w - verticalCuts[n-1];
    }
    else {
        return verticalCuts[i] - verticalCuts[i-1];
    }
}

int max(int a, int b) {
    return a < b ? b : a;
}

int maxArea(int h, int w, int* horizontalCuts, int horizontalCutsSize, int* verticalCuts, int verticalCutsSize) {
    qsort(horizontalCuts, horizontalCutsSize, sizeof(int), cmp_int);
    qsort(verticalCuts, verticalCutsSize, sizeof(int), cmp_int);
    int max_w = 0, max_h = 0;
    for (int i = 0; i <= horizontalCutsSize; i++) {
        max_h = max(max_h, get_height(h, horizontalCuts, horizontalCutsSize, i));
    }
    for (int i = 0; i <= verticalCutsSize; i++) {
        max_w = max(max_w, get_width(w, verticalCuts, verticalCutsSize, i));
    }
    return (((long long) max_w) * ((long long) max_h)) % ((int)1e9 + 7);
}
