#include <stdlib.h>

/* for this one we used space complexity O(m) */
/* but it could be improved by just using the space in the array nums1 */
/* for that we would have to calculate starting from the end of the array */

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
    /* copying nums1 to array1 */
    int *array1 = malloc(sizeof(int) * m);
    for (int j = 0; j < m; j++) {
        array1[j] = nums1[j];
    }

    int i = 0, j1 = 0, j2 = 0;
    while (i < m + n) {
        if (j1 >= m) {
            nums1[i] = nums2[j2++];
        }
        else if (j2 >= n) {
            nums1[i] = array1[j1++];
        }
        else {
            if (array1[j1] < nums2[j2]) {
                nums1[i] = array1[j1++];
            }
            else {
                nums1[i] = nums2[j2++];
            }
        }
        i++;
    }

    free(array1);
}
