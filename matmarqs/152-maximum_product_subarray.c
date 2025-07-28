int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

/* O(N) time, O(1) space */
int maxProduct(int* nums, int numsSize) {
    int global_max = nums[0];
    int last_max = nums[0];
    int last_min = nums[0];
    for (int i = 1; i < numsSize; i++) {
        /* max( last_max * nums[i], last_min * nums[i], nums[i] ) */
        int new_max = max(max(nums[i], last_max * nums[i]), last_min * nums[i]);
        /* min( last_max * nums[i], last_min * nums[i], nums[i] ) */
        int new_min = min(min(nums[i], last_max * nums[i]), last_min * nums[i]);
        global_max = max(global_max, new_max);
        last_max = new_max;
        last_min = new_min;
    }
    return global_max;
}
