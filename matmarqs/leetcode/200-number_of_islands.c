#include <stdbool.h>

/**************************************/

void traversal(char **grid, int m, int n, int i, int j) {
    grid[i][j] = '2';
    if (i-1 >= 0 && grid[i-1][j] == '1') {
        traversal(grid, m, n, i-1, j);
    }
    if (i+1 <  m && grid[i+1][j] == '1') {
        traversal(grid, m, n, i+1, j);
    }
    if (j-1 >= 0 && grid[i][j-1] == '1') {
        traversal(grid, m, n, i, j-1);
    }
    if (j+1 <  n && grid[i][j+1] == '1') {
        traversal(grid, m, n, i, j+1);
    }
}

int numIslands(char** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = *gridColSize;
    int count = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '1') {
                traversal(grid, m, n, i, j);
                count++;
            }
        }
    }
    return count;
}
