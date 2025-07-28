/* end not included, array assumed to be: */
/* nums[start], nums[start + 1], ..., nums[end-1] */
/* the number of elements is end - start */
void reverse(int *nums, int start, int end) {
    int stop = (end - start)/2;
    for (int i = 0; i < stop; i++) {
        int aux = nums[start + i];
        nums[start + i] = nums[end - 1 - i];
        nums[end - 1 - i] = aux;
    }
}

/* O(N) time, O(1) space */
void rotate_by_reversing(int* nums, int numsSize, int k) {
    k %= numsSize;  /* guarantee that 0 <= k < numsSize */
    if (k == 0)
        return;

    reverse(nums, 0, numsSize); /* reverse the whole array */
    reverse(nums, 0, k);        /* reverse the first k elements */
    reverse(nums, k, numsSize); /* reverse the remaining n-k elements */
    /* this effectively rotates the array by k positions */
}

/* this solution is more number theoretic */

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

/* we shift +k through the cycle */
void cycle_k(int *nums, int n, int index, int cycle, int k) {
    int curr = nums[index];
    for (int r = 0; r < cycle; r++) {
        index += k;
        int next = nums[index % n];
        nums[index % n] = curr;
        curr = next;
    }
}

/* O(N) time, O(1) space */
void rotate(int* nums, int numsSize, int k) {
    k %= numsSize;  /* guarantee that 0 <= k < numsSize */
    if (k == 0)
        return;

    int d = gcd(numsSize, k);

    /* this is based on the ring Zn */
    if (d > 1) {
        int len_cycle = numsSize / d;
        for (int i = 0; i < d; i++) {
            cycle_k(nums, numsSize, i, len_cycle, k);
        }
    }
    else {
        cycle_k(nums, numsSize, 0, numsSize, k);
    }
}
