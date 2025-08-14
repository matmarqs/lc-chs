/* 
 * All that matters in the input is the numbers of 0's, of 1's and of 2's.
 * Remember that num_0 > 0, num_1 > 0, and num_2 > 0
 *
 * 3 <= n <= 50
 * 0 <= s <= 1000
 *
 * The problem is not circular!
 *
 * the global minimum of s is 3.
 *
 * actually, the minimum of s is sum_i { a_i }
 * because we need to start from i = 1 and increment until i = n
 * this is the shortest path we can make
 *
 * | i_j - i_{j+1} | = 1 => this means that i_j can't be 0 and i_{j+1} = n (it is not circular)
 *
 * */

#include <stdio.h>

void solve(int n0, int n1, int n2, int s) {
    int base = n1 + 2*n2;

    if (s == base || s > base + 1) {
        putchar('-');
        putchar('1');
        putchar('\n');
        return;
    }

    while (n0) {
        putchar('0');
        putchar(' ');
        n0--;
    }
    while (n2) {
        putchar('2');
        putchar(' ');
        n2--;
    }
    while (n1) {
        putchar('1');
        putchar(' ');
        n1--;
    }
    putchar('\n');
}

int main() {
    // Set bigger buffer for stdin and stdout
    static char input_buf[1 << 20];  // 1MB buffer
    static char output_buf[1 << 20];
    setvbuf(stdin, input_buf, _IOFBF, sizeof(input_buf));
    setvbuf(stdout, output_buf, _IOFBF, sizeof(output_buf));

    int t, n, s;
    int num_0, num_1, num_2;
    scanf("%d", &t);
    for (; t > 0; t--) {
        scanf("%d %d", &n, &s);
        num_0 = num_1 = num_2 = 0;
        int temp;
        for (; n > 0; n--) {
            scanf("%d", &temp);
            if (temp == 0) {
                num_0++;
            }
            else if (temp == 1) {
                num_1++;
            }
            else if (temp == 2) {
                num_2++;
            }
        }
        solve(num_0, num_1, num_2, s);
    }
}
