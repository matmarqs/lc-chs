int min(int a, int b) {
    return (a < b) ? a : b;
}

int minCostToMoveChips(int* position, int positionSize) {
    int num_odd = 0;
    int num_even = 0;
    for (int i = 0; i < positionSize; i++) {
        if (position[i] % 2 == 0) {
            num_even++;
        }
        else {
            num_odd++;
        }
    }
    return min(num_odd, num_even);
}
