#include <string.h>

int min(int a, int b) {
    return a < b ? a : b;
}

long long minimumCost(char* s) {
    long long sum = 0;
    int n = strlen(s);
    for (int i = 1; i < n; i++) {
        if (s[i-1] != s[i]) {
            sum += min(i, n-i);
        }
    }
    return sum;
}
