#include <stdio.h>

/******************************************/

#include <stdlib.h>

/* we use a Monotonic Stack to find prev_smaller and next_smaller */
/* increase the sum by arr[stack[top]] * left * right */
/* considering the subarrays that arr[stack[top]] is a minimum: */
/* left is the number of positions that a subarray can start */
/* right is the number of positions that a subarray can end */

/* O(n) time, O(n) space */
int sumSubarrayMins(int* arr, int arrSize) {
    const int MOD = 1e9 + 7;
    long long sum = 0;

    // Increasing monotonic stack to find previous and next smaller elements
    int *stack = (int *)malloc(arrSize * sizeof(int));
    int top = -1;

    long long left, right;
    for (int i = 0; i <= arrSize; i++) {
        while (top >= 0 && (i == arrSize || arr[i] <= arr[stack[top]])) {
            left = stack[top] - (top > 0 ? stack[top-1] : -1);
            right = i - stack[top];
            sum = (sum + ((long long) arr[stack[top]]) * left * right) % MOD;
            top--;
        }
        stack[++top] = i;
    }

    free(stack);
    return (int) sum;
}

/******************************************/

int main() {
    int arr[] = { 11,81,94,43,3 };
    int sum = sumSubarrayMins(arr, 5);
    printf("soma final = %d\n", sum);
    return 0;
}
