// Algorithm idea (Dynamic Programming):
// The first two base values are reserved: one for the first bag, one for the second
// for (i = 1; i < n; i++) {
//     If count[i] == 0:
//         There is nothing to do
//     If count[i] > 2:
//         Transfer the extras to the next bucket i+1: count[i+1] += count[i] - 2; count[i] = 2;
//     This will solve the problem for all 1 <= j <= i, now we have to solve for i+1
//     If count[i] == 1:
//         Then it is impossible to balance the two bags for the element i
//         We return false
// }
// At the end of the for loop, i == n
// If there are an odd number of elements at count[n]:
//     We can not balance the two bags, return false.
// If there are an even number of elements at count[n]:
//     We successfully balanced the two bags, return true.
//
// [3, 3, 4, 5, 3, 3]
//
//     *
//     *                  *
//     *                * *              * * *
//     * * *            * * *            * * *
// 1 2 3 4 5   ->   1 2 3 4 5   ->   1 2 3 4 5
//
// 
// [1, 1, 1, 1, 1, 1, 1, 4]
//
// *
// *
// *                *
// *                *
// *                *                *
// *              * *            * * *          * * * *
// *     *        * *   *        * * * *        * * * *
// 1 2 3 4   ->   1 2 3 4   ->   1 2 3 4   ->   1 2 3 4

#include <stdio.h>
#include <stdbool.h>

/* O(n) */
bool solve(int *a, int n) {
    /* count frequency of elements 1 <= i <= n <= 1000 */
    int count[1001] = { 0 };
    for (int i = 0; i < n; i++) {
        count[a[i]]++;
    }

    for (int i = 1; i < n; i++) {
        if (count[i] > 2) {
            count[i+1] += count[i] - 2;
            count[i] = 2;
        }
        if (count[i] == 1) {
            return false;
        }
    }

    if (count[n] % 2 == 0) {
        return true;
    }
    else {
        return false;
    }
}

int main() {
    int t;  /* 1 <= t <= 10^4 */
    int n;  /* 2 <= n <= 1000, n is even */
    int a[1000];    /* 1 <= a[i] <= n */
    /* sum_{all test cases} { n^2 } <= 10^6 */

    scanf("%d", &t);
    for (; t > 0; t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        if (solve(a, n)) {
            puts("YES");
        }
        else {
            puts("NO");
        }
    }
}
