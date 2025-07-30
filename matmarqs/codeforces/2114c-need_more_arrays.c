#include <stdio.h>

/* assume the array is sorted a[i] <= a[i+1], for all 0 <= i < n */
int solve(int *a, int n) {
    int max_num_arrays = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] == a[i-1]) {
            /* does not matter if we remove an element or not */
            ;
        }
        else if (a[i] == a[i-1] + 1) {
            /* in this case we always remove an element */
            /* because, a[i-1] + 1 will not create a new array */
            /* and it will disturb the next element a[i+1] */
            a[i] = a[i-1];  // we 'remove' by making it equal to the last one
        }
        else {  // a[i] > a[i-1] + 1
            /* a new array is always created */
            max_num_arrays++;
        }
    }
    return max_num_arrays;
}

int main() {
    int t, n, a[200000];
    scanf("%d", &t);
    for (; t > 0; t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        printf("%d\n", solve(a, n));
    }
}
