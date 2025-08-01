// n = 5
//      k = 1:
//          5 5 5 5 4, min_dist = 1
//      k = 2:
//          4 4 4 5 4, min_dist = 1
//      k = 1:
//          5 5 5 5 4, min_dist = 1
// idea:
// we always teleport n -> n-1
// if k is odd, we teleport every i != n -> n
// if k is even, we teleport n-1 -> n and every other i -> n-1

#include <stdio.h>

#define is_odd(n) ((n) & 1)
#define is_even(n) (!((n) & 1))

int main() {
    int t, n, k;
    scanf("%d", &t);
    for (; t > 0; t--) {
        scanf("%d %d", &n, &k);
        if (is_odd(k)) {
            for (int i = 1; i <= n; i++) {
                if (i == n) {
                    printf("%d\n", n-1);
                }
                else {
                    printf("%d ", n);
                }
            }
        }
        else {
            for (int i = 1; i <= n; i++) {
                if (i == n) {
                    printf("%d\n", n-1);
                }
                else if (i == n-1) {
                    printf("%d ", n);
                }
                else {
                    printf("%d ", n-1);
                }
            }
        }
    }
}
