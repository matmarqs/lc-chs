#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include <stdbool.h>

#define DEFINE_HEAP(name, prefix, type, cmp_func) \
    \
    typedef struct { \
        type *arr; \
        int size; \
        int capacity; \
    } name; \
    \
    static inline int prefix##_parent(int i) { return (i - 1) / 2; } \
    static inline int prefix##_left(int i) { return 2 * i + 1; } \
    static inline int prefix##_right(int i) { return 2 * i + 2; } \
    \
    static void prefix##_sift_up(name *heap, int i) { \
        while (i > 0) { \
            int p = prefix##_parent(i); \
            if (cmp_func(heap->arr[i], heap->arr[p]) > 0) { \
                type tmp = heap->arr[i]; \
                heap->arr[i] = heap->arr[p]; \
                heap->arr[p] = tmp; \
                i = p; \
            } else { \
                break; \
            } \
        } \
    } \
    \
    static void prefix##_sift_down(name *heap, int i) { \
        while (1) { \
            int l = prefix##_left(i); \
            int r = prefix##_right(i); \
            int candidate = i; \
            \
            if (l < heap->size && cmp_func(heap->arr[l], heap->arr[candidate]) > 0) { \
                candidate = l; \
            } \
            if (r < heap->size && cmp_func(heap->arr[r], heap->arr[candidate]) > 0) { \
                candidate = r; \
            } \
            \
            if (candidate == i) break; \
            \
            type tmp = heap->arr[i]; \
            heap->arr[i] = heap->arr[candidate]; \
            heap->arr[candidate] = tmp; \
            i = candidate; \
        } \
    } \
    \
    static void prefix##_resize(name *heap) { \
        int new_capacity = heap->capacity * 2; \
        type *new_arr = (type *)realloc(heap->arr, new_capacity * sizeof(type)); \
        heap->arr = new_arr; \
        heap->capacity = new_capacity; \
    } \
    \
    name *prefix##_init(int capacity) { \
        name *heap = (name *)malloc(sizeof(name)); \
        heap->arr = (type *)malloc(capacity * sizeof(type)); \
        heap->size = 0; \
        heap->capacity = capacity; \
        return heap; \
    } \
    \
    void prefix##_free(name *heap) { \
        free(heap->arr); \
        free(heap); \
    } \
    \
    void prefix##_insert(name *heap, type value) { \
        if (heap->size == heap->capacity) { \
            prefix##_resize(heap); \
        } \
        heap->arr[heap->size] = value; \
        heap->size++; \
        prefix##_sift_up(heap, heap->size - 1); \
    } \
    \
    type prefix##_extract(name *heap) { \
        type top = heap->arr[0]; \
        heap->arr[0] = heap->arr[heap->size - 1]; \
        heap->size--; \
        prefix##_sift_down(heap, 0); \
        return top; \
    } \
    \
    type prefix##_peek(name *heap) { \
        return heap->arr[0]; \
    } \
    \
    bool prefix##_is_empty(name *heap) { \
        return heap->size == 0; \
    } \
    \
    int prefix##_size(name *heap) { \
        return heap->size; \
    }

#endif // HEAP_H
