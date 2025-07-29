#include <stdlib.h>

/* Below is the code for max heap */
/* just the methods, build_heap and extract_max */

int _left(int i) { return 2 * i + 1; }
int _right(int i) { return 2 * i + 2; }

void _sift_down(int *heap, int size, int i) {
    while (1) {
        int l = _left(i);
        int r = _right(i);
        int candidate = i;
       
        if (l < size && heap[l] > heap[candidate]) {
            candidate = l;
        }
        if (r < size && heap[r] > heap[candidate]) {
            candidate = r;
        }
       
        if (candidate == i) break;
       
        int tmp = heap[i];
        heap[i] = heap[candidate];
        heap[candidate] = tmp;
        i = candidate;
    }
}

int extract_max(int *heap, int *size) {
    int top = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    _sift_down(heap, *size, 0);
    return top;
}

void build_heap(int *array, int size) {
    for (int i = (size-1)/2; i >= 0; i--){
        _sift_down(array, size, i);
    }
}

/* O(N + k * log(N)) */
int miceAndCheese(int* reward1, int reward1Size, int* reward2, int reward2Size, int k) {
    /* if mouse 2 were to eat all the cheese, the sum would be this */
    int sum = 0;
    for (int i = 0; i < reward2Size; i++) {
        sum += reward2[i];
    }

    if (k > 0) {
        /* if k > 0, the mouse 1 eats k types of cheese */

        /* O(N) */
        int size = reward1Size;
        int *heap = (int *) malloc(sizeof(int) * size);

        /* O(N) */
        for (int i = 0; i < size; i++) {
            heap[i] = reward1[i] - reward2[i];
        }
        build_heap(heap, size); /* also O(N) */

        /* O(k * log(N)) */
        for (int i = 0; i < k; i++) {
            sum += extract_max(heap, &size);
        }

        free(heap);
    }

    return sum;
}
