int islandPerimeter(int** grid, int gridSize, int* gridColSize) {
    int perimeter = 0;
    int rows = gridSize;
    int cols = *gridColSize;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (grid[i][j]) {
                perimeter += 4;

                if (i-1 >= 0 && grid[i-1][j])
                    perimeter--;

                if (j-1 >= 0 && grid[i][j-1])
                    perimeter--;

                if (i+1 < rows && grid[i+1][j])
                    perimeter--;

                if (j+1 < cols && grid[i][j+1])
                    perimeter--;
            }

    return perimeter;
}
