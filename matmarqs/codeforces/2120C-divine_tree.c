#include <stdio.h>

/* fast I/O, because I got Time Limit Exceeded */
static char outbuf[8<<20];
static int outidx = 0;

void flush_output() {
    if (outidx) {
        fwrite(outbuf, 1, outidx, stdout);
        outidx = 0;
    }
}

void fast_write_int(int x) {
    if (x == 0) {
        if (outidx == sizeof(outbuf)) flush_output();
        outbuf[outidx++] = '0';
        return;
    }
    char temp[12];
    int len = 0;
    int is_negative = 0;
    if (x < 0) {
        is_negative = 1;
        x = -x;
    }
    while (x) {
        temp[len++] = x % 10 + '0';
        x /= 10;
    }
    if (outidx + len + is_negative > sizeof(outbuf)) {
        flush_output();
    }
    if (is_negative) {
        outbuf[outidx++] = '-';
    }
    for (int i = len-1; i >= 0; i--) {
        outbuf[outidx++] = temp[i];
    }
}

void fast_write_char(char c) {
    if (outidx == sizeof(outbuf)) {
        flush_output();
    }
    outbuf[outidx++] = c;
}

/* this is the maximum total divineness of the tree, if the root label is k */
/* f(n, k) is monotonic increasing in 1 <= k <= n */
/* f(n, 1) = n */
/* f(n, n) = n(n+1)/2 */
long long f(long long n, long long k) {
    return (k * (k+1))/2 + (n - k) * k;
}

/* optimal_k = min { k \in {1, 2, ..., n} | m <= f(n, k) } */
/* we assume that f(n,1) <= m <= f(n,n) */
int find_optimal_k(int n, long long m) {
    int left = 1;
    int right = n;
    int k;
    while (1) {
        k = (left + right) / 2;
        long long fk = f(n, k);
        if (m <= fk) {
            long long fk_prev = 0;
            if (k > 1) {
                fk_prev = f(n, k-1);
            }
            if (m > fk_prev) {
                break;
            } else {
                right = k-1;
            }
        } else {
            left = k+1;
        }
    }
    return k;
}

void solve(int n, long long m) {
    /* minimum of m = n */
    /* maximum of m = n*(n+1)/2 */
    if (m < f(n, 1) || m > f(n, n)) {
        fast_write_int(-1);
        fast_write_char('\n');
        return;
    }

    /* now it is guaranteed there is a solution */
    /* first, we need to find the optimal k (label for the root) */
    /* optimal_k = min_k { m <= f(n, k) } */
    /* we could find this with binary search, or linear search */
    int k = find_optimal_k(n, m);   /* O(log n) */

    /* now the tree will be constructed as follows: */
    /* the root label is k */
    /* the nodes 1, 2, 3, ..., k-1 will be direct children of the root */
    /* so, until now, the divineness is k(k+1)/2 */
    /* the remaining nodes are k+1, k+2, ..., n */
    /* they will be directly attached to some node with label 1 <= l <= k */
    /* and their divineness is the parent to which they were attached */
    /* therefore, we need to find any partition */
    /* q_{k+1} + q_{k+2} + ... + q_{n} = q = m - k(k+1)/2; */

    /* output the root of the tree */
    fast_write_int(k);
    fast_write_char('\n');

    /* output vertices 1, 2, ..., k-1 */
    /* they are direct children of the root */
    for (int i = 1; i < k; i++) {
        fast_write_int(k);
        fast_write_char(' ');
        fast_write_int(i);
        fast_write_char('\n');
    }

    long long q_val = m - (long long)k * (k+1) / 2;
    for (int j = k+1; j <= n; j++) {
        int rem = n - j;    /* how many remaining values we still have to choose after this one */
        long long min_val = q_val - (long long)rem * k; /* minimum value we can assign to this position */
        /* Each of those can be at most k, so rem * k is the maximum the rest can sum to */
        /* Clamp min_val to the range [1, k], since each value must stay in that range. */
        if (min_val < 1) min_val = 1;
        if (min_val > k) min_val = k;
        q_val -= min_val;

        fast_write_int((int)min_val);
        fast_write_char(' ');
        fast_write_int(j);
        fast_write_char('\n');
    }
}

int main() {
    int t, n;
    long long m;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %lld", &n, &m);
        solve(n, m);
    }
    flush_output(); /* fast I/O, because I got Time Limit Exceeded */
    return 0;
}
