#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int l;
    int r;
    int real;
} Casino;

/* r_i does not make different, because it does not make sense to play */
/* in the casino when real_i < x <= r_i */
int cmp_casino(const void *a, const void *b) {
    Casino ca = *(Casino *)a;
    Casino cb = *(Casino *)b;
    if (ca.real != cb.real) {
        return ca.real - cb.real;
    }
    return -(ca.l - cb.l);
}

bool we_play_at_casino(Casino casino, int k) {
    return casino.l <= k && k < casino.real;
}

/* O(n log n) */
int solve(Casino *casinos, int n, int k) {
    qsort(casinos, n, sizeof(Casino), cmp_casino);
    for (int i = 0; i < n; i++) {
        if (we_play_at_casino(casinos[i], k)) {
            k = casinos[i].real;
        }
    }
    return k;
}

/* O(t n log n) */
int main() {
    int t;
    scanf("%d", &t);

    for (; t > 0; t--) {    /* O(t) */
        int n, k;
        scanf("%d %d", &n, &k);

        Casino casinos[100000]; /* n <= 10^5 */

        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &casinos[i].l, &casinos[i].r , &casinos[i].real);
        }

        printf("%d\n", solve(casinos, n, k));   /* O(n log n) */
    }
}
