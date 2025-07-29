#include <stdbool.h>

/**********************************************************/

#include <stdlib.h>

/* O(N) solution */
bool canThreePartsEqualSum(int* arr, int arrSize) {
    long long *sumarr = (long long *) malloc(sizeof(long) * arrSize);
    long long sum = 0LL;
    for (int i = 0; i < arrSize; i++) {
        sum += (long long) arr[i];
        sumarr[i] = sum;
    }

    long long totalSum = sumarr[arrSize-1];

    /* totalSum has to be divisible by 3 */
    if (totalSum % 3 != 0) {
        goto fail;
    }

    int i;
    long long sum1;
    for (i = 0; i < arrSize - 2; i++) {
        sum1 = sumarr[i];
        if (sum1 == totalSum/3) {
            break;
        }
    }
    if (sum1 != totalSum/3) {
        goto fail;
    }

    int j;
    long long sum2;
    for (j = i+1; j < arrSize - 1; j++) {
        sum2 = sumarr[j] - sumarr[i];
        if (sum2 == totalSum/3) {
            break;
        }
    }
    if (sum2 != totalSum/3) {
        goto fail;
    }

    long long sum3 = sumarr[arrSize-1] - sumarr[j];
    free(sumarr);
    return sum3 == totalSum/3;

fail:
    free(sumarr);
    return false;
}

/**********************************************************/

/* O(N^2) solution: time limit exceeded */
bool canThreePartsEqualSum_TimeExceeded(int* arr, int arrSize) {
    long long *sumarr = (long long *) malloc(sizeof(long) * arrSize);
    long long sum = 0LL;
    for (int i = 0; i < arrSize; i++) {
        sum += (long long) arr[i];
        sumarr[i] = sum;
    }

    for (int i = 0; i < arrSize - 2; i++) {
        long long sum1 = sumarr[i];
        for (int j = i+1; j < arrSize-1; j++) {
            long long sum2 = sumarr[j] - sumarr[i]; 
            if (sum1 == sum2) {
                long long sum3 = sumarr[arrSize-1] - sumarr[j];
                if (sum2 == sum3) {
                    return true;
                }
            }
        }
    }
    return false;
}
