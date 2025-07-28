#include <stdio.h>
typedef enum {true, false} bool;

#include <math.h>

int digit(int x, int d) {
   int pot10 = 1;
   for (int i = 0; i < d; i++)
      pot10 *= 10;
   return (x / pot10) % 10;
}

bool isPalindrome(int x) {
   if (x < 0) 
        return false;

   int num_digits = (int) log10(x) + 1;

   /* 1 2 1 2 1 */
   /* 4 3 2 1 0 */

   /* 2 7 7 2 */
   /* 3 2 1 0 */

   int n = num_digits/2 - 1;
   for (int i = 0; i <= n; i++) {
      if (digit(x, i) != digit(x, num_digits-i-1))
         return false;
   }
   return true;
}

int main() {
   printf("%d\n", (int) log10(10) + 1);
   return 0;
}
