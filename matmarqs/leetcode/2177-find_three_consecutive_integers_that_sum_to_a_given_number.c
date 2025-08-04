#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
long long* sumOfThree(long long num, int* returnSize) {
    /* n + (n+1) + (n+2) = num */
    /* 3n + 3 = num */
    /* n = (num - 3) / 3 */
    if (num % 3 == 0) {
        *returnSize = 3;
        long long *s = malloc(sizeof(long long) * 3);
        s[0] = (num - 3) / 3;
        s[1] = (num - 3) / 3 + 1;
        s[2] = (num - 3) / 3 + 2;
        return s;
    }
    else {
        *returnSize = 0;
        return NULL;
    }
}
