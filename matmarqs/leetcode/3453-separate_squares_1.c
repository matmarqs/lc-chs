#define min(a, b) ((a) < (b) ? (a) : (b))

long long calculate_total_area(int **squares, int n, double *y0) {
    long long area = 0LL;
    double _y0 = 0.0;
    for (int i = 0; i < n; i++) {
        int y = squares[i][1];
        int l = squares[i][2];
        area += l * l;
        _y0 += (y + l/2.0) * l * l;
    }
    *y0 = _y0;
    return area;
}

/* O(N) */
double area_below_y(int **squares, int n, int y) {
    double area = 0.0;
    for (int i = 0; i < n; i++) {
        int y_i = squares[i][1];
        int l_i = squares[i][2];
        if (y_i < y) {
            area += l_i * (min(y_i + l_i, y) - y_i);
        }
    }
    return area;
}

double separateSquares(int** squares, int squaresSize, int* squaresColSize) {
    double y0;
    double half_area = calculate_total_area(squares, squaresSize, &y0) / 2.0;
}
