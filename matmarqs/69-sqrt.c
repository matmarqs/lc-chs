#include <stdio.h>

/* the question asks for the nearest integer less or equal to the actual square root */

/* this is Newton's method */
/* it works because at each iteration r is always greater than the square root */
/* this is a property of Newton's method and because f(x) = x^2 - a is convex  */
/* when r is too near to the answer, it's fractional part will be truncated */
/* for example, we are calculating sqrt(2): if we get 1.4, r will be truncated to 1 and r^2 <= x */

/* one interesting thing: if we work with double type, we get beats 28% */
/* working with int and long, we get 100% */
/* double operations cost far more than integer operations */

int mySqrt(int x) {
    if (x == 0) return 0;
    long r = x;
    while (r > x/r)
        r = (r + x/r) / 2;
    return r;
}

int main() {
    printf("%d\n", mySqrt(8));
    return 0;
}
