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

bool is_accessible(int l, int real, int k) {
    return l <= k && k < real;
}

/* O(n log n) */
int solve(Casino *casinos, int num_casinos, int k) {
    qsort(casinos, num_casinos, sizeof(Casino), cmp_casino);
    for (int i = 0; i < num_casinos; i++) {
        if (is_accessible(casinos[i].l, casinos[i].real, k)) {
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

        int count = 0;
        for (int i = 0; i < n; i++) {
            int l, r, real;
            scanf("%d %d %d", &l, &r , &real);
            /* otimizando, para diminuir o número de casinos que vão ser ordenados */
            if (is_accessible(l, real, k)) {
                k = real;
            }
            else {
                casinos[count].l = l;
                casinos[count].real = real;
                casinos[count].r = r;
                count++;
            }
        }

        printf("%d\n", solve(casinos, count, k));   /* O(n log n) */
    }
}
