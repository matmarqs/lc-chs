#include <stdlib.h>

int cmp(const void *a, const void *b) {
    const int *ea = (const int *)a;
    const int *eb = (const int *)b;
    // Sort by frequency descending, then by value descending
    if (eb[1] != ea[1]) {
        return eb[1] - ea[1];
    }
    else {
        return eb[0] - ea[0];
    }
}

/* O(len) */
int x_sum(int *array, int len, int x) {
    int freq[51][2] = { 0 };   /* hash table, 1 <= array[i] <= 50, zero-memory stack initialization, very fast */
    /* freq[i][0] = i (original_index), freq[i][1] = 0 (frequency of array[i]) */

    // initialize values
    for (int i = 0; i < 51; i++) {
        freq[i][0] = i;
    }

    // count frequencies
    for (int i = 0; i < len; i++) {
        freq[array[i]][1]++;
    }

    // sort by frequency (descending), then by value (descending)
    qsort(freq, 51, sizeof(freq[0]), cmp);

    int xsum = 0;
    for (int i = 0; i < x; i++) {
        xsum += freq[i][0] * freq[i][1];
    }

    return xsum;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

/* O((n-k+1) * k) */
/* when k = n/2, this is O(n^2) */
/* this can be improved by Sliding Window technique */
int* findXSum(int* nums, int numsSize, int k, int x, int* returnSize) {
    int answer_len = numsSize - k + 1;
    int *answer = (int *) malloc(answer_len * sizeof(int));
    *returnSize = answer_len;

    /* loop (n-k+1) times */
    for (int i = 0; i < answer_len; i++) {
        answer[i] = x_sum(nums+i, k, x);    /* O(k) */
    }

    return answer;
}
