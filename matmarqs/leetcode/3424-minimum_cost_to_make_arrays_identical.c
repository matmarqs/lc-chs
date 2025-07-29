/* my first solution below, which is Theta(N log N) */

#include <stdlib.h>

int cmp_int(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

long long get_x_total_cost(int *arr, int *brr, int size) {
    long long sum = 0LL;
    for (int i = 0; i < size; i++) {
        sum += llabs(arr[i] - brr[i]);
    }
    return sum;
}

long long minCost_qsort(int* arr, int arrSize, int* brr, int brrSize, long long k) {
    long long without_first = get_x_total_cost(arr, brr, arrSize);

    qsort(arr, arrSize, sizeof(int), cmp_int);
    qsort(brr, brrSize, sizeof(int), cmp_int);

    long long with_first = get_x_total_cost(arr, brr, arrSize) + k;

    if (without_first <= with_first) {   /* do not use first operation */
        return without_first;
    }
    else {  /* use first and second operation */
        return with_first;
    }
}


/* Below is the code for min heap */

int parent(int i) { return (i - 1) / 2; }
int left(int i) { return 2 * i + 1; }
int right(int i) { return 2 * i + 2; }

void sift_up(int *heap, int i) {
    while (i > 0) {
        int p = parent(i);
        if (heap[i] < heap[p]) {
            int tmp = heap[i];
            heap[i] = heap[p];
            heap[p] = tmp;
            i = p;
        } else {
            break;
        }
    }
}

void sift_down(int *heap, int size, int i) {
    while (1) {
        int l = left(i);
        int r = right(i);
        int candidate = i;
       
        if (l < size && heap[l] < heap[candidate]) {
            candidate = l;
        }
        if (r < size && heap[r] < heap[candidate]) {
            candidate = r;
        }
       
        if (candidate == i) break;
       
        int tmp = heap[i];
        heap[i] = heap[candidate];
        heap[candidate] = tmp;
        i = candidate;
    }
}

void build_heap(int *array, int size) {
    for (int i = (size-1)/2; i >= 0; i--){
        sift_down(array, size, i);
    }
}
