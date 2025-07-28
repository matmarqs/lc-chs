/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* transformArray(int* nums, int numsSize, int* returnSize) {
    int num_even = 0;
    int num_odd = 0;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] % 2 == 1) {
            num_odd++;
        }
        else {
            num_even++;
        }
    }

    for (int i = 0; i < num_even; i++) {
        nums[i] = 0;
    }
    for (int i = num_even; i < numsSize; i++) {
        nums[i] = 1;
    }

    *returnSize = numsSize;
    return nums;
}
