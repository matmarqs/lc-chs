#include <stdlib.h>
#include <math.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

/* worst case O(sqrt(area)) */
int* constructRectangle(int area, int* returnSize) {
    *returnSize = 2;
    int *lw = (int *) malloc(sizeof(int) * 2);
    int area_sqrt = (int) sqrt(area);
    for (int w = area_sqrt; w > 0; w--) {
        if (area % w == 0) {
            lw[0] = area / w;
            lw[1] = w;
            return lw;
        }
    }
    /* unreachable */
    return lw;
}
