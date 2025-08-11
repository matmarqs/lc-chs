#include <stdio.h>
#include <limits.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

void solve(int *a, int n) {
    int prefix_min[(int) 2e5], suffix_max[(int) 2e5];

    /* precalculate prefix_min */
    prefix_min[0] = INT_MAX;
    int pmin = INT_MAX;
    for (int i = 1; i < n; i++) {
        pmin = min(pmin, a[i-1]);
        prefix_min[i] = pmin;
    }

    /* precalculate suffix_max */
    suffix_max[n-1] = INT_MIN;
    int smax = INT_MIN;
    for (int i = n-2; i >= 0; i--) {
        smax = max(smax, a[i+1]);
        suffix_max[i] = smax;
    }

    for (int i = 0; i < n; i++) {
        /* if prefix_min[i] < a[i] < suffix_max[i] => binary[i] = 0 */
        /* otherwise, binary[i] = 1 */
        if (prefix_min[i] < a[i] && a[i] < suffix_max[i]) {
            putchar('0');
        }
        else {
            putchar('1');
        }
    }

    putchar('\n');
}

int main() {
    // Set bigger buffer for stdin and stdout
    static char input_buf[1 << 20];  // 1MB buffer
    static char output_buf[1 << 20];
    setvbuf(stdin, input_buf, _IOFBF, sizeof(input_buf));
    setvbuf(stdout, output_buf, _IOFBF, sizeof(output_buf));

    int t, n, a[(int) 2e5];
    scanf("%d", &t);
    for (; t > 0; t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }

        solve(a, n);
    }
}
