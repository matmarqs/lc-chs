int max(int a, int b) {
    return a > b ? a : b;
}

/* return the last element < target */
int binary_search_less(int *nums, int size, int target) {
    if (nums[0] >= target) {
        return -1;
    }
    if (nums[size-1] < target) {
        return size-1;
    }
    /* from here, we are sure that there exists an element < target such that the next is >= target */
    int mid, left = 0, right = size-1;
    while (1) {
        mid = (left + right) / 2;   /* left <= mid <= right */
        if (nums[mid] < target) {
            if (nums[mid+1] >= target) {
                break;
            }
            else {
                left = mid+1;
            }
        }
        else {
            right = mid-1;
        }
    }
    return mid;
}

/* return the first element > target */
int binary_search_greater(int *nums, int size, int target) {
    if (nums[size-1] <= target) {
        return size;
    }
    if (nums[0] > target) {
        return 0;
    }
    /* from here, we are sure that there exists an element > target, such that the previous is <= target */
    int mid, left = 0, right = size-1;
    while (1) {
        mid = (left + right) / 2;   /* left <= mid <= right */
        if (nums[mid] > target) {
            if (nums[mid-1] <= target) {
                break;
            }
            else {
                right = mid-1;
            }
        }
        else {
            left = mid+1;
        }
    }
    return mid;
}

int maximumCount(int* nums, int numsSize) {
    int last_less = binary_search_less(nums, numsSize, 0);
    int first_greater = binary_search_greater(nums, numsSize, 0);
    return max(last_less - (-1), numsSize - first_greater);
}
