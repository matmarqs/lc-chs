#include <stdio.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int solve(int m, int a, int b, int c) {
    int places_1 = m;
    int places_2 = m;

    places_1 -= min(a, m);
    places_2 -= min(b, m);

    if (places_1 > 0 && c > 0) {
        int c1 = min(c, places_1);
        places_1 -= c1;
        c -= c1;
    }
    if (places_2 > 0 && c > 0) {
        places_2 -= min(c, places_2);
    }

    return 2*m - places_1 - places_2;
}

int main() {
    int t;
    int m, a, b, c;

    scanf("%d", &t);

    for (; t > 0; t--) {
        scanf("%d %d %d %d", &m, &a, &b, &c);
        printf("%d\n", solve(m, a, b, c));
    }
}
