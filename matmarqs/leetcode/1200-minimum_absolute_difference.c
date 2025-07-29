#include <stdlib.h>

int cmp_int(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

/* O(N log N) because we sort */
int** minimumAbsDifference(int* arr, int arrSize, int* returnSize, int** returnColumnSizes) {
    int size = 0;
    int capacity = 2;
    int **return_array = (int **) malloc(sizeof(int *) * capacity);

    qsort(arr, arrSize, sizeof(int), cmp_int);

    int min_diff = +3000001;
    for (int i = 0; i < arrSize-1; i++) {
        min_diff = min(min_diff, arr[i+1] - arr[i]);
    }

    for (int i = 0; i < arrSize-1; i++) {
        if (arr[i+1] - arr[i] == min_diff) {
            int *pair = (int *) malloc(sizeof(int) * 2);
            pair[0] = arr[i];
            pair[1] = arr[i+1];
            if (size >= capacity) {
                capacity = 2 * capacity + 1;
                return_array = (int **) realloc(return_array, sizeof(int *) * capacity);
            }
            return_array[size++] = pair;
        }
    }

    *returnSize = size;
    *returnColumnSizes = (int *) malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        (*returnColumnSizes)[i] = 2;
    }
    return return_array;
}
