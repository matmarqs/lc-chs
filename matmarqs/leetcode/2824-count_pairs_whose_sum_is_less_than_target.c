#include <stdlib.h>

int cmp_int(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

/* O(N log N) because of sorting */
/* two pointers solution */
int countPairs(int* nums, int numsSize, int target) {
    qsort(nums, numsSize, sizeof(int), cmp_int);

    int count = 0;

    int left = 0;
    int right = numsSize-1;

    /* this while loop is O(N) */
    while (left < right) {
        if (nums[left] + nums[right] < target) {
            count += right - left;  /* all the pairs (nums[left], nums[k]), left < k <= right, satisfy the condition */
            left++;
        }
        else {  /* if for the current left element, the right element does not satisfy, it will not satisfy for all the other greater left elements */
            right--;    /* because nums[left2] + nums[right] >= nums[left] + nums[right] >= target also */
        }
    }

    return count;
}
