#include <stdlib.h>
#include <stdbool.h>

#define is_visited(i, j) (visited[(i) * (n) + (j)])
#define mark_visited(i, j) do { visited[(i) * (n) + (j)] = true; } while(0);

bool is_border(int **grid, int m, int n, int i, int j, int component_color, bool *visited) {
    if (i+1 >= m || i-1 < 0) {
        return true;
    }
    if (j+1 >= n || j-1 < 0) {
        return true;
    }
    if (!is_visited(i+1, j) && grid[i+1][j] != component_color ||
        !is_visited(i-1, j) && grid[i-1][j] != component_color ||
        !is_visited(i, j+1) && grid[i][j+1] != component_color ||
        !is_visited(i, j-1) && grid[i][j-1] != component_color)
        return true;
    return false;
}

void dfs(int **grid, int m, int n, int i, int j, int component_color, bool *visited, int color) {
    if (is_border(grid, m, n, i, j, component_color, visited)) {
        grid[i][j] = color;
    }
    mark_visited(i, j);

    if (i + 1 < m && !is_visited(i+1, j) && grid[i+1][j] == component_color)
        dfs(grid, m, n, i+1, j, component_color, visited, color);

    if (i - 1 >= 0 && !is_visited(i-1, j) && grid[i-1][j] == component_color)
        dfs(grid, m, n, i-1, j, component_color, visited, color);

    if (j + 1 < n && !is_visited(i, j+1) && grid[i][j+1] == component_color)
        dfs(grid, m, n, i, j+1, component_color, visited, color);

    if (j - 1 >= 0 && !is_visited(i, j-1) && grid[i][j-1] == component_color)
        dfs(grid, m, n, i, j-1, component_color, visited, color);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** colorBorder(int** grid, int gridSize, int* gridColSize, int row, int col, int color, int* returnSize, int** returnColumnSizes) {
    *returnSize = gridSize;
    *returnColumnSizes = gridColSize;
    if (color == grid[row][col])
        return grid;

    int m = gridSize;
    int n = *gridColSize;
    int component_color = grid[row][col];
    bool *visited = calloc(m * n, sizeof(bool));

    dfs(grid, m, n, row, col, component_color, visited, color);

    free(visited);
    return grid;
}
