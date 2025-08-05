#include <stdio.h>

int max(int a, int b) {
    return a > b ? a : b;
}

long long solve(int n, int *a, long long *max_score) {
    max_score[n] = a[n];
    long long global_max = a[n];
    for (int i = n-1; i > 0; i--) {
        max_score[i] = (i + a[i] > n) ? a[i] : max_score[i + a[i]] + a[i];
        global_max = max(global_max, max_score[i]);
    }
    return global_max;
}

int main() {
    int t, n;
    int a[(int) 2e5 + 1];
    long long max_score[(int) 2e5 + 1];
    scanf("%d", &t);
    for (; t > 0; t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        /* actual code */
        printf("%lld\n", solve(n, a, max_score));
    }
}
