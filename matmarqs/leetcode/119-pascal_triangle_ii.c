#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getRow(int rowIndex, int* returnSize) {
    *returnSize = rowIndex+1;
    int *row = (int *) malloc(sizeof(int) * (rowIndex + 1));
    row[0] = 1;
    for (int i = 1; i < rowIndex + 1; i++) {
        row[i] = 1;
        int aux1 = row[0], aux2 = row[1];
        for (int j = 1; j < i; j++) {
            aux2 = row[j];
            row[j] = aux1 + aux2;
            aux1 = aux2;
        }
    }
    return row;
}
