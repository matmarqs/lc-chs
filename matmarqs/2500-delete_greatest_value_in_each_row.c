#include <stdlib.h>

int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);  // ascending
}

int deleteGreatestValue(int** grid, int gridSize, int* gridColSize){
    int m = gridSize;
    int n = gridColSize[0];  // assuming all rows have the same length

    // Sort each row in ascending order
    for (int i = 0; i < m; i++) {
        qsort(grid[i], n, sizeof(int), cmp);
    }

    int ans = 0;
    // Traverse from last column to first
    for (int col = n - 1; col >= 0; col--) {
        int max_in_col = 0;
        for (int row = 0; row < m; row++) {
            if (grid[row][col] > max_in_col) {
                max_in_col = grid[row][col];
            }
        }
        ans += max_in_col;
    }

    return ans;
}
