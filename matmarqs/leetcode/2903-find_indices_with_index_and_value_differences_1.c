#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findIndices(int* nums, int numsSize, int indexDifference, int valueDifference, int* returnSize) {
    *returnSize = 2;
    int *ans = malloc(8);
    for (int i = 0; i < numsSize; i++) {
        for (int j = indexDifference + i; j < numsSize; j++) {
            if (abs(nums[i] - nums[j]) >= valueDifference) {
                ans[0] = i;
                ans[1] = j;
                return ans;
            }
        }
    }
    ans[0] = -1;
    ans[1] = -1;
    return ans;
}
