/* O(N) runtime, O(1) space */
int missingNumber(int* nums, int numsSize) {
    /* if the [0, n] numbers were in the array, the sum would be n * (n+1) / 2 */
    /* there is only one missing number, so it has to be n*(n+1)/2 - sum_of_the_array */
    int sum = 0;
    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];
    }
    return (numsSize*(numsSize+1))/2 - sum;
}


/* O(N) runtime, O(1) space */
int missingNumberXOR(int* nums, int numsSize) {
    /* XOR all the elements of [0, n] and also nums */
    /* all same elements will be canceled out by XOR */
    /* [0,1,2,3] and [3,0,1] */
    /* 0 ^ 1 ^ 2 ^ 3 ^ 3 ^ 0 ^ 1 = 2 */
    int missing = 0;
    for (int i = 0; i < numsSize; i++) {
        missing = missing ^ nums[i];
        missing = missing ^ i;
    }
    return missing ^ numsSize;
}
