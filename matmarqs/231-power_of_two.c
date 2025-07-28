#include <stdbool.h>

/***************************/

bool isPowerOfTwo(int n) {
    if (n < 0) {
        return false;
    }
    return (n != 0) && ((n & (n-1)) == 0);
}

/***************************/

/* 

100000000000
    &
011111111111
    =
000000000000



1100000
   &
1011111
   =
1000000


 * */

#include <stdio.h>

int main() {
    int n = -2147483648;
    printf("n:\tdecimal %d,\tbinário %b\n", n, n);
    printf("n-1:\tdecimal %d,\tbinário %b\n", n-1, n-1);
}
