#include <stdbool.h>
bool isBadVersion(int version);

// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

int firstBadVersion(int n) {
    int left = 1;
    int right = n;
    int v = left + (right - left) / 2;
    while (left < right) {
        if (isBadVersion(v)) {
            right = v;
        }
        else {
            left = v+1;
        }
        v = left + (right - left) / 2;
    }
    return v;
}
