#include <stdio.h>

/* this is the maximum total divineness of the tree, if the root label is k */
/* f(n, k) is monotonic increasing in 1 <= k <= n */
/* f(n, 1) = n */
/* f(n, n) = n(n+1)/2 */
long long f(long long n, long long k) {
    return (k * (k+1))/2 + (n - k) * k;
}

/* optimal_k = min { k \in {1, 2, ..., n} | m <= f(n, k) } */
/* we assume that f(n,1) <= m <= f(n,n) */
int find_optimal_k(int n, long long m) {    /* binary search method */
    int left = 1;
    int right = n;
    int k;
    while (1) {
        k = (left + right) / 2;
        if (m <= f(n, k)) {
            if (m > f(n, k-1)) {
                break;
            }
            else {
                right = k-1;
            }
        }
        else {
            left = k+1;
        }
    }
    return k;
}

void solve(int n, long long m, int *parent) {
    /* minimum of m = n */
    /* maximum of m = n*(n+1)/2 */
    if (m < f(n, 1) || m > f(n, n)) {
        printf("%d\n", -1);
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
    long long q = m - (k*(k+1))/2;

    int num_values_to_find = n - k;
    /* O(n) */
    for (int i = 0; i < num_values_to_find; i++) {
        int rem = num_values_to_find - i - 1;   /* how many remaining values we still have to choose after this one */
        long long min_val = q - rem * k;    /* minimum value we can assign to this position */
        /* Each of those can be at most k, so rem * k is the maximum the rest can sum to */
        if (min_val < 1) min_val = 1;
        if (min_val > k) min_val = k;
        /* Clamp min_val to the range [1, k], since each value must stay in that range. */
        parent[i] = min_val;
        q -= min_val;
    }

    // Output the result
    printf("%d\n", k);  // root of the tree
    for (int i = 1; i <= n; i++) {
        if (i == k) {   /* the root */
            continue;
        }
        if (i < k) {    /* vertices 1, 2, ..., k-1 */
            printf("%d %d\n", k, i);    /* they are direct children of the root */
        }
        else {  /* vertices k+1, k+2, ..., n */
            printf("%d %d\n", parent[i-(k+1)], i);    /* they direct children of the assigned partition */
        }
    }
}

int main() {
    int t, n;
    long long m;
    int parent[(int) 1e6];
    scanf("%d", &t);
    for (; t > 0; t--) {
        scanf("%d %lld", &n, &m);
        solve(n, m, parent);
    }
    return 0;
}

