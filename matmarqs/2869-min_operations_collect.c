#include <inttypes.h>
#include <stdio.h>

/******************************************************/

#include <stdint.h>

int minOperations(int* nums, int numsSize, int k) {
    uint64_t removed = 0;  // (n-1)-bit is set to 1, if the number n was removed
    int i = numsSize-1;
    int count = 0;
    while (count < k && i >= 0) {
        if (nums[i] <= k && !(removed & (1ULL << nums[i]))) { /* check the n-bit */
            count++;
            removed |= (1ULL << nums[i]);   /* set the n-bit */
        }
        i--;
    }
    return numsSize - i - 1;
}

/******************************************************/

int main() {
    int nums[] = {3,1,5,4,2};
    printf("%d\n", minOperations(nums, 5, 2));
}

/* 2^{k+1} - 1 = 2^0 + 2^1 + ... + 2^k = 11...1 (k+1 times) */
