#include <stdlib.h>

long long minOperations(int* nums1, int nums1Size, int* nums2, int nums2Size, int k) {
    int n = nums1Size;
    if (k != 0) {
        long long total_diff = 0;
        long long below = 0;
        long long above = 0;
        for (int i = 0; i < n; i++) {
            long long diff = nums1[i] - nums2[i];
            total_diff += diff;
            if (labs(diff) % k == 0) {
                if (diff < 0) {
                    below += labs(diff) / k;
                }
                else if (diff > 0) {
                    above += labs(diff) / k;
                }
            }
            else {
                return -1;
            }
        }
        if (total_diff != 0) {
            return -1;
        }
        if (above != below) {
            return -1;
        }
        return above;
    }
    else {
        for (int i = 0; i < n; i++) {
            if (nums1[i] != nums2[i]) {
                return -1;
            }
        }
        return 0;
    }
}
