#include <stdlib.h>

/* return 1 if all digits are 9's, 0 otherwise */
int all_nines(int *digits, int digitsSize) {
    for (int i = 0; i < digitsSize; i++) {
        if (digits[i] != 9) {
            return 0;
        }
    }
    return 1;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* plusOne(int* digits, int digitsSize, int* returnSize) {
    int one_more_digit = all_nines(digits, digitsSize);
    *returnSize = digitsSize + one_more_digit;
    int *new_digits = (int *) malloc(*returnSize * sizeof(int));
    if (one_more_digit)
        new_digits[0] = 1;
    int j = *returnSize-1;
    int plus_one = 1;
    for (int i = digitsSize-1; i >= 0; i--) {
        if (plus_one) {
            if (digits[i] != 9) {
                new_digits[j] = digits[i] + 1;
                plus_one = 0;
            }
            else {
                new_digits[j] = 0;
            }
        }
        else {
            new_digits[j] = digits[i];
        }
        j--;
    }
    return new_digits;
}
