#include <stdlib.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** generate(int numRows, int* returnSize, int** returnColumnSizes) {
    *returnSize = numRows;
    int **triangle = (int **) malloc(sizeof(int *) * (*returnSize));
    *returnColumnSizes = (int *) malloc(sizeof(int) * (*returnSize));
    *returnColumnSizes[0] = 1;
    triangle[0] = (int *) malloc(sizeof(int) * (*returnColumnSizes[0]));
    triangle[0][0] = 1;
    for (int i = 1; i < *returnSize; i++) {
        (*returnColumnSizes)[i] = i+1;
        triangle[i] = (int *) malloc(sizeof(int) * ((*returnColumnSizes)[i]));
        triangle[i][0] = 1;
        triangle[i][(*returnColumnSizes)[i] - 1] = 1;
        for (int j = 1; j < (*returnColumnSizes)[i] - 1; j++) {
            triangle[i][j] = triangle[i-1][j-1] + triangle[i-1][j];
        }
    }
    return triangle;
}
