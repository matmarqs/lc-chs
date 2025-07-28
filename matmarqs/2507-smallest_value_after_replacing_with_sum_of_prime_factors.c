int sumPrimeFactors(int n) {
    int sum = 0;

    // Handle 2 separately (only even prime)
    while (n % 2 == 0) {
        sum += 2;
        n /= 2;
    }

    // Handle 3 separately
    while (n % 3 == 0) {
        sum += 3;
        n /= 3;
    }

    // Now check for factors of the form 6k ± 1 (5, 7, 11, 13, ...)
    for (int p = 5; p * p <= n; p += 6) {
        while (n % p == 0) {
            sum += p;
            n /= p;
        }
        while (n % (p + 2) == 0) {
            sum += (p + 2);
            n /= (p + 2);
        }
    }

    // If remaining n is a prime > 1
    if (n > 1) {
        sum += n;
    }

    return sum;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int smallestValue(int n) {
    int next = sumPrimeFactors(n);
    int smallest = min(next, n);
    while (n != next) {
        n = next;
        next = sumPrimeFactors(n);
        smallest = min(next, n);
    }

    return smallest;
}
