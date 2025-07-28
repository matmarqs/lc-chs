#include <stdlib.h>

typedef struct Side {
   int *nums;
   int len;
   int below;
   int above;
} Side;

Side *side_init(int *nums, int numsSize) {
   Side *side = malloc(sizeof(Side));
   side->nums = nums;
   side->len = numsSize;
   side->below = 0;
   side->above = 0;
   return side;
}

void side_free(Side *side) {
   free(side);
}

void slice_sides(Side *side1, Side *side2) {
   int *nums1 = side1->nums;
   int *nums2 = side2->nums;
   int l1 = side1->len;
   int l2 = side2->len;

   int a1 = (l1 % 2 == 1) ? l1/2 : l1/2-1;
   int b1 = l1/2;
   int a2 = (l2 % 2 == 1) ? l2/2 : l2/2-1;
   int b2 = l2/2;

   int min = nums1[a1] < nums2[a2] ? 1 : 2;

   if (min == 1) {
      side1->nums += a1;
      side1->len -= a1;
      side1->below += a1;
      side2->len = b2 + 1;
      side2->above += l2 - (b2 + 1);
   }
   else {
      side2->nums += a2;
      side2->len -= a2;
      side2->below += a2;
      side1->len = b1 + 1;
      side1->above += l1 - (b1 + 1);
   }
}

double solve_final_slice(Side *side1, Side *side2) {
   /* we know the 0 <= l1, l2 <= 2, and l1 + l2 >= 1 */
   int l1 = side1->len;
   int l2 = side2->len;

   if (l1 == 0) {
      if (l2 == 1)
         return side2->nums[0];
      else {   /* l2 == 2 */
         return (side2->nums[0] + side2->nums[1]) / (2.0);
      }
   }
   if (l2 == 0) {
      if (l1 == 1)
         return side1->nums[0];
      else {   /* l1 == 2 */
         return (side1->nums[0] + side1->nums[1]) / (2.0);
      }
   }

   /* complete the function here */

}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
   Side *side1 = side_init(nums1, nums1Size);
   Side *side2 = side_init(nums2, nums2Size);
   while (side1->len > 2 && side2->len > 2) {
      slice_sides(side1, side2);
   }

   return solve_final_slice(side1, side2);
}

/*
m + n = p

let's say p is even, p = 2k

for M to be the median, M has to be greater or equal to k numbers and less or equal to k numbers.
this defines the median uniquely.

nums1 and nums2 are sorted
in order to get their median, we take O(1).
just take nums1[m/2] if m odd or (nums1[m/2] + nums1[m/2-1])/2 if m even.


let's take M1 = nums1[m/2] and M2 = nums2[n/2].
we have that M1 is greater or equal to m/2



            len/2=2                    len/2 = 2
[1,4,6,10], len = 4 and [3,7,9,10,30], len = 5
 0 1 2  3                0 1 2  3  4
     *                       *
se forem iguais, achamos a mediana!
who is greater? 6 < 9
pode ser maior que 9? não, pois então seria maior que 3 + 2 = 5. não é a mediana!
pode ser menor que 6? não, pois então seria menor que 2 + 3 = 5. não é a mediana!
então, sabemos que ele pertence a 6 <= x <= 9.
i = 2 (esquerdo) e j = 2 (direito)

->

[1,3,4,6,7,9,10,10,30], len = 9, len/2 = 4. a mediana tem que ser maior ou igual que 4
 0 1 2 3 4 5  6  7  8
         *

[6,10], len=2, len/2 = 1 and [3,7,9], len=3, len/2=1
 0  1                         0 1 2
    *                           *
->
[3,6,7,9,10]


0,0            0,0
[1,4,6,10] and [3,7,9,10,30]
   * *              *

1,0          0,2
[4,6,10] and [3,7,9]
   *            *

2,0        0,3
[6,10] and [3,7] -> [3,6,7,10]

[1,3,4,6,7,9,10,10,30]



[2,2,4,5,8,11,13,15]
 0 1 2 3 4  5  6  7
       * *

[2,5,11,15] and [2,4,8,13]
 0 1  2  3       0 1 2  3
   *  *            * *
pegamos o maior dos 4 e o menor dos 4: 11 > 4
pode ser maior que 11? não, pois seria maior que 3 + 3 = 6
pode ser menor que 4? não, pois seria menor que 3+3 = 6.

logo 4 <= x <= 11
[2,5,11] and [4,8,13]


[2,5,11,15] and [2,4,8,13]
   *  *            * *

[2,5,11] and [4,8,13]
   *            *

[5,11] and [4,8] => (5+8)/2 = 6.5


[10],[15]


[1,2,3,10] and [5,6,7,8]
   * *            * *

[2,3,10] and [5,6,7]
   *            *

[3,10] and [5,6]

if (size1 + size2 <= 4) => retorna mediana



[1,2,3,4,5,6,7,8,9] and [11,12,13,14,15,16,17,18,19]
         *                            *

[5,6,7,8,9] and [11,12,13,14,15]
     *                  *

[7,8,9] and [11,12,13]
   *             *

[8,9] and [11,12] => (9 + 11)/2





[1,1,7,9,10,20,30]
       *


[1,10,20] and [1,7,9,30]
    *            * *
menor=10         menor=7
maior=10         maior=9
0,1        1,0
[1,10] and [7,9,30]
 *  *         *

0,1        2,0
[1,10] and [9, 30]
->
0,1  2,0    0,1   2,0
[1,   9,    10,   30]

->

0,6  3,3   4,2    5,1
[1,  9,    10,    30]









0,1        2,0
[1,10] and [9, 30]


WRONG ANSWER, test case nums1 = [1,2,3,4,5], len=5 and nums2 = [6,7,8,9,10,11,12,13,14,15,16,17], len=12
output = 7, answer = 9


0         0     0                               0
[1,2,3,4,5] and [6,7,8,9,10,11,12,13,14,15,16,17]
 0 1 2 3 4       0 1 2 3  4  5  6  7  8  9 10 11
     *                       *  *

2     0     0                5
[3,4,5] and [6,7,8,9,10,11,12]
   *               *

3   0     0       8
[4,5] and [6,7,8,9]
 * *         * *

[4,5] and [6,7,8]
 * *         *

[4,5,7]



*/
