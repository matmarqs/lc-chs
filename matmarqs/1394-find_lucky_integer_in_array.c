int findLucky(int* arr, int arrSize) {
    int freq[501] = {0};

    for (int i = 0; i < arrSize; i++) {
        freq[arr[i]]++;
    }

    int max = -1;
    for (int i = 1; i < 501; i++) {
        if (i == freq[i]) {
            max = i;
        }
    }
    return max;
}
