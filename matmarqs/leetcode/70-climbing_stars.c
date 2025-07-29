unsigned long long binomial_coefficient(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;
    k = (k < n - k) ? k : n - k;  // Use symmetry

    unsigned long long result = 1;
    for (int i = 1; i <= k; i++) {
        result = result * (n - k + i) / i;  /* the numerator is guaranteed to be divisible by the denominator. */
    }
    return result;
}

int climbStairs(int n) {
    unsigned long long sum = 0;
    for (int i = 0; i <= n/2; i++) {
        sum += binomial_coefficient(n-i, i);
    }
    return (int)sum;  // Cast back to int if needed
}
