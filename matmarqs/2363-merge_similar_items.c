#include <stdlib.h>

/* compare items by value */
int cmp_item(const void *a, const void *b) {
    int **item_a = (int **)a;
    int **item_b = (int **)b;
    return (*item_a)[0] - (*item_b)[0];
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** mergeSimilarItems(int** items1, int items1Size, int* items1ColSize, int** items2, int items2Size, int* items2ColSize, int* returnSize, int** returnColumnSizes) {
    int **ret = (int **)malloc(sizeof(int *) * (items1Size + items2Size));
    for (int i = 0; i < items1Size + items2Size; i++) {
        ret[i] = (int *)malloc(sizeof(int) * 2);
    }
    int size = 0;

    qsort(items1, items1Size, sizeof(int *), cmp_item);
    qsort(items2, items2Size, sizeof(int *), cmp_item);

    int i1 = 0;
    int i2 = 0;
    while (i1 < items1Size || i2 < items2Size) {
        if (i1 < items1Size && i2 < items2Size && items1[i1][0] == items2[i2][0]) {
            ret[size][0] = items1[i1][0];
            ret[size][1] = items1[i1][1] + items2[i2][1];
            i1++;
            i2++;
        }
        else if (i2 >= items2Size || (i1 < items1Size && items1[i1][0] < items2[i2][0])) {
            ret[size][0] = items1[i1][0];
            ret[size][1] = items1[i1][1];
            i1++;
        }
        else {  /* i1 >= items1Size || items2[i2][0] < items1[i1][0] */
            ret[size][0] = items2[i2][0];
            ret[size][1] = items2[i2][1];
            i2++;
        }
        size++;
    }

    *returnSize = size;
    *returnColumnSizes = (int *)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        (*returnColumnSizes)[i] = 2;
    }
    return ret;
}
