#include <stdlib.h>

/* the idea is, use the value abs(nums[i])-1 as index */
/* we invert the sign of this index */
/* if we already have a minus sign, it means that we have a duplicate */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

/* O(N) runtime and O(1) space (excluding the return array) */
int* findDuplicates(int* nums, int numsSize, int* returnSize) {
    int size = 0;
    for (int i = 0; i < numsSize; i++) {
        int x = abs(nums[i]);
        if (nums[x-1] < 0) {
            size++;
        }
        nums[x-1] *= -1;
    }

    *returnSize = size;
    int *return_array = (int *) malloc(sizeof(int) * size);
    size = 0;

    // Reset the array to positive values first
    for (int i = 0; i < numsSize; i++) {
        nums[i] = abs(nums[i]);
    }

    // Now find duplicates again
    for (int i = 0; i < numsSize; i++) {
        int x = abs(nums[i]);
        nums[x-1] *= -1;
        if (nums[x-1] > 0) {  // If it's positive after flipping, it's a duplicate
            return_array[size++] = x;
        }
    }

    return return_array;
}
