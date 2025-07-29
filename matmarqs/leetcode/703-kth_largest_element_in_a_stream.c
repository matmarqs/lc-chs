#include <stdbool.h>

/*************************************************************/
/* Usamos uma min-heap, com exatamente k elementos */
/* Assim, os k maiores elementos estarão na min-heap */
/* O menor deles é o kth_greatest, e ele está na raiz da min-heap */

#include <stdlib.h>

typedef struct {
    int *arr;
    int size;
    int capacity;
    int k;
} KthLargest;

int cmp_func(int a, int b) {
    return a < b;
}

static inline int heap_parent(int i) { return (i - 1) / 2; }
static inline int heap_left(int i) { return 2 * i + 1; }
static inline int heap_right(int i) { return 2 * i + 2; }

static void heap_sift_up(KthLargest *heap, int i) {
    while (i > 0) {
        int p = heap_parent(i);
        if (cmp_func(heap->arr[i], heap->arr[p]) > 0) {
            int tmp = heap->arr[i];
            heap->arr[i] = heap->arr[p];
            heap->arr[p] = tmp;
            i = p;
        } else {
            break;
        }
    }
}

static void heap_sift_down(KthLargest *heap, int i) {
    while (1) {
        int l = heap_left(i);
        int r = heap_right(i);
        int candidate = i;

        if (l < heap->size && cmp_func(heap->arr[l], heap->arr[candidate]) > 0) {
            candidate = l;
        }
        if (r < heap->size && cmp_func(heap->arr[r], heap->arr[candidate]) > 0) {
            candidate = r;
        }

        if (candidate == i) break;

        int tmp = heap->arr[i];
        heap->arr[i] = heap->arr[candidate];
        heap->arr[candidate] = tmp;
        i = candidate;
    }
}

static void heap_resize(KthLargest *heap) {
    int new_capacity = (heap->capacity + 1) * 2;
    int *new_arr = (int *)realloc(heap->arr, new_capacity * sizeof(int));
    heap->arr = new_arr;
    heap->capacity = new_capacity;
}

KthLargest *heap_init(int capacity) {
    KthLargest *heap = (KthLargest *)malloc(sizeof(KthLargest));
    heap->arr = (int *)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void heap_free(KthLargest *heap) {
    free(heap->arr);
    free(heap);
}

void heap_insert(KthLargest *heap, int value) {
    if (heap->size == heap->capacity) {
        heap_resize(heap);
    }
    heap->arr[heap->size] = value;
    heap->size++;
    heap_sift_up(heap, heap->size - 1);
}

int heap_extract(KthLargest *heap) {
    int top = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    heap_sift_down(heap, 0);
    return top;
}

int heap_peek(KthLargest *heap) {
    return heap->arr[0];
}

bool heap_is_empty(KthLargest *heap) {
    return heap->size == 0;
}

int heap_size(KthLargest *heap) {
    return heap->size;
}

KthLargest* kthLargestCreate(int k, int* nums, int numsSize) {
    KthLargest *heap = heap_init(numsSize);
    heap->k = k;
    for (int i = 0; i < numsSize; i++) {
        heap_insert(heap, nums[i]);
    }
    while (heap_size(heap) > k) {
        heap_extract(heap);
    }
    return heap;
}

int kthLargestAdd(KthLargest* obj, int val) {
    heap_insert(obj, val);
    if (heap_size(obj) > obj->k) {
        heap_extract(obj);
    }
    return heap_peek(obj);
}

void kthLargestFree(KthLargest* obj) {
    heap_free(obj);
}

/**
 * Your KthLargest struct will be instantiated and called as such:
 * KthLargest* obj = kthLargestCreate(k, nums, numsSize);
 * int param_1 = kthLargestAdd(obj, val);
 
 * kthLargestFree(obj);
*/
