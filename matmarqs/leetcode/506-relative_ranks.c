#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int score;
    int index;
} Athlete;

typedef struct {
    Athlete *arr;
    int size;
    int cap;
} Heap;

Heap *heap_init(int capacity) {
    Heap *heap = (Heap *) malloc(sizeof(Heap));
    heap->size = 0;
    heap->cap = capacity;
    heap->arr = (Athlete *) malloc(sizeof(Athlete) * capacity);
    return heap;
}

void heap_free(Heap *heap) {
    free(heap->arr);
    free(heap);
}

int parent(int i) {
    return (i-1)/2;
}

int left_child(int i) {
    return 2*i + 1;
}

int right_child(int i) {
    return 2*i + 2;
}

void swap(Athlete *a, Athlete *b) {
    Athlete aux = *a;
    *a = *b;
    *b = aux;
}

void sift_up(Heap *heap, int i) {
    while (heap->arr[i].score > heap->arr[parent(i)].score) {
        swap(&heap->arr[i], &heap->arr[parent(i)]);
        i = parent(i);
    }
}

void sift_down(Heap *heap, int i) {
    int max_index = i;
    if (left_child(i) < heap->size && heap->arr[left_child(i)].score > heap->arr[max_index].score) {
            max_index = left_child(i);
    }
    if (right_child(i) < heap->size && heap->arr[right_child(i)].score > heap->arr[max_index].score) {
            max_index = right_child(i);
    }
    if (max_index != i) {
        swap(&heap->arr[i], &heap->arr[max_index]);
        sift_down(heap, max_index);
    }
}

void insert(Heap *heap, int index, int score) {
    heap->size++;
    Athlete ath;
    ath.index = index;
    ath.score = score;
    heap->arr[heap->size-1] = ath;
    sift_up(heap, heap->size-1);
}

Athlete extract_max(Heap *heap) {
    Athlete max = heap->arr[0];
    swap(&heap->arr[0], &heap->arr[heap->size-1]);
    heap->size--;
    sift_down(heap, 0);
    return max;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** findRelativeRanks(int* score, int scoreSize, int* returnSize) {
    *returnSize = scoreSize;
    Heap *heap = heap_init(scoreSize);

    for (int i = 0; i < scoreSize; i++) {
        insert(heap, i, score[i]);
    }

    char **ranks = (char **) malloc(sizeof(char *) * scoreSize);

    Athlete max;
    for (int i = 0; i < scoreSize; i++) {
        max = extract_max(heap);
        switch (i) {
            case 0:
                ranks[max.index] = strdup("Gold Medal");
                break;
            case 1:
                ranks[max.index] = strdup("Silver Medal");
                break;
            case 2:
                ranks[max.index] = strdup("Bronze Medal");
                break;
            default:
                ;   /* Label followed by a declaration is a C23 extension */
                char *numStr = (char *) malloc(6 * sizeof(char));
                sprintf(numStr, "%d", i+1);
                ranks[max.index] = numStr;
        }
    }

    heap_free(heap);

    return ranks;
}
