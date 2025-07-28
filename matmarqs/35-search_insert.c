int searchInsert(int* nums, int numsSize, int target) {
    int low = 0;
    int high = numsSize;
    while (low + 1 < high) {
        if (target < nums[(low + high) / 2]) {
            high = (low + high) / 2;
        }
        else {
            low = (low + high) / 2;
        }
    }
    return (target <= nums[low]) ? low : low+1;
}
