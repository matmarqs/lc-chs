#include <stdlib.h>

int cmp_int(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int arrayPairSum(int* nums, int numsSize) {
    qsort(nums, numsSize, sizeof(int), cmp_int);
    int sum = 0;
    for (int i = 0; i < numsSize/2; i++) {
        sum += min(nums[2*i], nums[2*i+1]);
    }
    return sum;
}
