#include <stdio.h>
#include <stdbool.h>

/* O(n) */
/* return 1 <= num <= n if it can put num in second_bag */
/* else return 0 */
int can_put_in_second_bag(int *fst, int *snd, int n) {
    /* it is worth to have one copy of each element in the second bag */
    for (int i = 1; i <= n; i++) {
        if (fst[i] > 1 && snd[i] == 0) {
            return i;
        }
    }
    return 0;
}

/* O(n) */
/* return 1 <= num <= n if it can increase num in first_bag */
/* else return 0 */
int can_increase_first(int *fst, int *snd, int n) {
    for (int i = 1; i <= n; i++) {
        if (snd[i] > 0 && fst[i] > 1) {
            return i;
        }
    }
    return 0;
}

/* O(n^2) */
bool solve(int *a, int n) {
    /* the bags store the count */
    int fst[1001] = { 0 };
    int snd[1001] = { 0 };
    for (int i = 0; i < n; i++) {
        fst[a[i]]++;
    }

    int target;
    while (target = can_put_in_second_bag(fst, snd, n)) {
    }
}

int main() {
    int t;  /* 1 <= t <= 10^4 */
    int n;  /* 2 <= n <= 1000, n is even */
    int a[1000];    /* 1 <= a[i] <= n */
    /* sum_{all test cases} { n^2 } <= 10^6 */

    /* from the constraints, a O(n^2) solution will probably pass */
    scanf("%d", &t);
    for (; t > 0; t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
    }
}
