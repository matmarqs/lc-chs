#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countBits(int n, int* returnSize) {
    *returnSize = n+1;
    int *ans = (int *) malloc(sizeof(int) * (n+1));
    ans[0] = 0;
    int power = 1;
    for (int i = 1; i <= n; i++) {
        if (i == power) {
            ans[i] = 1;
            power = power << 1;
        }
        else {
            ans[i] = ans[i-(power >> 1)] + 1;
        }
    }
    return ans;
}
